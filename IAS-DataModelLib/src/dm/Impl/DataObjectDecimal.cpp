/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectDecimal.cpp
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
#include "../../dm/Impl/DataObjectDecimal.h"
#include <commonlib/commonlib.h>
#include "../../dm/Type.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectDecimal::DataObjectDecimal(const Type *pType):DataObjectBasic(pType),aValue(0){
	IAS_TRACER;
}
/*************************************************************************/
DataObjectDecimal::~DataObjectDecimal() throw(){
	IAS_TRACER;

}
/*************************************************************************/
String DataObjectDecimal::toString()const{
	IAS_TRACER;
	return aValue.toString();
}
/*************************************************************************/
bool DataObjectDecimal::toBoolean()const{
	IAS_TRACER;
	return ((long)aValue) != 0;
}
/*************************************************************************/
int DataObjectDecimal::toInteger()const{
	IAS_TRACER;
	return (long)aValue;
}
/*************************************************************************/
Float DataObjectDecimal::toFloat()const{
	IAS_TRACER;
	return (Float)aValue;
}
/*************************************************************************/
IAS::Date DataObjectDecimal::toDate()const{
	IAS_TRACER;
	Date tsValue;
	time_t tmpValue((long)aValue);
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
IAS::Time DataObjectDecimal::toTime()const{
	IAS_TRACER;
	Time tsValue;
	time_t tmpValue((long)aValue);
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
IAS::DateTime DataObjectDecimal::toDateTime()const{
	IAS_TRACER;
	DateTime tsValue;
	time_t tmpValue((long)aValue);
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
IAS::Decimal DataObjectDecimal::toDecimal()const{
	IAS_TRACER;
	return aValue;
}
/*************************************************************************/
void DataObjectDecimal::setString(const String& strValue){
	IAS_TRACER;
	this->aValue = strValue;
}
/*************************************************************************/
void DataObjectDecimal::setDecimal(const Decimal& aValue){
	IAS_TRACER;
	this->aValue = aValue;
}
/*************************************************************************/
void DataObjectDecimal::setBoolean(bool bValue){
	IAS_TRACER;
	this->aValue = (long)bValue;
}
/*************************************************************************/
void DataObjectDecimal::setFloat(Float fValue){
	IAS_TRACER;
	this->aValue = fValue;
}
/*************************************************************************/
void DataObjectDecimal::setDateTime(const IAS::DateTime& tValue){
	IAS_TRACER;
	time_t tmpValue;
	tValue.toPosixTime(tmpValue);
	this->aValue=(long)tmpValue;
}
/*************************************************************************/
void DataObjectDecimal::setDate(const IAS::Date& tValue){
	IAS_TRACER;
	time_t tmpValue;
	tValue.toPosixTime(tmpValue);
	this->aValue=(long)tmpValue;
}
/*************************************************************************/
void DataObjectDecimal::setTime(const  IAS::Time& tValue){
	IAS_TRACER;
	time_t tmpValue;
	tValue.toPosixTime(tmpValue);
	this->aValue=(long)tmpValue;
}
/*************************************************************************/
void DataObjectDecimal::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	aValue = pDataObject->toDecimal();
}
/*************************************************************************/
bool DataObjectDecimal::equals(const IAS::DM::DataObject* pDataObject)const{

	IAS_TRACER;

	if(!pDataObject)
		return false;

	if(!pDataObject->getType()->equals(pType))
		return false;

	return aValue == pDataObject->toDecimal();
}
/*************************************************************************/
}
}
}
