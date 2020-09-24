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
	sender(endPoint.getPort()){
	IAS_TRACER;

	pWriter = tabBuffer + (iSequence % iBufferSize);
}
/*************************************************************************/
SequencedOutput::~SequencedOutput() throw(){
	IAS_TRACER;
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
void* SequencedOutput::next(){
	return pWriter->pPacket;
}
/*************************************************************************/
void  SequencedOutput::commit(PacketSizeType iSize){

	Mutex::Locker locker(Mutex);

	pWriter->iSize = iSize;
	pWriter->setSequence(iSequence);


	sender.send(pWriter->pPacket, pWriter->iSize + sizeof(IndexType));

	if(++pWriter >= pBufferEnd)
		pWriter = tabBuffer;

	iSequence++;
}
/*************************************************************************/
void SequencedOutput::serveWhoHas(const WhoHasMessage& message){
	IAS_TRACER;

	{

		Mutex::Locker locker(Mutex);

		if(message.iStartSequence + iBufferSize < iSequence )
			return;
	}

	IndexType iDataLeft  = message.iEndSequence - message.iStartSequence;
	WireData* pCursor    = tabBuffer + (message.iStartSequence % iBufferSize);
  IndexType iMsgSequence = message.iStartSequence;

	while(iDataLeft-- > 0){

		Mutex::Locker locker(Mutex);

    if(pCursor->getSequence() == iMsgSequence++){
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
}

/*************************************************************************/
}
}
}
