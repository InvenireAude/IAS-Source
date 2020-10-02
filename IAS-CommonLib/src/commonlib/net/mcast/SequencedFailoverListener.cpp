/*
 * File: SequencedFailoverListener.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 */

#include "SequencedFailoverListener.h"

#include "WhoHasMessage.h"
namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
SequencedFailoverListener::SequencedFailoverListener(const EndPoint& endPoint,
                                                      Callback *pCallback,
                                                      IndexType       iLookAHead,
                                                      unsigned int    iTimeout):
	SequencedBase(endPoint,MemoryManager::GetAllocator()),
	receiver(endPoint.getPort()),
	sender(endPoint.getPort() + 1),
  iLookAHead(iLookAHead),
  iTimeout(iTimeout),
  pCallback(pCallback),
  iNetworkSequence(0){
	IAS_TRACER;
  IAS_CHECK_IF_NULL(pCallback);
}
/*************************************************************************/
SequencedFailoverListener::~SequencedFailoverListener() throw(){
	IAS_TRACER;

  if(ptrNetListenerThread){
		ptrNetListenerThread->stop();
		ptrNetListenerThread->join();
	}
}
/*************************************************************************/
void SequencedFailoverListener::setup(IndexType iForcedSequence){

  iNetworkSequence = iForcedSequence;

	sender.setup(endPoint.getInterface(), endPoint.getGroup());
	receiver.bind();
	receiver.subscribe(endPoint.getInterface(), endPoint.getGroup());

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "SequencedFailoverListener seq: "<<iNetworkSequence);
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "SequencedFailoverListener is ready: "<<endPoint);

  // TODO ? make optional method, e.g. force forceWhoHas(iRange = iBufferSize);
  // 10000 ?= buffer size ?

  WhoHasMessage message(iNetworkSequence,iNetworkSequence + 10000);
  message.send(sender);

	ptrNetListenerThread = IAS_DFT_FACTORY<NetListener>::Create(this);
	ptrNetListenerThread->start();

}
/*************************************************************************/
void SequencedFailoverListener::listen(){
  IAS_TRACER;

  WireDataHolder wd(pAllocator);

  wd.pPacket = allocatePacket();

  if(!receiver.receive(wd.pPacket, endPoint.getMaxPacketSize() + sizeof(IndexType), wd.iSize)){

      WhoHasMessage message(iNetworkSequence,iNetworkSequence + 1);
      message.send(sender);

      if(!receiver.receive(wd.pPacket, endPoint.getMaxPacketSize() + sizeof(IndexType), wd.iSize)){
        pCallback->failover(iNetworkSequence);
        ptrNetListenerThread->stop();
      }
  }

  //We wait some time for the very first data.
  receiver.setTimeout(iTimeout);

  if(wd.iSize <= sizeof(IndexType))
      return;

  wd.iSize -= sizeof(IndexType);

  IndexType iMsgSequence = wd.getSequence();

  IAS_LOG(LogLevel::INSTANCE.isInfo()||true, "Received! expected: "<<iNetworkSequence<<", got: "<<iMsgSequence);

  if(iMsgSequence > iNetworkSequence)
    iNetworkSequence = iMsgSequence;

  iNetworkSequence++;
}
/*************************************************************************/
void SequencedFailoverListener::NetListener::run(){
	IAS_TRACER;

	while( !SYS::Signal::GetInstance()->isStopping() ){
    pListener->listen();
	}

}
/*************************************************************************/
}
}
}
