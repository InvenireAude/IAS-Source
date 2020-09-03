/*
 * File: IAS-CommonLib/src/commonlib/net/TCPConnectionBase.cpp
 * 
 * Copyright (C) 2015, Albert Krzymowski
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
#include "TCPConnectionBase.h"

#include <commonlib/logger/logger.h>
#include <commonlib/exception/SystemException.h>

#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <netinet/tcp.h>


namespace IAS {
namespace Net {

/*************************************************************************/
TCPConnectionBase::TCPConnectionBase():
 bNoDelay(false){
	IAS_TRACER;
}
/*************************************************************************/
TCPConnectionBase::TCPConnectionBase(const Peer& peerLocal):peerLocal(peerLocal){
	IAS_TRACER;
}
/*************************************************************************/
TCPConnectionBase::~TCPConnectionBase() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCPConnectionBase::setNoDelay(bool bValue){
	this->bNoDelay = bValue;
}
/*************************************************************************/
void TCPConnectionBase::setNoDelayImpl(int iSocket, bool bValue)const{
	IAS_TRACER;

	int optval = bValue  ? 1 : 0;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "setNoDelay("<<optval<<")");

	int rc = setsockopt(iSocket, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval);
	
	if(rc < 0)
		IAS_THROW(SystemException("setNoDelay(...) failed."));

}
/*************************************************************************/
}
}
