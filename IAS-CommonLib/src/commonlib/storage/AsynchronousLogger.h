/*
 * File: AsynchronousLogger.h
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


#ifndef _IAS_Storage_AsynchronousLogger_H_
#define _IAS_Storage_AsynchronousLogger_H_

#include "../logger/logger.h"
#include "../types.h"

#include <commonlib/threads/Condition.h>
#include <commonlib/threads/Mutex.h>

#include "Logger.h"

using namespace IAS;

namespace IAS {
namespace Storage {

/*************************************************************************/
/** The AsynchronousLogger class.
 *
 */
class AsynchronousLogger
  : public Logger {
public:

	virtual ~AsynchronousLogger() throw();

  virtual void logData(const void *pData, size_t iDataLen);

protected:
	AsynchronousLogger(LoggerOutput* pLoggerOutput, size_t iLogBufferSize = 4096, int iSyncInterval = 1000);

  Mutex mutex;
  Condition cndWriteInProgress;
  Condition cndReadyToWrite;

  struct LogBuffer {
    unsigned char *pData;
    unsigned char *pCurrent;
    size_t iLogBufferSize;

    void reset();

    size_t getLeftSpaceSize() const;
    size_t getUsedSpaceSize() const;
    void   appendData(const void *pData, size_t iDataLen);

    LogBuffer(size_t iLogBufferSize);
    ~LogBuffer();
  };

  size_t iLogBufferSize;
  int    iSyncInterval;

  LogBuffer logBufferOne;
  LogBuffer logBufferTwo;

  LogBuffer *pWaitingBuffer;
  LogBuffer *pWritingBuffer;

  void swapBuffers();
  void syncBuffer();

	friend class Factory<AsynchronousLogger>;
};

/*************************************************************************/
}
}

#endif /* _IAS_Storage_AsynchronousLogger_H_ */
