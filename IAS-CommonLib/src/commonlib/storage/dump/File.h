/*
 * File: File.h
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


#ifndef _IAS_Storage_Dump_File_H_
#define _IAS_Storage_Dump_File_H_

#include<commonlib/logger/logger.h>
#include<commonlib/types.h>
#include<commonlib/memory/memory.h>
#include<commonlib/memory/sharable/SharedMemoryFile.h>
#include<commonlib/threads/Mutex.h>

namespace IAS {
namespace Storage {
namespace Dump {

/*************************************************************************/
/** The File class.
 *
 */
class File {
public:

	virtual ~File() throw();

  typedef size_t IndexType;
  typedef size_t SizeType;

  inline SizeType getSize(){
    return iSize;
  }

  inline SizeType getAllocated(){
    Mutex::Locker locker(mutex);
    return *pBytesAllocated;
  }

  inline SizeType getNumItems(){
    Mutex::Locker locker(mutex);
    return *pNumItems;
  }

  inline SizeType getFree(){
    Mutex::Locker locker(mutex);

    if(iSize < *pBytesAllocated + 2 * sizeof(SizeType) + 7)
      return 0;

    return iSize - *pBytesAllocated - 2 * sizeof(SizeType) - 8;
  }

  inline bool hasMoreData(){
    return pFirstFree > pFirstToRead;
  }

  void* allocate(SizeType n);
  void* readNext(SizeType& iDataLen);

  inline const String& getName()const{
    return descriptor.getName();
  }

protected:
	File(const String& strFileName, size_t iSize = 0);

  SharedMemoryFile::Descriptor descriptor;
  IAS_DFT_FACTORY<SharedMemoryFile>::PtrHolder ptrFile;

  void     *pData;
  char     *pFirstFree;
  char     *pFirstToRead;
  SizeType *pBytesAllocated;
  SizeType *pNumItems;
  SizeType iSize;
  Mutex mutex;

	friend class Factory<File>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Storage_Dump_File_H_ */
