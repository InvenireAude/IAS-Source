/*
 * File: SequencedInput.h
 *
 * Copyright (C) 2015, Albert Krzymowski
 *

 */


#ifndef _IAS_Net_MCast_SequencedInput_H_
#define _IAS_Net_MCast_SequencedInput_H_

#include "SequencedBase.h"
#include "Receiver.h"
#include "Sender.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The SequencedInput class.
 *
 */
class SequencedInput : public SequencedBase {
public:

	virtual ~SequencedInput() throw();

	const WireData& next();

	void setup();

protected:
	SequencedInput( const EndPoint& endPoint,
			 	          IndexType      iBufferSize,
                  PacketSizeType iMaxPacketSize,
                  Allocator     *pAllocator);

	WireData *pNetwork;

	Receiver receiver;
	Sender   sender;

	IndexType iWhoHasMax;
	size_t    iWhoHasCount;

  void receiveFromNet(IndexType iMaxPrefetch);

	void sendWhoHas(IndexType iStartSequence, IndexType iEndSequence);

	Mutex mutex;

	friend class Factory<SequencedInput>;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedInput_H_ */
