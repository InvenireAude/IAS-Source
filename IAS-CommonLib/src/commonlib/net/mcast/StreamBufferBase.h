/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/StreamBufferBase.h
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

#ifndef _IAS_Net_Bus_StreamBufferBase_H_
#define _IAS_Net_Bus_StreamBufferBase_H_

#include <commonlib/types.h>
#include <commonlib/memory/memory.h>
#include <commonlib/threads/Mutex.h>
#include <commonlib/threads/Thread.h>
#include <commonlib/threads/Runnable.h>
#include <commonlib/threads/Condition.h>

#include "EndPoint.h"

#include "Receiver.h"
#include "Sender.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The StreamBufferBase class.
 *
 */
class StreamBufferBase {
public:

	virtual ~StreamBufferBase() throw();

	void startWorkers();
	void stopWorkers();

	const EndPoint& getEndPoint()const{
		return endPoint;
	}

	typedef size_t IndexType;

	static const IndexType CDftMaxPacketSize = 4096;
	static const IndexType CDftBufferSize    = 256*4096;

protected:


	StreamBufferBase( const EndPoint& endPoint,
			 	      IndexType iBufferSize = CDftBufferSize,
					  IndexType iMaxPacketSize = CDftMaxPacketSize,
					  Allocator* ma = MemoryManager::GetAllocator());


	EndPoint endPoint;

	IndexType iBufferSize;
	IndexType iMaxPacketSize;

	typedef unsigned char* BufferPtr;

	BufferPtr             pBufferStart;
	BufferPtr             pBufferEnd;
	
	Allocator* ma;
	
	typedef IAS_DFT_FACTORY<Thread>::PtrHoldersCollection ThreadCollection;
	ThreadCollection phcThreads;

	Mutex      mutex;
	Condition  cndEmpty;
	Condition  cndFull;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Bus_StreamBufferBase_H_ */
