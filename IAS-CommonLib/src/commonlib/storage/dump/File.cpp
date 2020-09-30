/*
 * File: File.cpp
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

#include "File.h"

#include <commonlib/exception/ItemNotFoundException.h>
#include <commonlib/memory/sharable/SharedMemoryFile.h>
#include <commonlib/sys/fs/FileLock.h>

namespace IAS {
namespace Storage {
namespace Dump {

/*************************************************************************/
File::File(const String& strFileName, size_t iSize){
	IAS_TRACER;

  descriptor.setName(strFileName);
  descriptor.setDomain(SharedMemoryFile::Descriptor::DM_FILE);
  if(iSize){
    descriptor.setSize(iSize);
    descriptor.setOpenMode(SharedMemoryFile::Descriptor::OM_CREATE_IF_NEEDED);
  }else{
    descriptor.setOpenMode(SharedMemoryFile::Descriptor::OM_ATTACH);
  }

  ptrFile = IAS_DFT_FACTORY<SharedMemoryFile>::Create(descriptor);

  this->iSize   = ptrFile->getSize();
  pData = ptrFile->getAddress();

  pBytesAllocated = reinterpret_cast<SizeType*>(pData);
  pNumItems       = pBytesAllocated + 1;
  pData = reinterpret_cast<void*>(pNumItems + 1);

  if(iSize){
    *pBytesAllocated = 0;
    *pNumItems = 0;
  }

  pFirstFree   = reinterpret_cast<char*>(pData) + *pBytesAllocated;
  pFirstToRead = reinterpret_cast<char*>(pData);

  IAS_LOG(LogLevel::INSTANCE.isInfo(),"File: "<<strFileName<<", size: "<<this->iSize<<", used: "<<*pBytesAllocated<<", items: "<<*pNumItems);
}
/*************************************************************************/
File::~File() throw(){
	IAS_TRACER;
}
/*************************************************************************/
static inline size_t __alignSize(size_t n){
  return (n + 0x07) & 0xfffffff8;
}
/*************************************************************************/
void* File::allocate(SizeType n){
	IAS_TRACER;

  Mutex::Locker locker(mutex);

  if(__alignSize(n) + *pBytesAllocated + 2 * sizeof(SizeType) > iSize)
    IAS_THROW(ItemNotFoundException("Dump::File::allocate: ")<<n<<" "<<__alignSize(n)<<" "
          <<(*pBytesAllocated)<<" "<<(2*sizeof(SizeType)));

  SizeType *pItemSize = reinterpret_cast<SizeType*>(pFirstFree);

  *pItemSize = n;
  pFirstFree = reinterpret_cast<char*>(pItemSize + 1);

  void *pResult = pFirstFree;

  pFirstFree += __alignSize(n);
  *pBytesAllocated = pFirstFree - reinterpret_cast<char*>(pData);
  (*pNumItems)++;
  return pResult;
}
/*************************************************************************/
void* File::readNext(SizeType& iDataLen){
	IAS_TRACER;

  Mutex::Locker locker(mutex);

  if(!hasMoreData())
    IAS_THROW(ItemNotFoundException("Dump::File::readNext: ")<<descriptor.getName());

  SizeType *pItemSize = reinterpret_cast<SizeType*>(pFirstToRead);
  iDataLen = *pItemSize;
  pFirstToRead = reinterpret_cast<char*>(pItemSize + 1);
  void *pResult = reinterpret_cast<void*>(pFirstToRead);

  pFirstToRead += __alignSize(iDataLen);
  pItemSize = reinterpret_cast<SizeType*>(pFirstToRead);

  return pResult;
}
/*************************************************************************/
}
}
}
