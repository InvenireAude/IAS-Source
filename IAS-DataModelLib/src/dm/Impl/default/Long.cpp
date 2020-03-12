/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Long.cpp
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
#include "../../../dm/Impl/default/Long.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::Long* Long::duplicateLong() const{
   return Ext::LongType::FromDataObject(duplicate());
}
/*************************************************************************/
Long::Long(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectLong(pType){
	IAS_TRACER;
}
/*************************************************************************/
Long::~Long() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
LongList::LongList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void LongList::addDataObject(::IAS::DM::Default::Long* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void LongList::add(const ::IAS::Long aValue){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(aValue));
}
/*************************************************************************/
::IAS::Long LongList::at(int iIdx)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toLong();
}
/*************************************************************************/
int LongList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::Long* LongList::getDataObject(int iIdx){
	return LongType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
LongType::LongType():
    ::IAS::DM::Impl::TypeLong(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "Long", NULL){
	IAS_TRACER;
}
/*************************************************************************/
LongType::LongType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeLong(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
LongType::~LongType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* LongType::createDataObjectImpl() const{
	return createLongImpl();
}
/*************************************************************************/
Long* LongType::createLongImpl() const{
	IAS_TRACER;
	return DataAllocator<Long>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::Long* LongType::createLong() const{
	IAS_TRACER;
	return createLongImpl();
}
/*************************************************************************/
::IAS::DM::Default::Long* LongType::createLong(const ::IAS::Long aValue) const{
	IAS_TRACER;
	DataAllocator<Long>::PtrHolder ptrTmp(createLongImpl());
	ptrTmp->setLong(aValue);
	return ptrTmp.pass();
}
/*************************************************************************/
Long* LongType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< Long* >(pDataObject);
}
/*************************************************************************/
const Long* LongType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const Long* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::Long* LongType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::Long*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::Long* LongType::cast(const ::IAS::DM::DataObject* pDataObject) const{
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
