/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/MemoryManager.h
 *
 * Copyright (C) 2015, Albert Krzymowski
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#ifndef _IAS_MemoryManager_H_
#define _IAS_MemoryManager_H_


#include <iostream>
#include <map>
#include <list>

#include "../ma/Allocator.h"

#include "../../threads/Mutex.h"
#include "../../sys/Signal.h"

namespace IAS{

/*************************************************************************/
/** The MemoryManager class.
 * One can dump the remaining allocated areas with printToStream() function.
 */

class MemoryManager :
	public Allocator,
  public SYS::Signal::UserSignalCallback
   {

public:
	MemoryManager(const char *sName = CDefaultName);
	virtual ~MemoryManager()throw();

	void addEntry(const char*   sFile,
			      const char*   sFun,
			      int           iLine,
			      unsigned long lPtr,
				  unsigned long iNumBytes);

	bool removeEntry(unsigned long lPtr);

	/** dumps the entries to the output stream */

	virtual void printToStream(std::ostream& os);

	void printToStream(std::ostream& os, bool bNewOnly, bool bStatsOnly = false);

	/** clears the "new" flag - use after allocating globals for example. */
	void clearNewFlag();

	inline static MemoryManager *GetInstance(){
		if(pInstance == NULL){
			pAllocator = pInstance = new MemoryManager;
    }
		return pInstance;
	}

	void static SetDefaultAllocator(Allocator* pAllcator){
		MemoryManager::pAllocator=pAllcator;
	}

	 long  getNumerOfNew()const;

 	 virtual void* allocate(size_t n);
	 virtual void  free(const void* p);
	 virtual bool check(const void* p);
   virtual void trim();

	inline static Allocator *GetAllocator(){
			GetInstance();
			return pAllocator;
	}

  virtual void handleUserSignal();

  static const char* CDefaultName;


 private:

	 struct Entry{
		const char *sFun;
		const char *sFile;
#ifdef __GLIBC__
    void *back_trace_array[10];
    int  back_trace_array_size;
    void printBackTrace(std::ostream& os) const;
#endif
		int        iLine;
		bool       bNewFlag;
		int        iTID;
		unsigned long lPtr;
		unsigned long iNumBytes;
	};

	typedef std::map<unsigned long, Entry> EntryMap;
	typedef std::map<std::string, void*> SharableInstancesMap;

	static MemoryManager   *pInstance;
	static Allocator       *pAllocator;

	EntryMap 				hmEntries;
	SharableInstancesMap	hmSharableInstances;

	unsigned long iTotalEntries;
	unsigned long iCurEntries;
	unsigned long iNewEntries;
	unsigned long iInstances;
	unsigned long iNumBytes;

	Mutex theLock;

	friend class IAS::Factory<MemoryManager>;

	unsigned char *pMemory;
	int           iFree;
  const char    *sName;
	TimeSamplesResults  tsrMutexWaits;
  TimeSamplesResults trsMemoryTrim;

  void clearNewFlagNoLock();
};

template<class T, class CO = DynamicCastOperator <T> >
 class MemoryManagerFactory : public AllocatorFactory<T, ::IAS::MemoryManager::GetAllocator, CO > {};

template<class T, class CO = StaticCastOperator <T> >
 class MemoryManagerStaticFactory : public AllocatorFactory<T, ::IAS::MemoryManager::GetAllocator, CO > {};

};

namespace IAS2{
using namespace IAS;

template<class T, class CO = DynamicCastOperator <T> >
 class MemoryManagerFactory : public IAS2::AllocatorFactory<T, CO > {};

};

#endif /* _IAS_MemoryManager_H_ */
