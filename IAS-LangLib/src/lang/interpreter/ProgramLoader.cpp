/*
 * File: IAS-LangLib/src/lang/interpreter/ProgramLoader.cpp
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
#include "ProgramLoader.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../script/parser.h"
#include "lang/model/Model.h"
#include "lang/interpreter/proc/processor.h"
#include "lang/interpreter/exe/Context.h"
#include "lang/interpreter/exe/Program.h"
#include "lang/interpreter/proc/ExecStore.h"
#include "lang/tools/parser/LexerIStreamFactoryForFiles.h"
#include "lang/exception/SourceNotFoundException.h"


namespace IAS {
namespace Lang {
namespace Interpreter {


const char    ProgramLoader::CFilePathDelimiter='/';
const String& ProgramLoader::CStrFileSufix=".b";
const char    ProgramLoader::CProgramNameDelimiter='.';

/*************************************************************************/
ProgramLoader::ProgramLoader(DM::DataFactory  *pDataFactory,
							Tools::Parser::LexerIStreamFactory* pLexerIStreamFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pDataFactory);

	ptrModel = IAS_DFT_FACTORY<Model::Model>::Create();

	ptrExecStore = IAS_DFT_FACTORY<Proc::ExecStore>::Create(ptrModel.getPointer(),pDataFactory);

	if(pLexerIStreamFactory==NULL){
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Default factory");
		ptrLexer=IAS_DFT_FACTORY<Script::Parser::Lexer>::Create<Tools::Parser::LexerIStreamFactory*, Tools::Parser::ISourceLocationStore*>(
				IAS_DFT_FACTORY<Tools::Parser::LexerIStreamFactoryForFiles>::Create(),ptrModel);
	}else{
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Supplied factory");
		ptrLexer=IAS_DFT_FACTORY<Script::Parser::Lexer>::Create<Tools::Parser::LexerIStreamFactory*, Tools::Parser::ISourceLocationStore*>(
				pLexerIStreamFactory,ptrModel);
	}

	ptrSourceStore = IAS_DFT_FACTORY<::IAS::Lang::Export::Text::SourceStore>::Create(ptrModel.getPointer(),pDataFactory);

}
/*************************************************************************/
ProgramLoader::~ProgramLoader() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ProgramLoader::loadModel(const String& strObject, Tools::Parser::LexerIStreamWrapper* pWrapper){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Model for: "<<strObject);

  bool bSomethingNewToParse = false;
	try{
		bSomethingNewToParse = ptrLexer->openObject(strObject, pWrapper);
	}catch(ItemNotFoundException& e){
		IAS_THROW(SourceNotFoundException(strObject));
	}

  if(bSomethingNewToParse){
	  IAS_DFT_FACTORY<Script::Parser::Parser>::PtrHolder ptrParser(IAS_DFT_FACTORY<Script::Parser::Parser>::Create(ptrModel.getPointer()));
	  IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"START Parsing:"<<strObject);
	  ptrParser->parse(ptrLexer);
	  IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"END Parsing:"<<strObject);
	  compileAll();
  }
}
/*************************************************************************/
const Interpreter::Exe::Program* ProgramLoader::getExecutable(const String& strProgramName)const{
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"getExecutable: "<<strProgramName);

	Model::Model::ProgramList lstPrograms(ptrModel->getPrograms(strProgramName));

	if(lstPrograms.size() == 0)
		IAS_THROW(ItemNotFoundException(strProgramName));

	if(lstPrograms.size() != 1)
		IAS_THROW(BadUsageException("More than one program with the same name in an external call: " + strProgramName));

	return ptrExecStore->getExecutable(*lstPrograms.begin());
}
/*************************************************************************/
const Interpreter::Exe::Program* ProgramLoader::getExecutable(const String& strProgramName, const TypeList& lstTypes)const{
	IAS_TRACER;

	if(::IAS::Lang::LogLevel::INSTANCE.isInfo()){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"getExecutable: "<<strProgramName<<", no. of args: "<<lstTypes.size());
		for(TypeList::const_iterator it = lstTypes.begin(); it != lstTypes.end(); it++)
			IAS_LOG(LogLevel::INSTANCE.isInfo(),(*it)->getFullName());
	}

	ProgramList lstOutput;

	return ptrExecStore->createOrGetExecutable(strProgramName, lstTypes);
}
/*************************************************************************/
void ProgramLoader::findAllMatches(const TypeList& lstTypes, ProgramList& lstOutput){
	IAS_TRACER;

	return ptrExecStore->findAllMatches(lstTypes,lstOutput);
}
/*************************************************************************/
const ::IAS::Lang::Model::Model* ProgramLoader::getModel()const{
	IAS_TRACER;
	return ptrModel;
}
/*************************************************************************/
::IAS::Lang::Export::Text::SourceStore* ProgramLoader::getSourceStore(){
	IAS_TRACER;
	return ptrSourceStore;
}
/*************************************************************************/
void ProgramLoader::compileAll(){
	ptrExecStore->compileAll();
}
/*************************************************************************/
const ::IAS::DM::DataFactory *ProgramLoader::getDataFactory()const{
	return pDataFactory;
}
/*************************************************************************/
}
}
}
