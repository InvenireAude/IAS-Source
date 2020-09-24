/*
 * File: SequencedInputAsync.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 */

#include "SequencedInputAsync.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
SequencedInputAsync::SequencedInputAsync( const EndPoint& endPoint,
			 	                        IndexType      iBufferSize,
                                PacketSizeType iMaxPacketSize,
                                Allocator     *pAllocator):
	SequencedInput(endPoint, iBufferSize, iMaxPacketSize, pAllocator){
	IAS_TRACER;

  pReader = tabBuffer;
  iAvailable = 0;
}
/*************************************************************************/
SequencedInputAsync::~SequencedInputAsync() throw(){

  ptrNetworkWorker->stop();
  ptrNetworkWorker->join();

}
/*************************************************************************/
void SequencedInputAsync::setup(){
  SequencedInput::setup();

  ptrNetworkWorker = IAS_DFT_FACTORY<NetworkWorker>::Create(this);
  ptrNetworkWorker->start();

}
/*************************************************************************/
const SequencedBase::WireData& SequencedInputAsync::next(){
  IAS_TRACER;

   Mutex::Locker locker(mutex);

   while(iAvailable == 0){
     Thread::Cancellation ca(true);
     mutex.wait(cndEmpty);
   }

  WireData *pResult = pNetwork;

	if(++pReader >= pBufferEnd){
		pReader = tabBuffer;
	}

  cndFull.signal();
  iAvailable--;

	return *pResult;
}
/*************************************************************************/
void SequencedInputAsync::serveNetwork(){
	IAS_TRACER;

  Mutex::Locker locker(mutex);

  while(iAvailable > iBufferSize){
     Thread::Cancellation ca(true);
     mutex.wait(cndFull);
   }

	if(!pNetwork->hasData() || pNetwork->getSequence() != iSequence){

    receiveFromNet(iBufferSize - iAvailable);

	}else{

  	iSequence++;

    if(++pNetwork >= pBufferEnd){
		  pNetwork = tabBuffer;
	  }

  }

}
/*************************************************************************/
void SequencedInputAsync::NetworkWorker::run(){
	IAS_TRACER;

	while( !SYS::Signal::GetInstance()->isStopping() ){
    pSequencedInputAsync->serveNetwork();
	}
}
/*************************************************************************/
}
}
}
