/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/Receiver.cpp
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

#include "Receiver.h"

#include <commonlib/commonlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

namespace IAS {
namespace Net {
namespace UDP {

/*************************************************************************/
Receiver::Receiver(unsigned int iDestinationPort):
	Base(iDestinationPort){
	IAS_TRACER;

	// int size = 1000 * 1024 * 1024;

	// if (setsockopt(iSocket, SOL_SOCKET, SO_RCVBUF, &size, (socklen_t)sizeof(int)) < 0)
  // 	IAS_THROW(SystemException()<<"UDP mulitcast socket (SO_RCVBUF), port: "<<(int)iDestinationPort);

	int reuse = 1;

  if (setsockopt(iSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
   	IAS_THROW(SystemException()<<"UDP socket (SO_REUSEADDR), port: "<<(int)iDestinationPort);
}
/*************************************************************************/
Receiver::~Receiver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Receiver::bind(){
	IAS_TRACER;
	struct sockaddr_in localSock;

	bzero((char *)&localSock, sizeof(localSock));

	localSock.sin_family = AF_INET;
  localSock.sin_port = htons(iDestinationPort);
  localSock.sin_addr.s_addr = INADDR_ANY;

  if(::bind(iSocket, (struct sockaddr *)&localSock, sizeof(localSock)) == -1){
		IAS_THROW(SystemException()<<"UDP  socket (bind), port: "<<(int)iDestinationPort);
  }

}
/*************************************************************************/
bool Receiver::receive(void *pData, size_t iBufferLen, size_t& iDataSize, String& strSrcIP, int &iSrcPort){
	IAS_TRACER;

	ssize_t iResult = 0;


  struct sockaddr_storage srcAddress;
  socklen_t iAddressLen = sizeof(srcAddress);

	{
		Thread::Cancellation ca(true);
		if(iTimeout != 0)
			if(!waitForData(WM_Read)){
				iDataSize = 0;
				return false;
		}


		iResult = ::recvfrom(iSocket, pData, iBufferLen, 0, (struct sockaddr*)&srcAddress, &iAddressLen);
	}

  // TODO class ipAddress or at least conversions.

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
}
}
}
