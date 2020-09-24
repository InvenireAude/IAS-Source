/*
 * Generated file.
 * 
 */
#include <commonlib/commonlib.h> 
#include "DataFactory.h" 
#include <dm/gen/DataFactory.h> 
#include "Impl/DataFactory.h" 
#include "Impl/org/invenireaude/lang/mod/ldap/QueryResult.h" 
using namespace IAS;
namespace org {
namespace invenireaude {
namespace lang {
namespace mod {
namespace ldap {
Ext::QueryResultType* DataFactory::getQueryResultType()const{
	return 
		IAS::InstanceFeatureWithFactory< 
         IAS::DM::Impl::ModelAllocator< ::IAS::DM::AG::Impl::org::invenireaude::lang::mod::ldap::Ext::QueryResultType >, 
                     ::IAS::DM::AG::Impl::org::invenireaude::lang::mod::ldap::Ext::QueryResultType >::GetInstance();
}
QueryResult* DataFactory::createQueryResult()const{
	return 
		IAS::InstanceFeatureWithFactory< 
                   IAS::DM::Impl::ModelAllocator< ::IAS::DM::AG::Impl::org::invenireaude::lang::mod::ldap::Ext::QueryResultType >, 
                     ::IAS::DM::AG::Impl::org::invenireaude::lang::mod::ldap::Ext::QueryResultType >::GetInstance()->createQueryResult();
}
QueryResult* DataFactory::createQueryResult(::org::invenireaude::lang::mod::ldap::QueryResult* aValue)const{
	return 
		IAS::InstanceFeatureWithFactory< 
                   IAS::DM::Impl::ModelAllocator< ::IAS::DM::AG::Impl::org::invenireaude::lang::mod::ldap::Ext::QueryResultType >, 
                     ::IAS::DM::AG::Impl::org::invenireaude::lang::mod::ldap::Ext::QueryResultType >::GetInstance()->createQueryResult(aValue);
}
::IAS::DM::DataFactory *DataFactory::getContaingDataFactory(){
	return ::IAS::DM::Gen::DataFactory::GetInstance();
}
DataFactory::DataFactory(){::IAS::DM::AG::Impl::DataFactoryInitalizer_1600450595::GetInstance();}
DataFactory::~DataFactory()throw(){}

} /* ldap */
} /* mod */
} /* lang */
} /* invenireaude */
} /* org */
