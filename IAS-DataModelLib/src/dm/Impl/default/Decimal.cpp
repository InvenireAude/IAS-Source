/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Decimal.cpp
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
#include "../../../dm/Impl/default/Decimal.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::Decimal* Decimal::duplicateDecimal() const{
   return Ext::DecimalType::FromDataObject(duplicate());
}
/*************************************************************************/
Decimal::Decimal(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectDecimal(pType){
	IAS_TRACER;
}
/*************************************************************************/
Decimal::~Decimal() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
DecimalList::DecimalList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void DecimalList::addDataObject(::IAS::DM::Default::Decimal* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void DecimalList::add(const ::IAS::Decimal& aValue){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(aValue));
}
/*************************************************************************/
::IAS::Decimal DecimalList::at(int iIdx)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toDecimal();
}
/*************************************************************************/
int DecimalList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::Decimal* DecimalList::getDataObject(int iIdx){
	return DecimalType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
DecimalType::DecimalType():
    ::IAS::DM::Impl::TypeDecimal(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "Decimal", NULL){
	IAS_TRACER;
}
/*************************************************************************/
DecimalType::DecimalType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeDecimal(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
DecimalType::~DecimalType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* DecimalType::createDataObjectImpl() const{
	return createDecimalImpl();
}
/*************************************************************************/
Decimal* DecimalType::createDecimalImpl() const{
	IAS_TRACER;
	return DataAllocator<Decimal>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::Decimal* DecimalType::createDecimal() const{
	IAS_TRACER;
	return createDecimalImpl();
}
/*************************************************************************/
::IAS::DM::Default::Decimal* DecimalType::createDecimal(const ::IAS::Decimal& aValue) const{
	IAS_TRACER;
	DataAllocator<Decimal>::PtrHolder ptrTmp(createDecimalImpl());
	ptrTmp->setDecimal(aValue);
	return ptrTmp.pass();
}
/*************************************************************************/
Decimal* DecimalType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< Decimal* >(pDataObject);
}
/*************************************************************************/
const Decimal* DecimalType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const Decimal* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::Decimal* DecimalType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::Decimal*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::Decimal* DecimalType::cast(const ::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataObject);
	if(pDataObject->getType()->isAssignableTo(this)){
		return FromDataObject(pDataObject);
	}

	IAS_THROW(IllegalCastException(pDataObject->getType(), this));
}
/*************************************************************************/
}
}
}
} /* DM */
} /* IAS */
