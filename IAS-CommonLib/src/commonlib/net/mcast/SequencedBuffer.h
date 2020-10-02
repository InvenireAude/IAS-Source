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
                PacketSizeType iMaxPacketSize,
                Allocator     *pAllocator);

	IndexType       iBufferSize;

  struct WireData{

    WireData():
      pPacket(NULL),
      iSize(0){}

		void            *pPacket;
		PacketSizeType  iSize;

    void unset(Allocator  *pAllocator){
      if(pPacket)
        pAllocator->free(pPacket);
    }

    void set(void* pPacket, PacketSizeType  iSize){
      this->pPacket = pPacket;
      this->iSize   = iSize;
    }

		inline bool hasData()const{
			return iSize != 0;
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

  struct WireDataHolder : public WireData {

    WireDataHolder(Allocator     *pAllocator):pAllocator(pAllocator){};
    ~WireDataHolder(){
        if(pPacket)
          pAllocator->free(pPacket);
      }

    void *release(){
      void *t = pPacket;
      pPacket = 0;
      return t;
    }

    Allocator     *pAllocator;
  };

	IAS_DFT_STATIC_FACTORY<WireData>::PtrHolder  tabBuffer;
	WireData                                   *pBufferEnd;

  Allocator     *pAllocator;
  PacketSizeType iMaxPacketSize;

  void *allocatePacket();

	friend class Factory<SequencedBuffer>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_SequencedBuffer_H_ */
