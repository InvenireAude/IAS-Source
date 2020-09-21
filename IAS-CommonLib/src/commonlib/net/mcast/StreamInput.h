/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/StreamInput.h
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

#ifndef _IAS_Net_Bus_StreamInput_H_
#define _IAS_Net_Bus_StreamInput_H_

#include "StreamBufferBase.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The StreamInput class.
 *
 */
class StreamInput : public StreamBufferBase {
public:

	virtual ~StreamInput() throw();

	void readNext(void*& pNewDataRef, size_t& iDataLen);

	void setup();

	void fetchFromNet();

protected:


	StreamInput( const EndPoint& endPoint,
			 	 IndexType iBufferSize = CDftBufferSize,
				 IndexType iMaxPacketSize = CDftMaxPacketSize,
				 Allocator* ma = MemoryManager::GetAllocator());

	class NetWorker : public Thread, public Runnable {

		virtual void run();

		protected:
			NetWorker(StreamInput* pStreamInput):
				pStreamInput(pStreamInput),
				Thread(this){}

		StreamInput* pStreamInput;
		friend class Factory<NetWorker>;
	};

	Sender    sender;
	Receiver  receiver;

	BufferPtr  pNetwork;
	BufferPtr  pReader;
	
	IndexType  iAvailable; 

	friend class Factory<StreamInput>;

};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Bus_StreamInput_H_ */
