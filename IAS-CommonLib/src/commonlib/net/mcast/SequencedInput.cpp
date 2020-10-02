/*
 * File: SequencedInput.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 */

#include "SequencedInput.h"

#include "WhoHasMessage.h"
namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
SequencedInput::SequencedInput( const EndPoint& endPoint,
			 	                        IndexType      iBufferSize,
                                PacketSizeType iMaxPacketSize,
                                Allocator     *pAllocator):
	SequencedBuffer(endPoint, iBufferSize, iMaxPacketSize, pAllocator),
	receiver(endPoint.getPort()),
	sender(endPoint.getPort() + 1),
  iNetworkSequence(0){
	IAS_TRACER;
	pNetwork = tabBuffer + (iNetworkSequence % iBufferSize);
	iWhoHasMax = iNetworkSequence;
}
/*************************************************************************/
SequencedInput::~SequencedInput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SequencedInput::setup(IndexType iForcedSequence){

  iNetworkSequence = iForcedSequence;
	pNetwork = tabBuffer + (iNetworkSequence % iBufferSize);
	iWhoHasMax = iNetworkSequence;

	sender.setup(endPoint.getInterface(), endPoint.getGroup());
	receiver.bind();
	receiver.subscribe(endPoint.getInterface(), endPoint.getGroup());

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "SequencedInput seq: "<<iNetworkSequence);
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "SequencedInput is ready: "<<endPoint);
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "SequencedOutput is ready: "<<iBufferSize);

  // TODO ? make optional method, e.g. force forceWhoHas(iRange = iBufferSize);
  WhoHasMessage message(iNetworkSequence,iNetworkSequence + iBufferSize);
  message.send(sender);

}
/*************************************************************************/
void SequencedInput::receiveFromNet(IndexType iMaxPrefetch){
  IAS_TRACER;

    if(iWhoHasMax < iNetworkSequence)
  		  iWhoHasMax = iNetworkSequence;

    WireDataHolder wd(pAllocator);

    wd.pPacket = allocatePacket();

		receiver.receive(wd.pPacket,
						         iMaxPacketSize + sizeof(IndexType),
						         wd.iSize);

    if(wd.iSize <= sizeof(IndexType))
        return;

		wd.iSize -= sizeof(IndexType);

		IndexType iMsgSequence = wd.getSequence();

		IAS_LOG(LogLevel::INSTANCE.isInfo(), "Received! expected: "<<iNetworkSequence<<", got: "<<iMsgSequence);

		if(iMsgSequence >= iNetworkSequence && iMsgSequence < iNetworkSequence + iMaxPrefetch){

      WireData *pTarget = tabBuffer + (iMsgSequence  % iBufferSize);

     // Mutex::Locker locker(mutex);

      if(!pTarget->hasData() || pTarget->getSequence() < iNetworkSequence){

        pTarget->unset(pAllocator);
        pTarget->set(wd.release(), wd.iSize);
        IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "Setting prefetch at: "<<(iMsgSequence  % iBufferSize));

			  if(iMsgSequence > iWhoHasMax){ //TODO do need lock for this
				    WhoHasMessage message(iNetworkSequence,iNetworkSequence + iBufferSize);
            message.send(sender);
				    iWhoHasMax = iMsgSequence;
			  }
      }
    }

}
/*************************************************************************/
void* SequencedInput::receive(PacketSizeType& iDataSize){
	IAS_TRACER;

   Mutex::Locker locker(mutex);

  while(!pNetwork->hasData() || pNetwork->getSequence() != iNetworkSequence){
       receiveFromNet(iBufferSize);
  }

	void *pData = pNetwork->pPacket;
  iDataSize = pNetwork->iSize;
  pNetwork->pPacket = NULL;
  pNetwork->iSize   = 0;

 	if(++pNetwork >= pBufferEnd){
	  	pNetwork = tabBuffer;
	  }

  ++iNetworkSequence;

  return pData;
}
/*************************************************************************/
}
}
}
