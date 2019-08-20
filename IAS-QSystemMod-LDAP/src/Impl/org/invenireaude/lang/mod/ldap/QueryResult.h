/*
 * Generated file.
 * 
 */
#ifndef IAS_DM_AG_Impl_IMPL_47ORG_47INVENIREAUDE_47LANG_47MOD_47LDAP_47QUERYRESULT_46H
#define IAS_DM_AG_Impl_IMPL_47ORG_47INVENIREAUDE_47LANG_47MOD_47LDAP_47QUERYRESULT_46H
#include <commonlib/commonlib.h> 
#include "dm/gen/DataObjectList.h" 
#include "dm/Impl/MemoryManager.h" 
#include <org/invenireaude/lang/mod/ldap/QueryResult.h> 
#include <dm/Impl/DataObjectComplex.h>
#include <dm/Impl/TypeComplex.h>
#include <dm/Impl/MemoryManager.h>

namespace IAS {
namespace DM {
namespace AG {
namespace Impl {
namespace org {
namespace invenireaude {
namespace lang {
namespace mod {
namespace ldap {
class QueryResultType;

class QueryResult:
	public ::IAS::DM::Impl::DataObjectComplex,
	public virtual ::org::invenireaude::lang::mod::ldap::QueryResult{

public:

	virtual ~QueryResult() throw();

   virtual ::org::invenireaude::lang::mod::ldap::QueryResult* duplicateQueryResult() const;
	virtual ::IAS::String getCn() ;
	virtual const ::IAS::String getCn() const ;
	virtual ::IAS::DM::Default::String* getCnDataObject() ;
	virtual const ::IAS::DM::Default::String* getCnDataObject() const ;
	virtual bool isSetCn() const ;
	virtual void setCn(const ::IAS::String& aValue);
	virtual void unsetCn();
	virtual void setCnDataObject(::IAS::DM::Default::String* aValue);
	virtual ::IAS::String getDn() ;
	virtual const ::IAS::String getDn() const ;
	virtual ::IAS::DM::Default::String* getDnDataObject() ;
	virtual const ::IAS::DM::Default::String* getDnDataObject() const ;
	virtual bool isSetDn() const ;
	virtual void setDn(const ::IAS::String& aValue);
	virtual void unsetDn();
	virtual void setDnDataObject(::IAS::DM::Default::String* aValue);
	virtual ::IAS::String getO() ;
	virtual const ::IAS::String getO() const ;
	virtual ::IAS::DM::Default::String* getODataObject() ;
	virtual const ::IAS::DM::Default::String* getODataObject() const ;
	virtual bool isSetO() const ;
	virtual void setO(const ::IAS::String& aValue);
	virtual void unsetO();
	virtual void setODataObject(::IAS::DM::Default::String* aValue);

protected:
	QueryResult(const ::IAS::DM::Impl::Type* pType);
	friend class ::IAS::Factory<QueryResult>;
};

namespace Ext{

typedef ::IAS::DM::Impl::DataAllocator< QueryResult >::RefCountingPtr QueryResultPtr;

class QueryResultList : public ::org::invenireaude::lang::mod::ldap::Ext::QueryResultList, 
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
   QueryResultList(::IAS::DM::DataObjectList& refList) throw();
   virtual ~QueryResultList();
	virtual void add(::org::invenireaude::lang::mod::ldap::QueryResult* pValue);
	virtual int size() const ;
	virtual ::org::invenireaude::lang::mod::ldap::QueryResult* at(int iIdx);
	virtual const ::org::invenireaude::lang::mod::ldap::QueryResult* at(int iIdx)const;
};

class QueryResultType :
	public ::IAS::DM::Impl::TypeComplex,
	public virtual ::org::invenireaude::lang::mod::ldap::Ext::QueryResultType,
	public	IAS::InstanceFeatureWithFactory<  IAS::DM::Impl::ModelAllocator< QueryResultType >, QueryResultType > {
public:

	virtual ~QueryResultType() throw();

	virtual ::org::invenireaude::lang::mod::ldap::QueryResult* createQueryResult() const;
	virtual ::org::invenireaude::lang::mod::ldap::QueryResult* createQueryResult(::org::invenireaude::lang::mod::ldap::QueryResult*) const;

	virtual ::org::invenireaude::lang::mod::ldap::QueryResult* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::org::invenireaude::lang::mod::ldap::QueryResult* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static ::org::invenireaude::lang::mod::ldap::QueryResult* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const ::org::invenireaude::lang::mod::ldap::QueryResult* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

	virtual const ::IAS::DM::Property* getCnProperty() const;
	virtual const ::IAS::DM::Property* getDnProperty() const;
	virtual const ::IAS::DM::Property* getOProperty() const;


 void defineProperties(::IAS::DM::DataFactory* pDataFactory);
protected:
	QueryResultType();
	QueryResultType(const ::IAS::String& strURI,const ::IAS::String& strName,const ::IAS::DM::Type *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;


	org::invenireaude::lang::mod::ldap::QueryResult* createQueryResultImpl() const;

	const ::IAS::DM::Property* pCnProperty;
	const ::IAS::DM::Property* pDnProperty;
	const ::IAS::DM::Property* pOProperty;
   friend class IAS::Factory< QueryResultType >; 
};
};

} /* ldap */
} /* mod */
} /* lang */
} /* invenireaude */
} /* org */
} /* Impl */
} /* AG */
} /* DM */
} /* IAS */
#endif
