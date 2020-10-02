/*
 * File: SequencedBase.h
 *
 * Copyright (C) 2015, Albert Krzymowski
 *

 */


#ifndef _IAS_Net_MCast_SequencedBase_H_
#define _IAS_Net_MCast_SequencedBase_H_

#include <commonlib/types.h>
#include <commonlib/memory/memory.h>
#include <commonlib/logger/logger.h>
#include <commonlib/threads/Mutex.h>
#include <commonlib/threads/Condition.h>

#include "EndPoint.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The SequencedBase class.
 *
 */

class SequencedBase {
public:

	virtual ~SequencedBase() throw();

	typedef size_t       IndexType;
	typedef size_t       PacketSizeType;

protected:
	SequencedBase(const EndPoint& endPoint);
	EndPoint        endPoint;

	friend class Factory<SequencedBase>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedBase_H_ */
