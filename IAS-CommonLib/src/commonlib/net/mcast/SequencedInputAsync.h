/*
 * File: SequencedInputAsync.h
 *
 * Copyright (C) 2015, Albert Krzymowski
 *

 */


#ifndef _IAS_Net_MCast_SequencedInputAsync_H_
#define _IAS_Net_MCast_SequencedInputAsync_H_

#include <commonlib/threads/Thread.h>
#include <commonlib/threads/Runnable.h>

#include "SequencedInput.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The SequencedInputAsync class.
 *
 */
class SequencedInputAsync : public SequencedInput {
public:

	virtual ~SequencedInputAsync() throw();

	void setup();
	const WireData& next();

protected:
	SequencedInputAsync( const EndPoint& endPoint,
			 	               IndexType      iBufferSize,
                       PacketSizeType iMaxPacketSize,
                       Allocator     *pAllocator);


	class NetworkWorker : public Thread, public Runnable {

		virtual void run();

		protected:
			NetworkWorker(SequencedInputAsync* pSequencedInputAsync):
				pSequencedInputAsync(pSequencedInputAsync),
				Thread(this){}

		SequencedInputAsync* pSequencedInputAsync;
		friend class Factory<NetworkWorker>;
	};

  void serveNetwork();

  Condition cndFull;
  Condition cndEmpty;

  IndexType iAvailable;
  WireData  *pReader;

  IAS_DFT_FACTORY<Thread>::PtrHolder ptrNetworkWorker;

	friend class Factory<SequencedInputAsync>;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedInputAsync_H_ */
