/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/StreamInput.cpp
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

#include "StreamInput.h"
#include <commonlib/logger/logger.h>

#include <string.h>

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
StreamInput::StreamInput(const EndPoint& endPoint,
			 	      	IndexType iBufferSize,
					  	IndexType iMaxPacketSize,
					  	Allocator* ma):
	StreamBufferBase(endPoint, iBufferSize, iMaxPacketSize, ma),
	receiver(endPoint.getPort()),
	sender(endPoint.getPort() + 1),
	iAvailable(0),
	pNetwork(NULL),
	pReader(NULL){
	IAS_TRACER;

	pNetwork = pBufferStart;
	pReader  = pBufferStart;

	phcThreads.addPointer(
		IAS_DFT_FACTORY<NetWorker>::Create(this)
	);
}
/*************************************************************************/
StreamInput::~StreamInput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StreamInput::setup(){
	
	sender.setup(endPoint.getInterface(), endPoint.getGroup());
	receiver.bind();
	receiver.subscribe(endPoint.getInterface(), endPoint.getGroup());

	IAS_LOG(true,"SequencerInput is ready: "<<endPoint);
}
/*************************************************************************/
void StreamInput::readNext(void*& pNewDataRef, size_t& iDataLen){
	IAS_TRACER;

	Mutex::Locker locker(mutex);
	
	while(iAvailable == 0){
		Thread::Cancellation ca(true);
		mutex.wait(cndEmpty);
	}

	pNewDataRef = pReader;

	if(pReader < pNetwork){
		iDataLen = pNetwork - pReader;
		pReader  = pNetwork;
	}else{
		iDataLen = pBufferEnd - pReader;
		pReader  = pBufferStart;
	}
	
	iAvailable -= iDataLen;

	cndFull.signal();
}
/*************************************************************************/
void StreamInput::fetchFromNet(){

{
	Mutex::Locker locker(mutex);
	
	while(iAvailable > iBufferSize - iMaxPacketSize){
		Thread::Cancellation ca(true);
		mutex.wait(cndFull);
	}
}

	size_t iDataLen;
	receiver.receive(pNetwork, iMaxPacketSize, iDataLen); // TOOD pTmpNet and release lock here
	//TODO if(packet offset is ok)

	
	if(pNetwork >= pBufferEnd){
		if(pNetwork > pBufferEnd){
			memcpy(pBufferStart, pBufferEnd, pNetwork - pBufferEnd);
		}
		pNetwork = pBufferStart;
	}

	Mutex::Locker locker(mutex);

	//TODO if(packet offset is ok)
	iAvailable += iDataLen;
	pNetwork += iDataLen;

	cndEmpty.signal();
}
/*************************************************************************/
void StreamInput::NetWorker::run(){
	IAS_TRACER;
	
	while( !SYS::Signal::GetInstance()->isStopping() ){
		pStreamInput->fetchFromNet(); 
	}
}
/*************************************************************************/
}
}
}
