/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectLong.cpp
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
#include "../../dm/Impl/DataObjectLong.h"
#include <commonlib/commonlib.h>
#include "../../dm/Type.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectLong::DataObjectLong(const Type *pType):DataObjectBasic(pType),fValue(0.0){
	IAS_TRACER;
}
/*************************************************************************/
DataObjectLong::~DataObjectLong() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String DataObjectLong::toString()const{
	IAS_TRACER;
	return TypeTools::LongToString(fValue);
}
/*************************************************************************/
bool DataObjectLong::toBoolean()const{
	IAS_TRACER;
	return fValue != 0;
}
/*************************************************************************/
int DataObjectLong::toInteger()const{
	IAS_TRACER;
	return (int)fValue;
}
/*************************************************************************/
Long DataObjectLong::toLong()const{
	IAS_TRACER;
	return fValue;
}
/*************************************************************************/
Decimal DataObjectLong::toDecimal()const{
	IAS_TRACER;
	return fValue;
}
/*************************************************************************/
void DataObjectLong::setString(const String& strValue){
	IAS_TRACER;
	fValue=TypeTools::StringToLong(strValue);
}
/*************************************************************************/
void DataObjectLong::setInteger(int iValue){
	IAS_TRACER;
	fValue = (int)iValue;
}
/*************************************************************************/
void DataObjectLong::setBoolean(bool bValue){
	IAS_TRACER;
	fValue = (Long)bValue;
}
/*************************************************************************/
void DataObjectLong::setLong(Long fValue){
	IAS_TRACER;
	this->fValue = fValue;
}
/*************************************************************************/
void DataObjectLong::setDecimal(const Decimal& aValue){
	IAS_TRACER;
	this->fValue = (Long)aValue;
}
/*************************************************************************/
void DataObjectLong::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	fValue = pDataObject->toLong();
}
/*************************************************************************/
bool DataObjectLong::equals(const IAS::DM::DataObject* pDataObject)const{

	IAS_TRACER;

	if(!pDataObject)
		return false;

	if(!pDataObject->getType()->equals(pType))
		return false;

	return fValue == pDataObject->toLong();
}
/*************************************************************************/
}
}
}
