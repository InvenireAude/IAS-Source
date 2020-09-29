/*
 * File: IAS-CommonExe/src/parameters/ProgramParameters.cpp
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
#include "ProgramParameters.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace Exe {
namespace Parameters {
/*************************************************************************/
const String ProgramParameters::StrCommonArgSpec("Vh");
/*************************************************************************/
ProgramParameters::ProgramParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
ProgramParameters::~ProgramParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool ProgramParameters::checkAndShowHelp(std::ostream& os){
	IAS_TRACER;

	if(hmIndicators.size() > 0 && !hmIndicators['h'])
		return false;

	showHelp(os);

	return true;
}
/*************************************************************************/
bool ProgramParameters::checkAndShowVersion(std::ostream& os){
	IAS_TRACER;

	if(hmIndicators.size() > 0 && !hmIndicators['V'])
		return false;

  IAS::Version::Print(os);
  os<<std::endl;

	return true;
}
/*************************************************************************/
void ProgramParameters::showHelp(std::ostream& os){
	IAS_TRACER;

	os<<"\n\t"<<getExeName()<<" ";
	printCmdDesc(os);
	os<<std::endl<<std::endl;
	os<<"Options:"<<std::endl;
	os<<"\t-h\t\t This help."<<std::endl;
  os<<"\t-V\t\t Version information."<<std::endl;
	printArgsDesc(os);
	os<<std::endl;

}
/*************************************************************************/
void ProgramParameters::init(int argc, char* argv[], const String& strArgSpec){
	IAS_TRACER;
	String strAllArgSpec(StrCommonArgSpec);
	strAllArgSpec += strArgSpec;
	::IAS::ProgramParameters::init(argc, argv, strAllArgSpec);
}
/*************************************************************************/
void ProgramParameters::printCmdDesc(std::ostream& os) const {
	IAS_TRACER;
	os<<"";
}
/*************************************************************************/
void ProgramParameters::printArgsDesc(std::ostream& os) const {
	IAS_TRACER;
	os<<"";
}
/*************************************************************************/
}
}
}
