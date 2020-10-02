/*
 * MBus: IAS-QSystemLib/src/qs/Impl/sdf/file/DriverBase.cpp
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
#include "DriverBase.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Message.h"

namespace IAS {
namespace QS {
namespace UDP {

const String DriverBase::CEnvInterface("IAS_QS_UDP_INTERFACE");
/*************************************************************************/
DriverBase::DriverBase(const API::Destination& destination):
  destination(destination),
  strTopic(destination.getName()),
  pAllocator(MemoryManager::GetAllocator()){
  IAS_LOG(LogLevel::INSTANCE.isInfo(), "Topic: ["<<strTopic<<"]");
	IAS_TRACER;
}
/*************************************************************************/
DriverBase::~DriverBase() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String DriverBase::getInterface()const{
  IAS_TRACER;
  return EnvTools::GetEnvWithDefault(CEnvInterface,"127.0.0.1");
}
/*************************************************************************/
}
}
}
