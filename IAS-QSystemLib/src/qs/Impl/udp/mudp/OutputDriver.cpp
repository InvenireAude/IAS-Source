/*
 * MUDP: IAS-QSystemLib/src/qs/Impl/sdf/file/OutputDriver.cpp
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
#include "OutputDriver.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Message.h"

#include <org/invenireaude/qsystem/workers/ClientIP.h>

namespace IAS {
namespace QS {
namespace UDP {
namespace MUDP {

/*************************************************************************/
OutputDriver::OutputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                            const API::Destination& destination):
    UDP::OutputDriver(destination),
		strMUDPName(dmConnection->getHost()),
    sender(dmConnection->getPort()),
		iCount(0){
	IAS_TRACER;

  sender.setup(getInterface(),dmConnection->getHost());

}
/*************************************************************************/
OutputDriver::~OutputDriver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool OutputDriver::send(Message* pMessage){

	IAS_TRACER;

	Mutex::Locker locker(mutex);
  size_t iDataLen = 0;
  pMessage->write(buffer, iDataLen, strTopic);
  sender.send(buffer.getBuffer<void>(), iDataLen);
  iCount ++;

	return true;
}
/*************************************************************************/
}
}
}
}
