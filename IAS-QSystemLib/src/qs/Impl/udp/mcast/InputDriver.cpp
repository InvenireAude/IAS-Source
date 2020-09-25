/*
 * MCast: IAS-QSystemLib/src/qs/Impl/sdf/file/InputDriver.cpp
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
#include "InputDriver.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Message.h"

namespace IAS {
namespace QS {
namespace UDP {
namespace MCast {

/*************************************************************************/
InputDriver::InputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                         const API::Destination& destination):
  destination(destination),
  receiver(dmConnection->getPort()){
	IAS_TRACER;
  receiver.bind();
  receiver.subscribe("127.0.0.1",dmConnection->getHost());
  buffer.reserve(64000);
}
/*************************************************************************/
InputDriver::~InputDriver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Message* InputDriver::receive(int iTimeWait, API::Attributes* pSelector){
	IAS_TRACER;

  size_t iDataLen;
  receiver.receive(buffer.getBuffer<void>(), buffer.getSize(), iDataLen);

 	IAS_DFT_FACTORY<Message>::PtrHolder ptrMessage(
			IAS_DFT_FACTORY<Message>::Create()
	);

  ptrMessage->getContent()->write(buffer.getBuffer<char>(), iDataLen);
  ptrMessage->getContent()->flush();

	ptrMessage->getAttributes()->setMID("ABC");

	return ptrMessage.pass();
}
/*************************************************************************/
unsigned int InputDriver::skip(unsigned int iOffset){
  IAS_TRACER;
  // todo
  return 0;
}
/*************************************************************************/
}
}
}
}
