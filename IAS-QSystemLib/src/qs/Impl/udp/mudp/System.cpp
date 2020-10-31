/*
 * MUDP: IAS-QSystemLib/src/qs/Impl/sdf/file/System.cpp
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
#include "System.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "InputDriver.h"
#include "OutputDriver.h"

namespace IAS {
namespace QS {
namespace UDP {
namespace MUDP {

/*************************************************************************/
System::System():UDP::System(){
	IAS_TRACER;
}
/*************************************************************************/
UDP::InputDriver* System::createInputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                            const API::Destination& destination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<InputDriver>::Create(dmConnection, destination);
}
/*************************************************************************/
UDP::OutputDriver* System::createOutputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                            const API::Destination& destination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<OutputDriver>::Create(dmConnection, destination);
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
