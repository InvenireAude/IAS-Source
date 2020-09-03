/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/FixedObjectPoolMemoryManager.h
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
#ifndef _IAS_FixedObjectPoolMemoryManager_H_
#define _IAS_FixedObjectPoolMemoryManager_H_

#include "../ma/Allocator.h"
#include "MemoryManager.h"

#include "commonlib/threads/Mutex.h"

namespace IAS {

/*************************************************************************/
/** The FixedObjectPoolMemoryManager class.
 *
 */
class FixedObjectPoolMemoryManager : public Allocator {
public:

	virtual ~FixedObjectPoolMemoryManager()throw();

	virtual void* allocate(size_t n);
	virtual void  free(const void* p);
	virtual bool  check(const void* p);
  virtual void  trim();

	virtual void printToStream(std::ostream& os);

	void dump(std::ostream& os);

	FixedObjectPoolMemoryManager(void *pStart, size_t iObjectSize, size_t iNumObjects);

	friend class Factory<FixedObjectPoolMemoryManager>;

	typedef uint32_t EntryIndex;
    static  const uint32_t CUnusedIndex = 0xffffffff;

	void*            pMemory;
    EntryIndex       iTop;

    size_t           iObjectSize;
  	size_t           iNumObjects;

  	bool             bFreeMe;

	TimeSamplesResults  tsrMutexWaits;
	TimeSamplesResults  tsrAllocations;

	inline EntryIndex& indexEntry(size_t iIdx){
		return *(EntryIndex*)(((unsigned char*)pMemory) + iIdx * iObjectSize);
	}

	inline bool isPointerSane(const void *p) const;

  	Mutex mutex;
};

/*************************************************************************/
}

#endif /* _IAS_FixedObjectPoolMemoryManager_H_ */
