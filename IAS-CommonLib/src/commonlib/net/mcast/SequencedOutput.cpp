/*
 * File: SequencedOutput.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 */

#include "SequencedOutput.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
SequencedOutput::SequencedOutput(const EndPoint& endPoint,
			 	                        IndexType      iBufferSize,
                                PacketSizeType iMaxPacketSize,
                                Allocator     *pAllocator):
	SequencedBase(endPoint, iBufferSize, iMaxPacketSize, pAllocator),
	receiver(endPoint.getPort() + 1),
	sender(endPoint.getPort()),
  iNetworkSequence(0),
  bMuted(false){
	IAS_TRACER;

	pNetwork = tabBuffer + (iNetworkSequence % iBufferSize);
}
/*************************************************************************/
SequencedOutput::~SequencedOutput() throw(){
	IAS_TRACER;
  stopRepeater();
}
/*************************************************************************/
void SequencedOutput::setup(){
	IAS_TRACER;

	sender.setup(endPoint.getInterface(), endPoint.getGroup());
	receiver.bind();
	receiver.subscribe(endPoint.getInterface(), endPoint.getGroup());

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "SequencedOutput is ready: "<<endPoint);
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "SequencedOutput is ready: "<<iBufferSize);
}
/*************************************************************************/
void  SequencedOutput::send(void* pPacket, PacketSizeType iSize){

	Mutex::Locker locker(Mutex);

  pNetwork->pPacket = pPacket;
	pNetwork->iSize   = iSize;
	pNetwork->setSequence(iNetworkSequence);

  IAS_LOG(LogLevel::INSTANCE.isInfo(), "iNetworkSequence: "<<iNetworkSequence);

  if(!bMuted)
    sender.send(pNetwork->pPacket, pNetwork->iSize + sizeof(IndexType));

	if(++pNetwork >= pBufferEnd)
		pNetwork = tabBuffer;

	iNetworkSequence++;
}
/*************************************************************************/
void SequencedOutput::serveWhoHas(const WhoHasMessage& message){
	IAS_TRACER;

	{

		Mutex::Locker locker(Mutex);
    IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"X: "<<message.iStartSequence<<" "<<iBufferSize<<" "<<iNetworkSequence);

		if(message.iStartSequence + iBufferSize < iNetworkSequence )
			return;
	}

	IndexType iDataLeft  = message.iEndSequence - message.iStartSequence;
	WireData* pCursor    = tabBuffer + (message.iStartSequence % iBufferSize);
  IndexType iMsgSequence = message.iStartSequence;

	while(iDataLeft-- > 0){

    IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "Repeat: "<<iMsgSequence<<
        ", ptr:"<<pCursor->pPacket<<", size:"<<pCursor->iSize);

		Mutex::Locker locker(Mutex);

    if(pCursor->hasData() && pCursor->getSequence() == iMsgSequence++){
      sender.send(pCursor->pPacket, pCursor->iSize + sizeof(IndexType));
    }

		if(++pCursor > pBufferEnd){
      pCursor = tabBuffer;
    }


	}

}
/*************************************************************************/
void SequencedOutput::NetRepeater::run(){
	IAS_TRACER;

	while( !SYS::Signal::GetInstance()->isStopping() ){
		WhoHasMessage message;
		size_t iWritten;
		pSequencedOutput->receiver.receive(&message, sizeof(WhoHasMessage), iWritten);
		pSequencedOutput->serveWhoHas(message);
	}
}
/**************************************************************************/
void SequencedOutput::startRepeater(){
	IAS_TRACER;
	ptrNetRepeaterThread = IAS_DFT_FACTORY<NetRepeater>::Create(this);
	ptrNetRepeaterThread->start();
}
/**************************************************************************/
void SequencedOutput::stopRepeater(){
	IAS_TRACER;
	if(ptrNetRepeaterThread){
		ptrNetRepeaterThread->stop();
		ptrNetRepeaterThread->join();
	}

  ptrNetRepeaterThread = 0;
}
/*************************************************************************/
void  SequencedOutput::setMute(bool bMuted){
	Mutex::Locker locker(Mutex);
  this->bMuted = bMuted;
}
/*************************************************************************/
}
}
}
