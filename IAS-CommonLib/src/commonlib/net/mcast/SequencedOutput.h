/*
 * File: SequencedOutput.h
 *
 * Copyright (C) 2015, Albert Krzymowski
 *

 */


#ifndef _IAS_Net_MCast_SequencedOutput_H_
#define _IAS_Net_MCast_SequencedOutput_H_

#include <commonlib/threads/Thread.h>
#include <commonlib/threads/Runnable.h>

#include "SequencedBase.h"
#include "Receiver.h"
#include "Sender.h"

using namespace IAS;

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The SequencedOutput class.
 *
 */
class SequencedOutput : public SequencedBase {
public:

	virtual ~SequencedOutput() throw();

 	void* next();
	void commit(PacketSizeType iSize);

	void setup();
	void startRepeater();
	void stopRepeater();

protected:
	SequencedOutput(const EndPoint& endPoint,
			 	          IndexType      iBufferSize,
                  PacketSizeType iMaxPacketSize,
                  Allocator     *pAllocator);

	class NetRepeater : public Thread, public Runnable {

		virtual void run();

		protected:
			NetRepeater(SequencedOutput* pSequencedOutput):
				pSequencedOutput(pSequencedOutput),
				Thread(this){}

		SequencedOutput* pSequencedOutput;
		friend class Factory<NetRepeater>;
	};

  IndexType iNetworkSequence;
	WireData *pNetwork;

	Receiver receiver;
	Sender   sender;

	Mutex mutex;

	IAS_DFT_FACTORY<Thread>::PtrHolder ptrNetRepeaterThread;
	void serveWhoHas(const WhoHasMessage& message);

	friend class Factory<SequencedOutput>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedOutput_H_ */
