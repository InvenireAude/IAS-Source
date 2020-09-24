/*
 * File: SequencedInput.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 */

#include "SequencedInput.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
SequencedInput::SequencedInput( const EndPoint& endPoint,
			 	                        IndexType      iBufferSize,
                                PacketSizeType iMaxPacketSize,
                                Allocator     *pAllocator):
	SequencedBase(endPoint, iBufferSize, iMaxPacketSize, pAllocator),
	receiver(endPoint.getPort()),
	sender(endPoint.getPort() + 1),
	iWhoHasCount(0){
	IAS_TRACER;
	pNetwork = tabBuffer + (iSequence % iBufferSize);
	iWhoHasMax = iSequence;
}
/*************************************************************************/
SequencedInput::~SequencedInput() throw(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"iWhoHasCount: "<<iWhoHasCount);
}
/*************************************************************************/
void SequencedInput::setup(){

	sender.setup(endPoint.getInterface(), endPoint.getGroup());
	receiver.bind();
	receiver.subscribe(endPoint.getInterface(), endPoint.getGroup());

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"SequencedInput is ready: "<<endPoint);
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "SequencedOutput is ready: "<<iBufferSize);
}
/*************************************************************************/
void SequencedInput::receiveFromNet(IndexType iMaxPrefetch){
  IAS_TRACER;

	  if(iWhoHasMax < iSequence)
  		  iWhoHasMax = iSequence;

    size_t iNetDataLen;

		receiver.receive(pNetwork->pPacket,
						 iMaxPacketSize + sizeof(IndexType),
						 iNetDataLen);

		pNetwork->iSize = iNetDataLen - sizeof(IndexType);

		IndexType iMsgSequence = pNetwork->getSequence();

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "Received! expected: "<<iSequence<<", got: "<<iMsgSequence);

		if(iMsgSequence > iSequence && iMsgSequence < iSequence + iMaxPrefetch){

			pNetwork->swap(tabBuffer[ iMsgSequence  % iBufferSize ]);

      IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "Swaping: "<<iSequence<<", with "<<(iMsgSequence  % iBufferSize));

      pNetwork->setSequence(-1);

			if(iMsgSequence > iWhoHasMax){
				sendWhoHas(iWhoHasMax, iMsgSequence);
				iWhoHasMax = iMsgSequence;
			}
    }

}
/*************************************************************************/
const SequencedBase::WireData& SequencedInput::next(){
	IAS_TRACER;

  Mutex::Locker locker(mutex);

	while(!pNetwork->hasData() || pNetwork->getSequence() != iSequence){
      receiveFromNet(iBufferSize);
	}

	iSequence++;

	WireData *pResult = pNetwork;

	if(++pNetwork >= pBufferEnd){
		pNetwork = tabBuffer;
	}

	return *pResult;
}
/*************************************************************************/
void SequencedInput::sendWhoHas(IndexType iStartSequence, IndexType iEndSequence){
	WhoHasMessage message;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "Sending WhoHas? "<<iStartSequence<<", got: "<<iEndSequence);

	iWhoHasCount++;

	message.iStartSequence = iSequence;
	message.iEndSequence   = iEndSequence;

	sender.send(&message, sizeof(WhoHasMessage));
}
/*************************************************************************/
}
}
}
