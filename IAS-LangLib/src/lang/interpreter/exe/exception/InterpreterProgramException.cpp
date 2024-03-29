/*
 * File: IAS-LangLib/src/lang/interpreter/exe/exception/InterpreterProgramException.cpp
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
#include "InterpreterProgramException.h"
#include<lang/log/LogLevel.h>

namespace IAS{
namespace Lang {
namespace Interpreter{
namespace Exe{
/*************************************************************************/
InterpreterProgramException::InterpreterProgramException(DM::DataObject* dmValue):
		dmValue(dmValue){
	IAS_TRACER;

	if(!dmValue)
		return;

	if(dmValue->getType()->isDataObjectType()){

		const DM::ComplexType *pComplexType = dmValue->getType()->asComplexType();

		const DM::PropertyList& lstProperties(pComplexType->getProperties());

		StringStream ssInfo;

		for(int iIdx=0; iIdx<lstProperties.getSize(); iIdx++){
			const DM::Property *pProperty = lstProperties.getProperty(iIdx);
			if(!pProperty->getType()->isDataObjectType() && dmValue->isSet(pProperty) && dmValue->getDataObject(pProperty) != NULL)
				ssInfo<<(iIdx ? ",":"")<<pProperty->getName()<<" "<<dmValue->getString(pProperty);
		}
		setInfo(ssInfo.str());
	}else
		setInfo(dmValue->toString());

}
/*************************************************************************/
InterpreterProgramException::~InterpreterProgramException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* InterpreterProgramException::getName(){
	IAS_TRACER;
	return "InterpreterProgramException";
}
/*************************************************************************/
DM::DataObject* InterpreterProgramException::getValue()const{
	IAS_TRACER;
	return dmValue;
}
/*************************************************************************/
}
}
}
}
