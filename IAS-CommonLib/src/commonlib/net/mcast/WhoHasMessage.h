/*
 * File: WhoHasMessage.h
 *
 * Copyright (C) 2015, Albert Krzymowski
 *

 */


#ifndef _IAS_Net_MCast_WhoHasMessage_H_
#define _IAS_Net_MCast_WhoHasMessage_H_

#include <commonlib/types.h>
#include <commonlib/memory/memory.h>
#include <commonlib/logger/logger.h>

#include "EndPoint.h"
#include "SequencedBase.h"
namespace IAS {
namespace Net {
namespace MCast {

class Sender;
class Receiver;
/*************************************************************************/
/** The WhoHasMessage class.
 *
 */

struct WhoHasMessage {

    WhoHasMessage();

    WhoHasMessage(SequencedBase::IndexType iStartSequence,
		              SequencedBase::IndexType iEndSequence);

		SequencedBase::IndexType iStartSequence;
		SequencedBase::IndexType iEndSequence;

    void send(Sender& sender);
    void receive(Receiver& receiver);
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_WhoHasMessage_H_ */
