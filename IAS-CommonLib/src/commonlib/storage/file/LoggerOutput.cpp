/*
 * File: LoggerOutput.cpp
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

#include "LoggerOutput.h"

#include <commonlib/exception/SystemException.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

namespace IAS {
namespace Storage {
namespace File {

/*************************************************************************/
LoggerOutput::LoggerOutput(const String& strName, size_t iAutoRollLimit, bool bAutoSync):
  strName(strName),
  iAutoRollLimit(iAutoRollLimit),
  bAutoSync(bAutoSync),
  iFD(0){
	IAS_TRACER;

  // TODO rotation; size or date switch etc.

  iFD = ::open(strName.c_str(),
    O_WRONLY | O_CREAT
  , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  if(iFD < 0){
    IAS_THROW(SystemException("open: " + strName, errno));
  }
}
/*************************************************************************/
LoggerOutput::~LoggerOutput() throw(){
	IAS_TRACER;

  if(iFD >= 0)
    close(iFD);
}
/*************************************************************************/
void LoggerOutput::write(const void *pData, size_t iDataLen){
	IAS_TRACER;

  ssize_t iWritten = 0;

  while(iWritten < iDataLen){

    ssize_t iResult = ::write(iFD,(const char*)pData + iWritten, iDataLen - iWritten);

    if(iResult < 0){
     IAS_THROW(SystemException("write to: " +  strName, errno));
    }

    iWritten += iResult;
  }

  if(!bAutoSync)
    return;


  // TODO check if open flags works https://lwn.net/Articles/350219/

  if(fsync(iFD) < 0){
     IAS_THROW(SystemException("fsync: " + strName, errno));
  }

}
/*************************************************************************/


}
}
}
