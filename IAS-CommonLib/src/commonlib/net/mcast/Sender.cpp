/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/Sender.cpp
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

#include "Sender.h"

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
namespace MCast {

/*************************************************************************/
Sender::Sender(unsigned int iPort):
	Base(iPort){
	IAS_TRACER;
}
/*************************************************************************/
Sender::~Sender() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Sender::setup(const String& strInterface, const String& strGroup){
	IAS_TRACER;
	
	struct in_addr localInterface;
    localInterface.s_addr = inet_addr(strInterface.c_str());

    if (setsockopt(iSocket, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0){
       IAS_THROW(SystemException()<<"UDP mulitcast socket (IP_MULTICAST_IF), port: "<<(int)iPort);
    }

	groupSock.sin_family = AF_INET;
    groupSock.sin_addr.s_addr = inet_addr(strGroup.c_str());
    groupSock.sin_port = htons(iPort);

}
/*************************************************************************/
void Sender::send(const void *pData, size_t iDataSize, size_t& iWritten){
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
		iResult = ::sendto(iSocket, pData, iDataSize, 0, (struct sockaddr *)&groupSock, sizeof(groupSock));
	}

	if(iResult < 0){
		IAS_LOG(LogLevel::INSTANCE.isError(),"SEND:"<<(void*)pData<<"len="<<iDataSize);
		IAS_THROW(SystemException("read",errno));
	}

	iWritten = iResult;
}
/*************************************************************************/
void Sender::send(const void *pData, size_t iDataSize){
	IAS_TRACER;
	size_t iWritten;
	Sender::send(pData, iDataSize, iWritten);

	if(iWritten != iDataSize){
		IAS_THROW(SystemException("Sender::send(), iWritten != iDataSize"));
	}
}
/*************************************************************************/
}
}
}
