/*
 * File: SequencedBuffer.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 */

#include "SequencedBuffer.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
SequencedBuffer::SequencedBuffer(const EndPoint& endPoint,
			 	                        IndexType      iBufferSize,
                                PacketSizeType iMaxPacketSize,
                                Allocator     *pAllocator):
	SequencedBase(endPoint, iMaxPacketSize, pAllocator),
  iBufferSize(iBufferSize){
	IAS_TRACER;

	tabBuffer = IAS_DFT_STATIC_FACTORY<WireData>().allocate(iBufferSize);
 	WireData *pWireData = tabBuffer;

	for(int iIdx = 0; iIdx < iBufferSize; iIdx++, pWireData++){
		pWireData->pPacket = 0;
		pWireData->iSize   = 0;
	}

	pBufferEnd = tabBuffer + iBufferSize;
}
/*************************************************************************/
SequencedBuffer::~SequencedBuffer() throw(){
	IAS_TRACER;

   WireData *pWireData = tabBuffer;
  for(int iIdx = 0; iIdx < iBufferSize; iIdx++, pWireData++){
		pWireData->unset(pAllocator);
	}
}
/*************************************************************************/
}
}
}
