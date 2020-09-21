/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/StreamOutput.cpp
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

#include "StreamOutput.h"
#include <commonlib/logger/logger.h>

#include <string.h>

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
StreamOutput::StreamOutput(const EndPoint& endPoint,
			 	      			   IndexType iBufferSize,
					  			   IndexType iMaxPacketSize,
					  			   Allocator* ma):
	StreamBufferBase(endPoint, iBufferSize, iMaxPacketSize, ma),
	receiver(endPoint.getPort() + 1),
	sender(endPoint.getPort()),
	iPending(0),
	pNetwork(NULL),
	pWriter(NULL){
	IAS_TRACER;

	pNetwork = pBufferStart;
	pWriter  = pBufferStart;

	phcThreads.addPointer(
		IAS_DFT_FACTORY<NetWorker>::Create(this)
	);
}
/*************************************************************************/
StreamOutput::~StreamOutput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StreamOutput::setup(){

	sender.setup(endPoint.getInterface(), endPoint.getGroup());
	receiver.bind();
	receiver.subscribe(endPoint.getInterface(), endPoint.getGroup());
	
	IAS_LOG(true,"SequencerOutput is ready: "<<endPoint);
	IAS_LOG(true,"SequencerOutput is ready: "<<iBufferSize);
	IAS_LOG(true,"SequencerOutput is ready: "<<iMaxPacketSize);

}
/*************************************************************************/
void* StreamOutput::nextPacket(){	
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	while(iPending > iBufferSize - iMaxPacketSize){
		Thread::Cancellation ca(true);
		mutex.wait(cndFull);
	}

	return pWriter;
}
/*************************************************************************/	
void  StreamOutput::commit(unsigned int iSize){
	IAS_TRACER;

	if(iSize == 0)
		return;

	BufferPtr  pNextWriter = pWriter + iSize;

	if(pNextWriter >= pBufferEnd){

		if(pNextWriter > pBufferEnd){
			memcpy(pBufferStart, pBufferEnd, pNextWriter - pBufferEnd);
		}
		
		pNextWriter = pBufferStart;
	}

	Mutex::Locker locker(mutex);

	iPending += iSize;
	pWriter = pNextWriter;
	
	cndEmpty.signal();
}
/*************************************************************************/	
void  StreamOutput::sendToNet(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	while(iPending == 0){
		Thread::Cancellation ca(true);
		mutex.wait(cndEmpty);
	}

	size_t iPacketSize = iPending;
	
	if(iPacketSize > iMaxPacketSize)
		iPacketSize = iMaxPacketSize;

	if(pNetwork + iPacketSize > pBufferEnd)
		iPacketSize = pBufferEnd - pNetwork;

	size_t iWritten;
	
	sender.send(pNetwork, iPacketSize, iWritten); // TOOD pTmpNet and release lock here
	
	if(iWritten != iPacketSize){
		IAS_THROW(InternalException(" StreamOutput::sendToNet(), iWritten != iPacketSize"));
	}

	pNetwork +=iPacketSize;
	if(pNetwork > pBufferEnd){
		pNetwork = pBufferStart + (pNetwork - pBufferEnd);	
	}

	iPending -= iPacketSize;

	cndFull.signal();
}
/*************************************************************************/
void StreamOutput::NetWorker::run(){
	IAS_TRACER;
	
	while( !SYS::Signal::GetInstance()->isStopping() ){
		pStreamOutput->sendToNet();
	}
}
/*************************************************************************/	
}
}
}
