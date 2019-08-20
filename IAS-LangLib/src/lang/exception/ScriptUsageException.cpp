/*
 * File: IAS-LangLib/src/lang/exception/ScriptUsageException.cpp
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
#include "ScriptUsageException.h"
#include <lang/log/LogLevel.h>
#include <lang/ui/Messages.h>

namespace IAS{
namespace Lang {


/*************************************************************************/
ScriptUsageException::ScriptUsageException(){
	IAS_TRACER;
}

/*************************************************************************/
ScriptUsageException::ScriptUsageException(const String& strInfo){
	IAS_TRACER;
	setInfo(strInfo);
	UserMessage(UI::Messages::MSGE_LangScriptUsageError)<<getInfo();
}
/*************************************************************************/
ScriptUsageException::ScriptUsageException(const String& strInfo, const String& strFile, int iLine){
	(*this)<<strInfo<<", \n\t at: "<<strFile<<":"<<iLine;
	UserMessage(UI::Messages::MSGE_LangScriptUsageError)<<getInfo();
}
/*************************************************************************/
ScriptUsageException::ScriptUsageException(const String& strInfo, Tools::Parser::LexerIStreamWrapper* pLexerIStreamWrapper){
	IAS_TRACER
	IAS_CHECK_IF_NULL(pLexerIStreamWrapper);

	(*this)<<strInfo<<", \n\t at: "<<pLexerIStreamWrapper->getName()<<":"<<pLexerIStreamWrapper->getLineNo();
	UserMessage(UI::Messages::MSGE_LangScriptUsageError)<<getInfo();
}
/*************************************************************************/
ScriptUsageException::~ScriptUsageException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* ScriptUsageException::getName(){
	IAS_TRACER;
	return "ScriptUsageException";
}


/*************************************************************************/
} /* namespace Lang */
} /* namespace AS */
