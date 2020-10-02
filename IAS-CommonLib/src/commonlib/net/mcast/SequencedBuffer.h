/*
 * File: SequencedBuffer.h
 *
 * Copyright (C) 2015, Albert Krzymowski
 *

 */


#ifndef _IAS_Net_MCast_SequencedBuffer_H_
#define _IAS_Net_MCast_SequencedBuffer_H_

#include <commonlib/types.h>
#include <commonlib/memory/memory.h>
#include <commonlib/logger/logger.h>
#include <commonlib/threads/Mutex.h>
#include <commonlib/threads/Condition.h>

#include "SequencedBase.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The SequencedBuffer class.
 *
 */

class SequencedBuffer : public SequencedBase {
public:

	virtual ~SequencedBuffer() throw();

protected:
	SequencedBuffer(const EndPoint& endPoint,
			 	        IndexType      iBufferSize,
                Allocator     *pAllocator);

	IndexType       iBufferSize;

	IAS_DFT_STATIC_FACTORY<WireData>::PtrHolder  tabBuffer;
	WireData                                   *pBufferEnd;

	friend class Factory<SequencedBuffer>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedBuffer_H_ */
