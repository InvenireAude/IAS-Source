/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Receiver.cpp
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
#include "Receiver.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Message.h"
#include "Session.h"
#include "Connection.h"
#include "System.h"

#include <commonlib/commonlib.h>
#include "InputDriver.h"

namespace IAS {
namespace QS {
namespace UDP {

/*************************************************************************/
Receiver::Receiver(Session* pSession):
	Manageable(pSession),
	pDriver(0),
	myDestination("__FAKE__"){
	IAS_TRACER;
}

/*************************************************************************/
Receiver::~Receiver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Receiver::open(const API::Destination& refDestination){
	IAS_TRACER;

  pDriver=getSession()->getConnection()->getSystem()->getInputDriver(
          getSession()->getConnection()->getConfiguration(),
          refDestination);

	IAS_CHECK_IF_NULL(pDriver);
}
/*************************************************************************/
API::Message* Receiver::receive(int iTimeWait, API::Attributes* pSelector){

	IAS_TRACER;

	return pDriver->receive(iTimeWait, pSelector);

}

/*************************************************************************/

}
}
}
