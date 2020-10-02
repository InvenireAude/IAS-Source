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

#include "SequencedBuffer.h"
#include "SequencedFailoverListener.h"

#include "Receiver.h"
#include "Sender.h"

using namespace IAS;

namespace IAS {
namespace Net {
namespace MCast {

class WhoHasMessage;

/*************************************************************************/
/** The SequencedOutput class.
 *
 */
class SequencedOutput :
public SequencedBuffer,
public SequencedFailoverListener::Callback {
public:

	virtual ~SequencedOutput() throw();


	void send(void* pPacket, PacketSizeType iSize);

	void setup();
	void startRepeater();
	void stopRepeater();

  void setMute(bool bMuted);

  virtual void failover(IndexType iStartSequence);

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
  bool bMuted;

	IAS_DFT_FACTORY<Thread>::PtrHolder ptrNetRepeaterThread;
	void serveWhoHas(const WhoHasMessage& message);

	friend class Factory<SequencedOutput>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedOutput_H_ */
