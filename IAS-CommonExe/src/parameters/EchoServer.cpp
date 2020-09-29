/*
 * File: IAS-QSystemExe/src/parameters/EchoServer.cpp
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
#include "EchoServer.h"


#include <commonlib/commonlib.h>

namespace IAS {
namespace Exe {
namespace Parameters {

/*************************************************************************/
EchoServer::EchoServer(int argc, char* argv[]){
	IAS_TRACER;

	::IAS::Exe::Parameters::ProgramParameters::init(argc,argv,"p:");

}
/*************************************************************************/
const String& EchoServer::getSystemName()const{

	if(!hmIndicators.count('p'))
			IAS_THROW(ConfigException("Missing -p option."));

	return hmValues.find('p')->second;
}
/*************************************************************************/
int EchoServer::getPort()const{

	if(!hmIndicators.count('p'))
			IAS_THROW(ConfigException("Missing -p option."));

	return TypeTools::StringToInt(hmValues.find('p')->second);
}
/*************************************************************************/
EchoServer::~EchoServer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void EchoServer::printCmdDesc(std::ostream& os) const{
	IAS_TRACER;
}
/*************************************************************************/
void EchoServer::printArgsDesc(std::ostream& os) const{
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
