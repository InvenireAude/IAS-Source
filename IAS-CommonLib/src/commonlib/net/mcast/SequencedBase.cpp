/*
 * File: SequencedBase.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 */

#include "SequencedBase.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
SequencedBase::SequencedBase(const EndPoint& endPoint,
                             Allocator     *pAllocator):
	endPoint(endPoint),
  pAllocator(pAllocator){}
/*************************************************************************/
SequencedBase::~SequencedBase() throw(){}
/*************************************************************************/
void *SequencedBase::allocatePacket(){
	IAS_TRACER;
  return pAllocator->allocate(endPoint.getMaxPacketSize());
}
/*************************************************************************/
}
}
}
