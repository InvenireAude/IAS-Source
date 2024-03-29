/*
 * File: IAS-QSystemMod-SysMon/src/qs/lang/ldap/ModuleProxy.cpp
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

#include "ModuleProxy.h"
#include <lang/log/LogLevel.h>
#include "SimpleQuery.h"


#include <org/invenireaude/lang/mod/ldap/QueryResult.h>
#include <org/invenireaude/lang/mod/ldap/DataFactory.h>

using namespace ::org::invenireaude::lang::mod::ldap;

namespace IAS  {
namespace QS  {
namespace Lang {
namespace LDAP  {

/*************************************************************************/
ModuleProxy::ModuleProxy(){
	IAS_TRACER;
}
/*************************************************************************/
ModuleProxy::~ModuleProxy() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ModuleProxy::setupImpl(){
	IAS_TRACER;
	registerSymbol("SimpleQuery",  &(SimpleQuery::Create));
}
/*************************************************************************/
void ModuleProxy::cleanUpImpl(){
	IAS_TRACER;
}
/*************************************************************************/
ModuleProxy* ModuleProxy::Create(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"ModuleProxy::Create()");
	DataFactory::GetInstance()->getContaingDataFactory();
	return IAS_DFT_FACTORY<ModuleProxy>::Create();
}
/*************************************************************************/
}
}
}
}

/*************************************************************************/
void* ias_lang_mod_ldap_proxy(){
	IAS_TRACER;
	return ::IAS::QS::Lang::LDAP::ModuleProxy::Create();
}
/*************************************************************************/
