#include "dm/Impl/default/String.h" 
#include "dm/Impl/default/Integer.h" 
#include "dm/Impl/default/Float.h" 
#include "dm/Impl/default/Boolean.h" 
#include "dm/Impl/default/Time.h" 
#include "dm/Impl/default/Date.h" 
#include "dm/Impl/default/DateTime.h" 
#include "dm/Impl/exception/IllegalCastException.h"
/*
 * Generated file.
 * 
 */
#include "QueryResult.h" 
namespace IAS {
namespace DM {
namespace AG {
namespace Impl {
namespace org {
namespace invenireaude {
namespace lang {
namespace mod {
namespace ldap {
bool QueryResult::isSetCn() const {
	return isSet(dynamic_cast<const Ext::QueryResultType*>(pType)->getCnProperty());
}
void QueryResult::setCn(const ::IAS::String& aValue){
	setString(dynamic_cast<const Ext::QueryResultType*>(pType)->getCnProperty(),aValue);
}
void QueryResult::unsetCn(){
	unset(dynamic_cast<const Ext::QueryResultType*>(pType)->getCnProperty());
}
::IAS::String QueryResult::getCn() {
	return getString( dynamic_cast<const Ext::QueryResultType*>(pType)->getCnProperty());
}
const ::IAS::String QueryResult::getCn() const {
	return getString(dynamic_cast<const Ext::QueryResultType*>(pType)->getCnProperty());
}
::IAS::DM::Default::String* QueryResult::getCnDataObject() {
return ::IAS::DM::Impl::Default::Ext::StringType::FromDataObject((DM::DataObject*)getDataObject(dynamic_cast<const Ext::QueryResultType*>(pType)->getCnProperty()));
}
const ::IAS::DM::Default::String* QueryResult::getCnDataObject() const {
return ::IAS::DM::Impl::Default::Ext::StringType::FromDataObject((DM::DataObject*)getDataObject(dynamic_cast<const Ext::QueryResultType*>(pType)->getCnProperty()));
}
void QueryResult::setCnDataObject(::IAS::DM::Default::String* aValue){
	setDataObject(dynamic_cast<const Ext::QueryResultType*>(pType)->getCnProperty(),aValue);
}
bool QueryResult::isSetDn() const {
	return isSet(dynamic_cast<const Ext::QueryResultType*>(pType)->getDnProperty());
}
void QueryResult::setDn(const ::IAS::String& aValue){
	setString(dynamic_cast<const Ext::QueryResultType*>(pType)->getDnProperty(),aValue);
}
void QueryResult::unsetDn(){
	unset(dynamic_cast<const Ext::QueryResultType*>(pType)->getDnProperty());
}
::IAS::String QueryResult::getDn() {
	return getString( dynamic_cast<const Ext::QueryResultType*>(pType)->getDnProperty());
}
const ::IAS::String QueryResult::getDn() const {
	return getString(dynamic_cast<const Ext::QueryResultType*>(pType)->getDnProperty());
}
::IAS::DM::Default::String* QueryResult::getDnDataObject() {
return ::IAS::DM::Impl::Default::Ext::StringType::FromDataObject((DM::DataObject*)getDataObject(dynamic_cast<const Ext::QueryResultType*>(pType)->getDnProperty()));
}
const ::IAS::DM::Default::String* QueryResult::getDnDataObject() const {
return ::IAS::DM::Impl::Default::Ext::StringType::FromDataObject((DM::DataObject*)getDataObject(dynamic_cast<const Ext::QueryResultType*>(pType)->getDnProperty()));
}
void QueryResult::setDnDataObject(::IAS::DM::Default::String* aValue){
	setDataObject(dynamic_cast<const Ext::QueryResultType*>(pType)->getDnProperty(),aValue);
}
bool QueryResult::isSetO() const {
	return isSet(dynamic_cast<const Ext::QueryResultType*>(pType)->getOProperty());
}
void QueryResult::setO(const ::IAS::String& aValue){
	setString(dynamic_cast<const Ext::QueryResultType*>(pType)->getOProperty(),aValue);
}
void QueryResult::unsetO(){
	unset(dynamic_cast<const Ext::QueryResultType*>(pType)->getOProperty());
}
::IAS::String QueryResult::getO() {
	return getString( dynamic_cast<const Ext::QueryResultType*>(pType)->getOProperty());
}
const ::IAS::String QueryResult::getO() const {
	return getString(dynamic_cast<const Ext::QueryResultType*>(pType)->getOProperty());
}
::IAS::DM::Default::String* QueryResult::getODataObject() {
return ::IAS::DM::Impl::Default::Ext::StringType::FromDataObject((DM::DataObject*)getDataObject(dynamic_cast<const Ext::QueryResultType*>(pType)->getOProperty()));
}
const ::IAS::DM::Default::String* QueryResult::getODataObject() const {
return ::IAS::DM::Impl::Default::Ext::StringType::FromDataObject((DM::DataObject*)getDataObject(dynamic_cast<const Ext::QueryResultType*>(pType)->getOProperty()));
}
void QueryResult::setODataObject(::IAS::DM::Default::String* aValue){
	setDataObject(dynamic_cast<const Ext::QueryResultType*>(pType)->getOProperty(),aValue);
}
::org::invenireaude::lang::mod::ldap::QueryResult* QueryResult::duplicateQueryResult() const{
   return Ext::QueryResultType::FromDataObject(duplicate());
}
QueryResult::~QueryResult() throw(){}
QueryResult::QueryResult(const ::IAS::DM::Impl::Type* pType):
	::IAS::DM::Impl::DataObjectComplex(pType){

}
namespace Ext{
QueryResultList::QueryResultList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
QueryResultList::~QueryResultList(){}
void QueryResultList::add(::org::invenireaude::lang::mod::ldap::QueryResult* pValue){
	refDataObjectList.add(pValue);
}
int QueryResultList::size()const{
	return refDataObjectList.size();
}
::org::invenireaude::lang::mod::ldap::QueryResult* QueryResultList::at(int iIdx){
	return Ext::QueryResultType::FromDataObject(refDataObjectList.at(iIdx));
}
const ::org::invenireaude::lang::mod::ldap::QueryResult* QueryResultList::at(int iIdx)const{
	return Ext::QueryResultType::FromDataObject(refDataObjectList.at(iIdx));
}
QueryResultType::~QueryResultType() throw(){
}

QueryResultType::QueryResultType() : 
	::IAS::DM::Impl::TypeComplex("http://www.invenireaude.org/lang/mod/ldap","QueryResult",NULL){};

QueryResultType::QueryResultType(const ::IAS::String& strURI, const ::IAS::String& strName, const ::IAS::DM::Type    *pBaseType) : 
	::IAS::DM::Impl::TypeComplex(strURI,strName,pBaseType ? pBaseType : (::IAS::DM::Type*) 		IAS::InstanceFeatureWithFactory< 
                   IAS::DM::Impl::ModelAllocator< ::IAS::DM::AG::Impl::org::invenireaude::lang::mod::ldap::Ext::QueryResultType >, 
                     ::IAS::DM::AG::Impl::org::invenireaude::lang::mod::ldap::Ext::QueryResultType >::GetInstance()){};

void QueryResultType::defineProperties(::IAS::DM::DataFactory* pDataFactory){

	{
		const ::IAS::DM::Type* pPropType=pDataFactory->getType("IAS/DM/Default","String");
		pCnProperty = defineProperty("cn",pPropType,false,false);
	}
	{
		const ::IAS::DM::Type* pPropType=pDataFactory->getType("IAS/DM/Default","String");
		pDnProperty = defineProperty("dn",pPropType,false,false);
	}
	{
		const ::IAS::DM::Type* pPropType=pDataFactory->getType("IAS/DM/Default","String");
		pOProperty = defineProperty("o",pPropType,false,false);
	}
}

::IAS::DM::Impl::DataObject* QueryResultType::createDataObjectImpl() const{
	return createQueryResultImpl();
}

org::invenireaude::lang::mod::ldap::QueryResult* QueryResultType::createQueryResultImpl() const{
	IAS_TRACER;
   return ::IAS::DM::Impl::DataAllocator< org::invenireaude::lang::mod::ldap::QueryResult>::Create(this);
}

::org::invenireaude::lang::mod::ldap::QueryResult* QueryResultType::createQueryResult() const{
	IAS_TRACER;
	return createQueryResultImpl();
}

::org::invenireaude::lang::mod::ldap::QueryResult* QueryResultType::createQueryResult(::org::invenireaude::lang::mod::ldap::QueryResult* aValue) const{
	IAS_TRACER;
	::IAS::DM::Impl::DataAllocator< org::invenireaude::lang::mod::ldap::QueryResult>::PtrHolder ptrTmp(createQueryResultImpl());
	ptrTmp->setDataObject(aValue);
	return ptrTmp.pass();
}
::org::invenireaude::lang::mod::ldap::QueryResult* QueryResultType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< org::invenireaude::lang::mod::ldap::QueryResult* >(pDataObject);
}
const ::org::invenireaude::lang::mod::ldap::QueryResult* QueryResultType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const org::invenireaude::lang::mod::ldap::QueryResult* >(pDataObject);
}

::org::invenireaude::lang::mod::ldap::QueryResult* QueryResultType::cast(::IAS::DM::DataObject* pDataObject) const{
	return const_cast< ::org::invenireaude::lang::mod::ldap::QueryResult*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}

const ::org::invenireaude::lang::mod::ldap::QueryResult* QueryResultType::cast(const ::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER; 
	IAS_CHECK_IF_NULL(pDataObject);
	if(pDataObject->getType()->isAssignableTo(this)){
		return FromDataObject(pDataObject);
	}
	IAS_THROW(::IAS::DM::Impl::IllegalCastException(pDataObject->getType(), this));
}

const ::IAS::DM::Property* QueryResultType::getCnProperty() const {
	return pCnProperty;
};

const ::IAS::DM::Property* QueryResultType::getDnProperty() const {
	return pDnProperty;
};

const ::IAS::DM::Property* QueryResultType::getOProperty() const {
	return pOProperty;
};

}
} /* ldap */
} /* mod */
} /* lang */
} /* invenireaude */
} /* org */
} /* Impl */
} /* AG */
} /* DM */
} /* IAS */
