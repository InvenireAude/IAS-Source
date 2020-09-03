/*
 * File: Logger.h
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


#ifndef _IAS_Storage_Logger_H_
#define _IAS_Storage_Logger_H_

#include "../memory/memory.h"
#include "../logger/logger.h"
#include "../types.h"

using namespace IAS;

namespace IAS {
namespace Storage {

class LoggerOutput;
/*************************************************************************/
/** The Logger class.
 *
 */
class Logger {
public:

	virtual ~Logger() throw();

  virtual void logData(const void *pData, size_t iDataLen) = 0;

protected:
	Logger(LoggerOutput* pLoggerOutput);

  IAS_DFT_FACTORY<LoggerOutput>::PtrHolder ptrLoggerOutput;

	friend class Factory<Logger>;
};

/*************************************************************************/
}
}

#endif /* _IAS_Storage_Logger_H_ */
