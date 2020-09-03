/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/FixedObjectPoolMemoryManager.cpp
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
#include "FixedObjectPoolMemoryManager.h"
#include "commonlib/exception/InternalException.h"

#include <commonlib/commonlib.h>
#include <new>
#include <string.h>
#include <strings.h>

namespace IAS {


/*************************************************************************/
FixedObjectPoolMemoryManager::FixedObjectPoolMemoryManager(
    void *pStart, size_t iObjectSize, size_t iNumObjects):
  bFreeMe(false){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Call for FOPMM: "<<iNumObjects<<" at: "<<pStart<<", size="<<iObjectSize<<" at="<<(void*)this);

  if(iObjectSize % sizeof(EntryIndex) != 0){
    IAS_THROW(InternalException("FixedObjectPoolMemoryManager object size error: ")<<iObjectSize<<" ? "<<sizeof(EntryIndex));
  }

  const size_t iTabSize =iObjectSize * iNumObjects;

  if(!pStart){

    pStart = new char[iTabSize];

    if(!pStart){
      IAS_LOG(LogLevel::INSTANCE.bIsError,"FixedObjectPoolMemoryManager cannot allocate memory.");
      throw std::bad_alloc();
    }

    bFreeMe = true;
  }

  pMemory = (EntryIndex*) pStart;

  this->iObjectSize = iObjectSize;
  this->iNumObjects = iNumObjects;

  for(EntryIndex iIdx = 0; iIdx < iNumObjects - 1; iIdx++){
    indexEntry(iIdx) =  iIdx + 1;
  }
  indexEntry(iNumObjects - 1) = CUnusedIndex;

  iTop = 0;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"FOPMM is ready !");

}
/*************************************************************************/
void* FixedObjectPoolMemoryManager::allocate(size_t n){

  if(n != iObjectSize){
    IAS_LOG(LogLevel::INSTANCE.bIsError,"(FOPMM) Bad memory allocation request, got: "<<n<<" bytes, expected: "<<iObjectSize<<".");
    throw std::bad_alloc();
  }

  if(iTop == CUnusedIndex){
    IAS_LOG(LogLevel::INSTANCE.bIsError,"FixedObjectPoolMemoryManager is out of memory.");
    throw std::bad_alloc();
  }

	Mutex::Locker locker(mutex, tsrMutexWaits);
	AutoTimeSample sample(tsrAllocations,LogLevel::INSTANCE.isProfile());

  void *pResult = &(indexEntry(iTop));
  iTop = indexEntry(iTop);
	return pResult;
}
/*************************************************************************/
inline bool FixedObjectPoolMemoryManager::isPointerSane(const void *p) const{
		bool bResult = p >= pMemory &&
		   p < (unsigned char*)pMemory + iObjectSize * iNumObjects &&
           ((long long)p) % iObjectSize == 0;

		if(!bResult){
			IAS_LOG(LogLevel::INSTANCE.bIsError,"FixedObjectPoolMemoryManager pointer error: "
				<<p<<" "
				<<((unsigned char*)p - (unsigned char*)pMemory)
				<<", iObjectSize: "<<iObjectSize<<", iNumObjects: "<<iNumObjects);
		}

		return bResult;
  	}
/*************************************************************************/
void  FixedObjectPoolMemoryManager::free(const void* p){

  if(!isPointerSane(p)){
   throw std::bad_alloc();
  }

	EntryIndex iReturned = ((unsigned char*)p - (unsigned char*)pMemory)/iObjectSize;

  Mutex::Locker locker(mutex, tsrMutexWaits);

  indexEntry(iReturned) = iTop;
  iTop = iReturned;
}
/*************************************************************************/
bool  FixedObjectPoolMemoryManager::check(const void* p){

  if(!isPointerSane(p))
    return false;

  EntryIndex iReturned = ((unsigned char*)p - (unsigned char*)pMemory)/iObjectSize;

	Mutex::Locker locker(mutex, tsrMutexWaits);

  EntryIndex iCurrent = iTop;

  while(iCurrent != CUnusedIndex){

    if(p == (void*)&(indexEntry(iCurrent))){
      IAS_LOG(LogLevel::INSTANCE.bIsError,
        "FixedObjectPoolMemoryManager::check() failed for: "<<iCurrent<<"\t"<<(void*)&(indexEntry(iCurrent))<<"\t"<<p);
      return false;
    }

    iCurrent = indexEntry(iCurrent);
  }
	return true;
}
/*************************************************************************/
FixedObjectPoolMemoryManager::~FixedObjectPoolMemoryManager()throw(){
	IAS_TRACER;
}

/*************************************************************************/
void FixedObjectPoolMemoryManager::printToStream(std::ostream& os){

	Mutex::Locker locker(mutex);

	os<<"FixedObjectPoolMemoryManager, entries="<<iNumObjects<<", size="<<iObjectSize<<" bytes."<<std::endl;

	os<<"  Waits:        "<<tsrMutexWaits<<std::endl;
	os<<"  Allocations:  "<<tsrAllocations<<std::endl;
	os<<std::endl;
}
/*************************************************************************/
void FixedObjectPoolMemoryManager::dump(std::ostream& os){

  os<<"Free List"<<std::endl;
  Mutex::Locker locker(mutex);

  EntryIndex iCurrent = iTop;

  while(iCurrent != CUnusedIndex){
    os<<iCurrent<<"\t"<<(void*)&(indexEntry(iCurrent))<<std::endl;
    iCurrent = indexEntry(iCurrent);
  }
  os<<"End of dump."<<std::endl;
}
/*************************************************************************/
void FixedObjectPoolMemoryManager::trim(){
}
/*************************************************************************/
}
