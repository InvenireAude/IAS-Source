/*
 * File: SequencedInput.h
 *
 * Copyright (C) 2015, Albert Krzymowski
 *

 */


#ifndef _IAS_Net_MCast_SequencedInput_H_
#define _IAS_Net_MCast_SequencedInput_H_

#include "SequencedBuffer.h"
#include "Receiver.h"
#include "Sender.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The SequencedInput class.
 *
 */
class SequencedInput : public SequencedBuffer {
public:

	virtual ~SequencedInput() throw();

	void* receive(PacketSizeType& iDataSize);

  template<class C>
   inline C* receive(PacketSizeType& iDataSize){
      return reinterpret_cast<C*>(receive(iDataSize));
    }

	void setup(IndexType iForcedSequence = 0);

protected:
	SequencedInput( const EndPoint& endPoint,
			 	          IndexType      iBufferSize,
                  Allocator     *pAllocator);

  IndexType iNetworkSequence;
	WireData  *pNetwork;

	Receiver receiver;
	Sender   sender;

	IndexType iWhoHasMax;

  void receiveFromNet(IndexType iMaxPrefetch);

	Mutex mutex;

	friend class Factory<SequencedInput>;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedInput_H_ */
