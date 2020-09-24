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

	struct WireData{

		void            *pPacket;
		PacketSizeType  iSize;

		inline bool hasData()const{
			return iSize != 0;
		}

		void swap(WireData& other){
			WireData tmp;
			tmp = other;
			other.pPacket = this->pPacket;
			other.iSize   = this->iSize;
			this->pPacket = tmp.pPacket;
			this->iSize   = tmp.iSize;
		}

		inline IndexType getSequence()const{

			const IndexType *pSequence = reinterpret_cast<const IndexType*>(
				reinterpret_cast<const char*>(pPacket) + iSize);

			return *pSequence;
		}

		inline void setSequence(IndexType iSequence){

			IndexType *pSequence = reinterpret_cast<IndexType*>(
				reinterpret_cast<char*>(pPacket) + iSize);

			*pSequence = iSequence;
		}

	};

protected:
	SequencedBase(const EndPoint& endPoint,
			 	        IndexType      iBufferSize,
                PacketSizeType iMaxPacketSize,
                Allocator     *pAllocator);

	EndPoint endPoint;
	IndexType                 iBufferSize;

	IAS_DFT_STATIC_FACTORY<WireData>::PtrHolder  tabBuffer;
	WireData                                   *pBufferEnd;

	IndexType      iSequence;
  Allocator     *pAllocator;
  PacketSizeType iMaxPacketSize;

	struct WhoHasMessage{
		IndexType iStartSequence;
		IndexType iEndSequence;
	};

  protected:

	friend class Factory<SequencedBase>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedBase_H_ */
