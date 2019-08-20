/*
 * Generated file.
 * 
 */
#ifndef IAS_DM_AG_Impl_ORG_47INVENIREAUDE_47LANG_47MOD_47LDAP_47QUERYRESULT_46H
#define IAS_DM_AG_Impl_ORG_47INVENIREAUDE_47LANG_47MOD_47LDAP_47QUERYRESULT_46H
#include <commonlib/commonlib.h> 
#include "dm/datamodel.h" 
#include "dm/default/String.h" 
#include "dm/default/Integer.h" 
#include "dm/default/Float.h" 
#include "dm/default/Boolean.h" 
#include "dm/default/Date.h" 
#include "dm/default/Time.h" 
#include "dm/default/DateTime.h" 
namespace org {
namespace invenireaude {
namespace lang {
namespace mod {
namespace ldap {
class QueryResult : public virtual ::IAS::DM::DataObject {
public:

	virtual ::IAS::String getCn() =0;
	virtual const ::IAS::String getCn()const =0;
	virtual ::IAS::DM::Default::String* getCnDataObject() =0;
	virtual const ::IAS::DM::Default::String* getCnDataObject()const =0;
	virtual bool isSetCn()const =0;
	virtual void setCn(const ::IAS::String& aValue)=0;
	virtual void unsetCn()=0;
	virtual void setCnDataObject(::IAS::DM::Default::String* aValue)=0;
	virtual ::IAS::String getDn() =0;
	virtual const ::IAS::String getDn()const =0;
	virtual ::IAS::DM::Default::String* getDnDataObject() =0;
	virtual const ::IAS::DM::Default::String* getDnDataObject()const =0;
	virtual bool isSetDn()const =0;
	virtual void setDn(const ::IAS::String& aValue)=0;
	virtual void unsetDn()=0;
	virtual void setDnDataObject(::IAS::DM::Default::String* aValue)=0;
	virtual ::IAS::String getO() =0;
	virtual const ::IAS::String getO()const =0;
	virtual ::IAS::DM::Default::String* getODataObject() =0;
	virtual const ::IAS::DM::Default::String* getODataObject()const =0;
	virtual bool isSetO()const =0;
	virtual void setO(const ::IAS::String& aValue)=0;
	virtual void unsetO()=0;
	virtual void setODataObject(::IAS::DM::Default::String* aValue)=0;

   virtual QueryResult* duplicateQueryResult() const = 0;};
namespace Ext{
typedef ::IAS::DM::Impl::DataAllocator< ::org::invenireaude::lang::mod::ldap::QueryResult >::RefCountingPtr QueryResultPtr;
class QueryResultList {
	public:
	virtual void add(::org::invenireaude::lang::mod::ldap::QueryResult* pValue) = 0;
	virtual int size() const = 0;
	virtual ::org::invenireaude::lang::mod::ldap::QueryResult* at(int iIdx) = 0;
	virtual const ::org::invenireaude::lang::mod::ldap::QueryResult* at(int iIdx) const = 0;
};
/*************************************************************************/
class QueryResultType : public virtual ::IAS::DM::Type {
	public:

	virtual ::org::invenireaude::lang::mod::ldap::QueryResult* createQueryResult() const=0;
	virtual ::org::invenireaude::lang::mod::ldap::QueryResult* createQueryResult(::org::invenireaude::lang::mod::ldap::QueryResult* aValue) const=0;
	virtual ::org::invenireaude::lang::mod::ldap::QueryResult* cast(::IAS::DM::DataObject* pDataObject) const=0;
	virtual const ::org::invenireaude::lang::mod::ldap::QueryResult* cast(const ::IAS::DM::DataObject* pDataObject) const=0;
	virtual const ::IAS::DM::Property* getCnProperty() const=0;
	virtual const ::IAS::DM::Property* getDnProperty() const=0;
	virtual const ::IAS::DM::Property* getOProperty() const=0;
};
};

} /* ldap */
} /* mod */
} /* lang */
} /* invenireaude */
} /* org */
#endif
