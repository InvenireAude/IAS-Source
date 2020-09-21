/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/StreamBufferBase.cpp
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

#include "StreamBufferBase.h"
#include <commonlib/logger/logger.h>


namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
StreamBufferBase::StreamBufferBase(const EndPoint& endPoint,
			 	      			   IndexType iBufferSize,
					  			   IndexType iMaxPacketSize,
					  			   Allocator* ma):
	endPoint(endPoint),
	iBufferSize(iBufferSize),
	iMaxPacketSize(iMaxPacketSize),
	ma(ma){
	IAS_TRACER;

	pBufferStart = (BufferPtr) ma->allocate(iBufferSize + iMaxPacketSize);
	pBufferEnd   = pBufferStart + iBufferSize;
}
/*************************************************************************/
StreamBufferBase::~StreamBufferBase() throw(){
	IAS_TRACER;

	stopWorkers();
}
/*************************************************************************/
void  StreamBufferBase::startWorkers(){
	IAS_TRACER;
	for(ThreadCollection::iterator it = phcThreads.begin();
      it != phcThreads.end(); ++it){
        (*it)->start();
      }


}
/*************************************************************************/
void StreamBufferBase:: stopWorkers(){
	IAS_TRACER;
	
	for(ThreadCollection::iterator it = phcThreads.begin();
      it != phcThreads.end(); ++it){
        (*it)->stop();
	}

	for(ThreadCollection::iterator it = phcThreads.begin();
		it != phcThreads.end(); it++){
		(*it)->join();
	}
}
/*************************************************************************/
}
}
}
