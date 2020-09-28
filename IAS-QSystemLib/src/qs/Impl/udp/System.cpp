/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/System.cpp
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
#include "System.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "ContentManager.h"
#include "Connection.h"

#include "OutputDriver.h"
#include "InputDriver.h"

#include "org/invenireaude/qsystem/stats/DataFactory.h"


using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace UDP {

/*************************************************************************/
System::System():
	strName("UDPMulitCast"){
	IAS_TRACER;
}
/*************************************************************************/
API::Connection* System::createConnection(
    const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;
	return IAS_DFT_FACTORY<QS::UDP::Connection>::Create(this,dmConnection);
}
/*************************************************************************/
ContentManager*  System::getContentManager(){
	IAS_TRACER;
	IAS_THROW(InternalException("No content created"));
	return 0;
}
/*************************************************************************/
static String _getKey(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                     const API::Destination& destination){
  StringStream ss;
  ss<<dmConnection->getHost()<<"#"<<dmConnection->getPort()<<"#"<<destination.getName();
  return ss.str();
}
/*************************************************************************/
InputDriver*  System::getInputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                     const API::Destination& destination){
	IAS_TRACER;
	Mutex::Locker locker(mutex);

  String strKey(_getKey(dmConnection, destination));

  if(!hmInputDrivers.count(strKey))
		hmInputDrivers[strKey] = createInputDriver(dmConnection, destination);

	return hmInputDrivers.at(strKey);

}
/*************************************************************************/
OutputDriver* System::getOutputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                     const API::Destination& destination){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

  String strKey(_getKey(dmConnection, destination));

  if(!hmOutputDrivers.count(strKey))
		hmOutputDrivers[strKey]=createOutputDriver(dmConnection, destination);

	return hmOutputDrivers.at(strKey);
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** UDP instance destroyed.");
}
/*************************************************************************/
}
}
}
