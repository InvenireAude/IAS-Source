/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/Socket.cpp
 *
 * Copyright (C) 2020, Albert Krzymowski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Socket.h"

#include <commonlib/commonlib.h>
#include <unistd.h>

namespace IAS {
namespace Net {
namespace UDP {

/*************************************************************************/
Socket::Socket(unsigned int iDestinationPort):
	iDestinationPort(iDestinationPort),
	iTimeout(C_UnLimited){
	IAS_TRACER;

	if((iSocket=socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		IAS_THROW(SystemException("UDP socket, port: ")<<(int)iDestinationPort);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"iSocket:"<<iSocket);
}
/*************************************************************************/
Socket::~Socket() throw(){
	IAS_TRACER;

	if(iSocket > 0)
		::close(iSocket);
}
/*************************************************************************/
void Socket::setTimeout(int iTimeout){
	IAS_TRACER;

	if(iTimeout != C_UnLimited && iTimeout < 0)
		IAS_THROW(BadUsageException("timeout: ")<<iTimeout);

	this->iTimeout=iTimeout;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"fd("<<iSocket<<"), timeout: "<<this->iTimeout);
}
/*************************************************************************/
bool Socket::waitForData(WaitMode iMode){
	IAS_TRACER;

	 fd_set set;
	 struct timeval timeout;

	 FD_ZERO(&set);
	 FD_SET(iSocket, &set);

	 timeout.tv_sec = 0;
	 timeout.tv_usec = 1000*iTimeout;

	 IAS_LOG(LogLevel::INSTANCE.isInfo(),"fd("<<iSocket<<"), timeout: "<<iTimeout);

	 int iRC = ::select(iSocket + 1,
			 	 (iMode == WM_Read  ? &set : NULL),
				 (iMode == WM_Write ? &set : NULL),
				 &set,
				 iTimeout == C_UnLimited ? NULL : &timeout);

	 IAS_LOG(LogLevel::INSTANCE.isInfo(),"rc="<<iRC);

	 switch(iRC){
	 	 case -1:
	 		 IAS_THROW(SystemException("select: ")<<iSocket)
			 break;
	 	 case 0:
	 		 return false;
	 		 break;
	 }

	 return true;
}
/*************************************************************************/
void Socket::bind(unsigned int iPort){
	IAS_TRACER;
	struct sockaddr_in localSock;

	bzero((char *)&localSock, sizeof(localSock));

	localSock.sin_family = AF_INET;
  localSock.sin_port = htons(iPort);
  localSock.sin_addr.s_addr = INADDR_ANY;

  if(::bind(iSocket, (struct sockaddr *)&localSock, sizeof(localSock)) == -1){
		IAS_THROW(SystemException()<<"UDP  socket (bind), port: "<<(int)iDestinationPort);
  }

}
/*************************************************************************/
bool Socket::receive(void *pData, size_t iBufferLen, size_t& iDataSize,
                    struct sockaddr_storage* pSrcAddress, socklen_t* pAddressLen){
	IAS_TRACER;

	ssize_t iResult = 0;

	{
		Thread::Cancellation ca(true);
    IAS_LOG(LogLevel::INSTANCE.isInfo(),"Timeout: "<<iTimeout);
		if(iTimeout != 0)
			if(!waitForData(WM_Read)){
				iDataSize = 0;
				return false;
		}


		iResult = ::recvfrom(iSocket, pData, iBufferLen, 0, (struct sockaddr*)pSrcAddress, pAddressLen);
	}

  if(LogLevel::INSTANCE.isSystem()){
   switch (pSrcAddress->ss_family){
    case AF_INET:
          {
            StringStream ssTmp;
            struct sockaddr_in* a = reinterpret_cast<struct sockaddr_in*>(pSrcAddress);
            ssTmp<<(a->sin_addr.s_addr  & 0x000000ff)<<".";
            ssTmp<<((a->sin_addr.s_addr & 0x0000ff00) >> 8)<<".";
            ssTmp<<((a->sin_addr.s_addr & 0x00ff0000) >> 16)<<".";
            ssTmp<<((a->sin_addr.s_addr & 0xff000000) >> 24)<<":"<<ntohs(a->sin_port);
            IAS_LOG(true, "ReceivedFrom: "<<ssTmp.str());
          }
        break;
    case AF_INET6:
        IAS_LOG(true, "ReceivedFrom: IPv6");
        break;
    default:
        IAS_LOG(true, "Unknown: "<<pSrcAddress->ss_family);
    }
  }


  // TODO class ipAddress or at least conversions.

	if(iResult < 0){
		IAS_LOG(LogLevel::INSTANCE.isError(),"READ:"<<(void*)pData<<"len="<<iBufferLen);
		IAS_THROW(SystemException("read",errno));
	}

	if(LogLevel::INSTANCE.isData()){
		String strData;
		for(int i=0;i<iResult;i++)
			strData += String("") + (*(((char*)pData)+i) >= ' ' ? *(((char*)pData)+i) : '.');
		IAS_LOG(LogLevel::INSTANCE.isData(),"READ:"<<iResult<<" ["<<strData<<"]");
	}

	iDataSize = iResult;
  return true;
}
/*************************************************************************/
bool Socket::receive(void *pData, size_t iBufferLen, size_t& iDataSize){

  return receive(pData, iBufferLen, iDataSize, NULL, NULL);
}
/*************************************************************************/
bool Socket::receive(void *pData, size_t iBufferLen, size_t& iDataSize, String& strSrcIP, int &iSrcPort){

  struct sockaddr_storage srcAddress;
  socklen_t iAddressLen;

  if(!receive(pData, iBufferLen, iDataSize, &srcAddress, &iAddressLen))
    return false;

  switch (srcAddress.ss_family){
    case AF_INET:
          {
            StringStream ssTmp;
            struct sockaddr_in* a = reinterpret_cast<struct sockaddr_in*>(&srcAddress);
            ssTmp<<(a->sin_addr.s_addr  & 0x000000ff)<<".";
            ssTmp<<((a->sin_addr.s_addr & 0x0000ff00) >> 8)<<".";
            ssTmp<<((a->sin_addr.s_addr & 0x00ff0000) >> 16)<<".";
            ssTmp<<((a->sin_addr.s_addr & 0xff000000) >> 24);
            strSrcIP=ssTmp.str();
            iSrcPort=ntohs(a->sin_port);
          }
        break;
    case AF_INET6:

        break;
  }

	return true;
}
/*************************************************************************/
void Socket::send(struct sockaddr_in& destSockAddr, const void *pData, size_t iDataSize, size_t& iWritten){
	IAS_TRACER;

	ssize_t iResult = 0;

	if(LogLevel::INSTANCE.isData()){
		String strData;
		for(int i=0;i<iDataSize;i++)
			strData += String("") + (*(((char*)pData)+i) >= ' ' ? *(((char*)pData)+i) : '.');
		IAS_LOG(LogLevel::INSTANCE.isData(),"WRITE:"<<iDataSize<<" ["<<strData<<"]");
	}

	{
		Thread::Cancellation ca(true);
		iResult = ::sendto(iSocket, pData, iDataSize, 0, (struct sockaddr *)&destSockAddr, sizeof(destSockAddr));
	}

	if(iResult < 0){
		IAS_LOG(LogLevel::INSTANCE.isError(),"SEND:"<<(void*)pData<<"len="<<iDataSize);
		IAS_THROW(SystemException("write",errno));
	}

	iWritten = iResult;
}
/*************************************************************************/
}
}
}
