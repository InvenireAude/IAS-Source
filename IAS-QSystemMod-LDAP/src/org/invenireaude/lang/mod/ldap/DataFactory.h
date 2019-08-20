/*
 * Generated file.
 * 
 */
#ifndef IAS_DM_AG_Impl_ORG_47INVENIREAUDE_47LANG_47MOD_47LDAP_47DATAFACTORY_46H
#define IAS_DM_AG_Impl_ORG_47INVENIREAUDE_47LANG_47MOD_47LDAP_47DATAFACTORY_46H
#include <commonlib/commonlib.h> 
#include "dm/datamodel.h" 
#include "dm/gen/DataObjectList.h" 
#include "dm/Impl/MemoryManager.h" 
#include "Declarations.h" 
namespace org {
namespace invenireaude {
namespace lang {
namespace mod {
namespace ldap {
/*************************************************************************/
class DataFactory :
   public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<DataFactory>, DataFactory >{
	public:

	Ext::QueryResultType* getQueryResultType()const;
	QueryResult*     createQueryResult()const;
	QueryResult*     createQueryResult(::org::invenireaude::lang::mod::ldap::QueryResult* aValue)const;


	virtual ~DataFactory() throw();

	::IAS::DM::DataFactory *getContaingDataFactory();

protected:
	DataFactory();
   friend class IAS::Factory< DataFactory >;

};


} /* ldap */
} /* mod */
} /* lang */
} /* invenireaude */
} /* org */
#endif
