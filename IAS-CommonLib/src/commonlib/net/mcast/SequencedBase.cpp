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
                             PacketSizeType iMaxPacketSize,
                             Allocator     *pAllocator):
	endPoint(endPoint),
  pAllocator(pAllocator),
  iMaxPacketSize(iMaxPacketSize){}
/*************************************************************************/
SequencedBase::~SequencedBase() throw(){}
/*************************************************************************/
void *SequencedBase::allocatePacket(){
	IAS_TRACER;
  return pAllocator->allocate(iMaxPacketSize);
}
/*************************************************************************/
}
}
}
