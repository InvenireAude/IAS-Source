/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/GetTimeDiff.cpp
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
#include "GetTimeDiff.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {

/*************************************************************************/
GetTimeDiff::GetTimeDiff(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
GetTimeDiff::~GetTimeDiff() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetTimeDiff::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	DateTime tsOne(pParameters->getDate("arg1"));
	DateTime tsTwo(pParameters->getDate("arg2"));

	Timestamp ts(tsOne-tsTwo);

	short iHour;
	short iMin;
	short iSec;
	int iUsec;

	ts.getTime(iHour, iMin, iSec, iUsec);

	pParameters->setInteger(Model::Dec::ResultDeclarationNode::CStrResultVariable,((long)ts)*1000+iUsec/1000);

}
/*************************************************************************/
Statement* GetTimeDiff::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetTimeDiff>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
