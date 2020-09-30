/*
 * File: FileSet.h
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


#ifndef _IAS_Storage_Dump_FileSet_H_
#define _IAS_Storage_Dump_FileSet_H_

#include <commonlib/logger/logger.h>
#include <commonlib/types.h>
#include <commonlib/memory/memory.h>
#include <commonlib/memory/sharable/SharedMemoryFile.h>
#include <commonlib/threads/Mutex.h>

#include "File.h"
#include <list>

namespace IAS {
namespace Storage {
namespace Dump {

/*************************************************************************/
/** The FileSet class.
 *
 */
class FileSet : public Allocator{
public:

	virtual ~FileSet() throw();

	virtual void* allocate(size_t n);
	virtual void  free(const void* p);
	virtual bool  check(const void* p);
  virtual void  trim();
  virtual void printToStream(std::ostream& os);


  void openBackLog();
  void *nextFromBackLog(File::SizeType& iDataLen);
  bool hasMoreBackLogData();

protected:
	FileSet(const String& strDirectory,
          size_t   iMaxFileSize);

  String strDirectory;

  typedef std::list<File*>  FilesList;

  FilesList                 lstFiles;
  FilesList                 lstBackLogFiles;
  FilesList::iterator       itBackLogFiles;

  size_t iNextSeq;
  size_t iMaxFileSize;

  String buildFileName(unsigned int iSeq)const;
  void   closeOldest();

  bool discoverNextSequence();
  void createNewFile();

  static const String CFileSufix;
  static const int    CNumNameDigits;

	friend class Factory<FileSet>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Storage_Dump_FileSet_H_ */
