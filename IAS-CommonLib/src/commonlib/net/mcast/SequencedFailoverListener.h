/*
 * File: SequencedFailoverListener.h
 *
 * Copyright (C) 2015, Albert Krzymowski
 *

 */


#ifndef _IAS_Net_MCast_SequencedFailoverListener_H_
#define _IAS_Net_MCast_SequencedFailoverListener_H_

#include <commonlib/threads/Thread.h>
#include <commonlib/threads/Runnable.h>

#include "SequencedBase.h"
#include "Receiver.h"
#include "Sender.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The SequencedFailoverListener class.
 *
 */
class SequencedFailoverListener : public SequencedBase {
public:

  class Callback{
    public:
      virtual void failover(IndexType iStartSequence) = 0;
  };

	virtual ~SequencedFailoverListener() throw();

	void setup(IndexType iForcedSequence = 0);

protected:
	SequencedFailoverListener( const EndPoint& endPoint,
                             Callback *pCallback,
			 	                        IndexType       iLookAHead,
                                PacketSizeType iMaxPacketSize,
                                unsigned int    iTimeout);

  IndexType iNetworkSequence;
  IndexType       iLookAHead;
  Callback *pCallback;

	Receiver receiver;
	Sender   sender;

	class NetListener : public Thread, public Runnable {

		virtual void run();

		protected:
			NetListener(SequencedFailoverListener* pListener):
				pListener(pListener),
				Thread(this){}

		SequencedFailoverListener* pListener;
		friend class Factory<NetListener>;
	};

  void listen();

	Mutex mutex;
  unsigned int    iTimeout;

  IAS_DFT_FACTORY<Thread>::PtrHolder ptrNetListenerThread;

	friend class Factory<SequencedFailoverListener>;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedFailoverListener_H_ */
