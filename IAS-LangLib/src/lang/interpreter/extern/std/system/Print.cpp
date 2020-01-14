/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/Print.cpp
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
#include "Print.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/ui/Messages.h>

#include <dm/datamodel.h>
 #include <syslog.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {
namespace System {
/*************************************************************************/
Print::Print(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
Print::~Print() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Print::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strStreamName  = pParameters->getType()->asComplexType()->getProperties().hasProperty("stream") ?
                                   pParameters->getString("stream") : "stdout";

  const String strMessage  = pParameters->getString("message");

  if(strStreamName.compare("stdout")==0){
    std::cout<<strMessage<<std::endl;
  }else if(strStreamName.compare("stderr")==0){
    std::cout<<strMessage<<std::endl;
  } else {
    OutputFile::SaveString(strStreamName, strMessage+"\n", true);
  }


}
/*************************************************************************/
Statement* Print::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Print>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
}
