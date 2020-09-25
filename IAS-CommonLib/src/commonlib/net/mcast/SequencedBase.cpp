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
			 	                     IndexType      iBufferSize,
                             PacketSizeType iMaxPacketSize,
                             Allocator     *pAllocator):
	endPoint(endPoint),
	pAllocator(pAllocator),
  iBufferSize(iBufferSize),
  iMaxPacketSize(iMaxPacketSize){
	IAS_TRACER;

	tabBuffer = IAS_DFT_STATIC_FACTORY<WireData>().allocate(iBufferSize);
 	WireData *pWireData = tabBuffer;

	for(int iIdx = 0; iIdx < iBufferSize; iIdx++, pWireData++){
		pWireData->pPacket = allocatePacket();
		pWireData->iSize   = 0;
	}

	pBufferEnd = tabBuffer + iBufferSize;
}
/*************************************************************************/
SequencedBase::~SequencedBase() throw(){
	IAS_TRACER;

   WireData *pWireData = tabBuffer;
  for(int iIdx = 0; iIdx < iBufferSize; iIdx++, pWireData++){
		pWireData->unset(pAllocator);
	}
}
/*************************************************************************/
void *SequencedBase::allocatePacket(){
	IAS_TRACER;
  return pAllocator->allocate(iMaxPacketSize + sizeof(IndexType));
}
/*************************************************************************/
}
}
}
