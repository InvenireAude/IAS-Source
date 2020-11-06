/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/Client.cpp
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

#include "Client.h"

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
Client::Client(unsigned int iDestinationPort, unsigned int iSourcePort):
	Socket(iDestinationPort){
	IAS_TRACER;

	// int size = 1000 * 1024 * 1024;

	// if (setsockopt(iSocket, SOL_SOCKET, SO_RCVBUF, &size, (socklen_t)sizeof(int)) < 0)
  // 	IAS_THROW(SystemException()<<"UDP mulitcast socket (SO_RCVBUF), port: "<<(int)iDestinationPort);

	int reuse = 1;

  if (setsockopt(iSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
   	IAS_THROW(SystemException()<<"UDP socket (SO_REUSEADDR), port: "<<(int)iDestinationPort);

  Socket::bind(iSourcePort);
}
/*************************************************************************/
Client::~Client() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool Client::receive(void *pData, size_t iBufferLen, size_t& iDataSize){
  String strSrcIP;
  int    iSrcPort;
  return Socket::receive(pData, iBufferLen, iDataSize, strSrcIP, iSrcPort);
}
/*************************************************************************/
void Client::setup(const String& strSourceIP, const String& strDestinationIP){
	IAS_TRACER;

	struct in_addr localSourceIP;
  localSourceIP.s_addr = inet_addr(strSourceIP.c_str());

	destSockAddr.sin_family = AF_INET;
  destSockAddr.sin_addr.s_addr = inet_addr(strDestinationIP.c_str());
  destSockAddr.sin_port = htons(iDestinationPort);

}
/*************************************************************************/
void Client::send(const void *pData, size_t iDataSize){
	IAS_TRACER;
	size_t iWritten;

  Socket::send(destSockAddr, pData, iDataSize, iWritten);

	if(iWritten != iDataSize){
		IAS_THROW(SystemException("Client::send(), iWritten != iDataSize"));
	}
}
/*************************************************************************/
}
}
}
