/*
 * File: IAS-QSystemLib/src/qs/lang/tools/ApplyTemplate.cpp
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
#include "ApplyTemplate.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>
#include <lang/tools/parser/LexerIStreamWrapper.h>

#include <lang/model/dec/ResultDeclarationNode.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <dm/datamodel.h>
#include <dm/gen/DataFactory.h>

#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>
//TODO common include for Lang
#include <lang/interpreter/ProgramLoader.h>
#include <lang/model/Model.h>
#include <lang/interpreter/proc/processor.h>

#include "regexp/RegExpMatchContainer.h"

#include <qs/tools/Template.h>

using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {

/*************************************************************************/
ApplyTemplate::ApplyTemplate(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

	ptrDataFactory = IAS_DFT_FACTORY<DM::Impl::DataFactory>::Create(::IAS::DM::Gen::DataFactory::GetInstance());


	IAS_DFT_FACTORY<IAS::Lang::Tools::Parser::LexerIStreamFactoryForFiles>::PtrHolder ptrLexerIStreamFactory;
	ptrLexerIStreamFactory = IAS_DFT_FACTORY<IAS::Lang::Tools::Parser::LexerIStreamFactoryForFiles>::Create();

	ptrProgramLoader = IAS_DFT_FACTORY<::IAS::Lang::Interpreter::ProgramLoader>::Create(
			ptrDataFactory,ptrLexerIStreamFactory.pass());

	for(StringList::const_iterator it=lstParamaters.begin(); it != lstParamaters.end(); it++)
		ptrProgramLoader->loadModel(*it);


}
/*************************************************************************/
ApplyTemplate::~ApplyTemplate() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ApplyTemplate::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	IAS_DFT_FACTORY<QS::Tools::Template>::PtrHolder ptrTemplate(
			IAS_DFT_FACTORY<QS::Tools::Template>::Create(pParameters->getString("pattern")));

	DM::DataObject* dmArgs = pParameters->getDataObject("args");

	try{

		StringStream ssResult;

		QS::Tools::Template::Arguments args(dmArgs, ptrProgramLoader);
		ptrTemplate->evaluate(args,ssResult);

		pParameters->setString(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),
				ssResult.str());

	}catch(Exception& e){

		//TODO (H) use exceptions from the tools namespace.

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();

		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}

}
/*************************************************************************/
Extern::Statement* ApplyTemplate::Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<ApplyTemplate>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

