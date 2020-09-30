/*
 * File: IAS-QSystemExe/src/parameters/MBusRepeaterParameters.cpp
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
#include "MBusRepeaterParameters.h"


#include <commonlib/commonlib.h>

namespace IAS {
namespace Exe {
namespace Parameters {

/*************************************************************************/
MBusRepeaterParameters::MBusRepeaterParameters(int argc, char* argv[]){
	IAS_TRACER;

	::IAS::Exe::Parameters::ProgramParameters::init(argc,argv,"p:i:g:D:b:B:P:T:M:N:I:X");

}
/*************************************************************************/
const String& MBusRepeaterParameters::getInterface()const{
  static const String strDefault("127.0.0.1");
  return getStringValue('i',strDefault);
}
/*************************************************************************/
const String& MBusRepeaterParameters::getGroup()const{
  return getStringValue('g');
}
/*************************************************************************/
const String& MBusRepeaterParameters::getDumpDirectory()const{
  return getStringValue('D');
}
/*************************************************************************/
bool MBusRepeaterParameters::hasDumpDirectory()const{
  return hmIndicators.count('D');
}
/*************************************************************************/
bool MBusRepeaterParameters::hasPrintStats()const{
  return hmIndicators.count('X') && hmIndicators.count('D');
}
/*************************************************************************/
int MBusRepeaterParameters::getInputBufferSize()const{
  return getIntValue('b',1000);
}
/*************************************************************************/
int MBusRepeaterParameters::getOutputBufferSize()const{
  return getIntValue('B',1000000);
}
/*************************************************************************/
int MBusRepeaterParameters::getMaxPacketSize()const{
  return getIntValue('P',128000);
}
/*************************************************************************/
int MBusRepeaterParameters::getNumThreads()const{
  return getIntValue('T',1);
}
/*************************************************************************/
int MBusRepeaterParameters::getMaxFileSize()const{
  return getIntValue('M',1024*1024);
}
/*************************************************************************/
int MBusRepeaterParameters::getMaxPacketsInFile()const{
  return getIntValue('N');
}
/*************************************************************************/
int MBusRepeaterParameters::getNewFileInterval()const{
  return getIntValue('I');
}
/*************************************************************************/
int MBusRepeaterParameters::getPort()const{
  return getIntValue('p');
}
/*************************************************************************/
MBusRepeaterParameters::~MBusRepeaterParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void MBusRepeaterParameters::printCmdDesc(std::ostream& os) const{
	IAS_TRACER;
}
/*************************************************************************/
void MBusRepeaterParameters::printArgsDesc(std::ostream& os) const{
	IAS_TRACER;
  //p:i:g:F:b:B:p:T:M:P:I:
  os<<"\t -p <port>      \t port number"<<std::endl;
  os<<"\t -i <interface> \t interface"<<std::endl;
  os<<"\t -g <group>     \t mulitcast group"<<std::endl;
  os<<"\t -b <size>      \t input buffer size"<<std::endl;
  os<<"\t -B <size>      \t cache buffer size"<<std::endl;
  os<<"\t -P <size>      \t max. packet  size"<<std::endl;
}
/*************************************************************************/
}
}
}
