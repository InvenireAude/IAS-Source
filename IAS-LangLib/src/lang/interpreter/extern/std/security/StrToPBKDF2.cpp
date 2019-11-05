/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/StrToPBKDF2.cpp
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
#include "StrToPBKDF2.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <commonlib/net/ssl/Tools.h>

#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {
namespace Security {

/*************************************************************************/
StrToPBKDF2::StrToPBKDF2(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
StrToPBKDF2::~StrToPBKDF2() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StrToPBKDF2::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;
	DM::DataObject* pParameters = pCtx->getBlockVariables(0);
  const String strAlgo = pParameters->getString("strAlgo");
	const String strArgument = pParameters->getString("strArgument");
  const String strSalt = pParameters->getString("strSalt");
  const unsigned int iCount = pParameters->getInteger("iCount");
  const unsigned int iResultLen = pParameters->getInteger("iResultLen");

	pParameters->setString(Model::Dec::ResultDeclarationNode::CStrResultVariable,
    Net::SSL::Tools::PBKDF2(strAlgo, strArgument, strSalt, iCount, iResultLen));
}
/*************************************************************************/
Statement* StrToPBKDF2::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<StrToPBKDF2>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
}
