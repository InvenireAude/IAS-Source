/*
 * File: WhoHasMessage.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 */

#include "WhoHasMessage.h"
#include "Sender.h"
#include "Receiver.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
WhoHasMessage::WhoHasMessage():
	iStartSequence(0),
	iEndSequence(0){}
/*************************************************************************/
WhoHasMessage::WhoHasMessage(SequencedBase::IndexType iStartSequence,
		                         SequencedBase::IndexType iEndSequence):
  iStartSequence(iStartSequence),
  iEndSequence(iEndSequence){
}
/*************************************************************************/
void WhoHasMessage::send(Sender& sender){

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "Sending WhoHas? "<<iStartSequence<<", got: "<<iEndSequence);
	sender.send(this, sizeof(WhoHasMessage));
}
/*************************************************************************/
void WhoHasMessage::receive(Receiver& receiver){
  size_t iWritten = 0;
  while(iWritten != sizeof(WhoHasMessage)){
    receiver.receive(this, sizeof(WhoHasMessage), iWritten);
  }
}
/*************************************************************************/
}
}
}
