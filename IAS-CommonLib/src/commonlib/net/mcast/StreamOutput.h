/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/StreamOutput.h
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

#ifndef _IAS_Net_Bus_StreamOutput_H_
#define _IAS_Net_Bus_StreamOutput_H_

#include "StreamBufferBase.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The StreamOutput class.
 *
 */
class StreamOutput : public StreamBufferBase {
public:

	virtual ~StreamOutput() throw();

	void* nextPacket();
	void  commit(unsigned int iSize);

	void setup();

protected:

	StreamOutput( const EndPoint& endPoint,
			 	 IndexType iBufferSize = CDftBufferSize,
				 IndexType iMaxPacketSize = CDftMaxPacketSize,
				 Allocator* ma = MemoryManager::GetAllocator());

	void sendToNet();

	class NetWorker : public Thread, public Runnable {

		virtual void run();

		protected:
			NetWorker(StreamOutput* pStreamOutput):
				pStreamOutput(pStreamOutput),
				Thread(this){}

		StreamOutput* pStreamOutput;
		friend class Factory<NetWorker>;
	};


	Sender    sender;
	Receiver  receiver;

	BufferPtr  pNetwork;
	BufferPtr  pWriter;
	
	IndexType  iPending; 

	friend class Factory<StreamOutput>;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Bus_StreamOutput_H_ */
