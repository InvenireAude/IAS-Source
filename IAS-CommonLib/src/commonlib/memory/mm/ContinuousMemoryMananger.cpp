/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/ContinuousMemoryMananger.cpp
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
#include "ContinuousMemoryMananger.h"
#include "commonlib/exception/InternalException.h"

#include <commonlib/commonlib.h>
#include <new>
#include <string.h>
#include <strings.h>

namespace IAS {


/*************************************************************************/
ContinuousMemoryMananger::ContinuousMemoryMananger(
    void *pStart, size_t iSize):
  bFreeMe(false),
  iStart(0),
  iSize(iSize),
  iFree(iSize){
	IAS_TRACER;

  if(!pStart){

    pStart = new char[iSize];

    if(!pStart){
      IAS_LOG(LogLevel::INSTANCE.bIsError,"ContinuousMemoryMananger cannot allocate memory.");
      throw std::bad_alloc();
    }

    bFreeMe = true;
  }

  pMemory = (unsigned char*) pStart;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CMM is ready !");

}
/*************************************************************************/
void* ContinuousMemoryMananger::allocate(size_t n){

  if(iFree < n){
    IAS_LOG(LogLevel::INSTANCE.bIsError,"ContinuousMemoryMananger is out of memory.");
    throw std::bad_alloc();
  }

	Mutex::Locker locker(mutex, tsrMutexWaits);
	AutoTimeSample sample(tsrAllocations,LogLevel::INSTANCE.isProfile());

  iFree -= n;
  void *pResult = pMemory + iStart;
  iStart += n;
	return pResult;
}
/*************************************************************************/
inline bool ContinuousMemoryMananger::isPointerSane(const void *p) const{
		bool bResult = p >= pMemory &&
		   p < pMemory + iStart;

		if(!bResult){
			IAS_LOG(LogLevel::INSTANCE.bIsError,"ContinuousMemoryMananger pointer error: "
				<<p<<" "
				<<((unsigned char*)p - (unsigned char*)pMemory)
				<<", iStart: "<<iStart<<", iSize: "<<iSize);
		}

		return bResult;
  	}
/*************************************************************************/
void  ContinuousMemoryMananger::free(const void* p){

  if(!isPointerSane(p)){
   throw std::bad_alloc();
  }

}
/*************************************************************************/
bool  ContinuousMemoryMananger::check(const void* p){

  if(!isPointerSane(p))
    return false;

	return true;
}
/*************************************************************************/
ContinuousMemoryMananger::~ContinuousMemoryMananger()throw(){
	IAS_TRACER;
}

/*************************************************************************/
void ContinuousMemoryMananger::printToStream(std::ostream& os){

	Mutex::Locker locker(mutex);

	os<<"ContinuousMemoryMananger, size: "<<iSize<<", start: "<<iStart<<std::endl;

	os<<"  Waits:        "<<tsrMutexWaits<<std::endl;
	os<<"  Allocations:  "<<tsrAllocations<<std::endl;
	os<<std::endl;
}
/*************************************************************************/
void ContinuousMemoryMananger::dump(std::ostream& os){

  Mutex::Locker locker(mutex);

	os<<"ContinuousMemoryMananger, size: "<<iSize<<", start: "<<iStart<<", free: "<<iFree<<std::endl;

}
/*************************************************************************/
void ContinuousMemoryMananger::trim(){
}
/*************************************************************************/
}
