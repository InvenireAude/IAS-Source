/*
 * File: IAS-QSystemLib/src/qs/lang/db/ModuleProxy.cpp
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
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "WrappedStatement.h"
#include "Commit.h"
#include "Rollback.h"
#include "CommitAll.h"
#include "RollbackAll.h"

namespace IAS {
namespace QS {
namespace Lang {
namespace DB {

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
	registerSymbol("WrappedStatement",  &(WrappedStatement::Create));
	registerSymbol("Commit",            &(Commit::Create));
	registerSymbol("Rollback",          &(Rollback::Create));
  registerSymbol("CommitAll",         &(CommitAll::Create));
	registerSymbol("RollbackAll",       &(RollbackAll::Create));
}
/*************************************************************************/
void ModuleProxy::cleanUpImpl(){
	IAS_TRACER;
}
/*************************************************************************/
ModuleProxy* ModuleProxy::Create(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<ModuleProxy>::Create();
}
/*************************************************************************/
}
}
}
}
/*************************************************************************/
void* ias_qs_lang_db_proxy(){
	IAS_TRACER;
	return ::IAS::QS::Lang::DB::ModuleProxy::Create();
}
/*************************************************************************/
