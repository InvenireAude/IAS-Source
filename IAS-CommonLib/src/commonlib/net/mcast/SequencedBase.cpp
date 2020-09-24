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
  iMaxPacketSize(iMaxPacketSize),
	iSequence(0){
	IAS_TRACER;

	tabBuffer = IAS_DFT_STATIC_FACTORY<WireData>().allocate(iBufferSize);
 	WireData *pWireData = tabBuffer;

	for(int iIdx = 0; iIdx < iBufferSize; iIdx++, pWireData++){
		pWireData->pPacket = pAllocator->allocate(iMaxPacketSize + sizeof(IndexType));
		pWireData->iSize   = 0;
	}

	pBufferEnd = tabBuffer + iBufferSize;
}
/*************************************************************************/
SequencedBase::~SequencedBase() throw(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Last sequence: "<<iSequence);
}
/*************************************************************************/
}
}
}
