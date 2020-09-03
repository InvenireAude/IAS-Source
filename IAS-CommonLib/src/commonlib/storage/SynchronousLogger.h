/*
 * File: SynchronousLogger.h
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


#ifndef _IAS_Storage_SynchronousLogger_H_
#define _IAS_Storage_SynchronousLogger_H_

#include "../logger/logger.h"
#include "../types.h"

#include "Logger.h"

using namespace IAS;

namespace IAS {
namespace Storage {

/*************************************************************************/
/** The SynchronousLogger class.
 *
 */
class SynchronousLogger : public Logger{
public:

	virtual ~SynchronousLogger() throw();

 virtual void logData(const void *pData, size_t iDataLen);

protected:
	SynchronousLogger(LoggerOutput* pLoggerOutput);

	friend class Factory<SynchronousLogger>;
};

/*************************************************************************/
}
}

#endif /* _IAS_Storage_SynchronousLogger_H_ */
