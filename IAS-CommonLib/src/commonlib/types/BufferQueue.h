/*
 * File: IAS-CommonLib/src/commonlib/types/BufferQueue.h
 *
 * Copyright (C) 2020, Albert Krzymowski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _IAS_Types_BufferQueue_H_
#define _IAS_Types_BufferQueue_H_

#include <commonlib/types.h>
#include <commonlib/memory/memory.h>
#include <commonlib/exception/BadUsageException.h>

namespace IAS {

/*************************************************************************/
/** The BufferQueue class.
 *
 */
template<class C, class TA = IAS_DFT_FACTORY<C> >
class BufferQueue {

public:

  BufferQueue(C *pStart, size_t iLogSize):
    tabValues(pStart),
    iSize(0x1L << iLogSize ),
    iMask((0x1L << iLogSize) - 1),
    iNumItems(0),
    iHead(0){}

  BufferQueue(size_t iLogSize):
    iSize(0x1L << iLogSize),
    iMask((0x1L << iLogSize) - 1),
    iNumItems(0),
    iHead(0){
      TA a;
      tabValues = a.allocate(iSize);
    }

  static size_t ComputeMemoryRequirement(size_t iLogSize){
    return sizeof(C)*(0x1L << (iLogSize - 1));
  }
  const C& get(){

      if(iNumItems == 0)
        IAS_THROW(BadUsageException("BufferQueue: is empty."));

      const size_t iIdx = iHead;
      iHead = (iHead + 1) & iMask;
      iNumItems--;

      return tabValues[iIdx];
  }

  void put(const C& aValue){

    if(iNumItems == iSize)
      IAS_THROW(BadUsageException("BufferQueue: out of range."));
    
    tabValues[(iHead + iNumItems++) & iMask] = aValue;
  }
    
  void clear(){
    iHead = iNumItems = 0;
  }

  size_t size() const{
    return iNumItems;
  }

  bool empty() const{
    return iNumItems == 0;
  }

  bool full() const{
    return iNumItems == iSize;
  }

 protected:
  
  typedef C ItemType;
  C *tabValues;
  size_t iSize;
  size_t iHead;
  size_t iMask;
  size_t iNumItems;

};

/*************************************************************************/

}

#endif /* _IAS_Types_SortedHeap_H_ */
