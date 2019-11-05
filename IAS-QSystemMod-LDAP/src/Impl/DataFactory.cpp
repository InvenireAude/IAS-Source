/*
 * Generated file.
 * 
 */
#include "DataFactory.h" 
#include <dm/gen/DataFactory.h> 
#include <Impl/org/invenireaude/lang/mod/ldap/QueryResult.h>
namespace IAS {
namespace DM {
namespace AG {
namespace Impl {
static void initialize_1572970963(::IAS::DM::Gen::DataFactory* pDataFactory){
	IAS_TRACER;


	pDataFactory->declareBuiltInTypeTmpOveride(
       IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator< org::invenireaude::lang::mod::ldap::Ext::QueryResultType >, org::invenireaude::lang::mod::ldap::Ext::QueryResultType >
 				::GetInstance());

       IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator< org::invenireaude::lang::mod::ldap::Ext::QueryResultType >, org::invenireaude::lang::mod::ldap::Ext::QueryResultType >
 				::GetInstance()->defineProperties(pDataFactory);


}

DataFactoryInitalizer_1572970963::DataFactoryInitalizer_1572970963(){
	IAS_TRACER;
   IAS::DM::Gen::DataFactory::GetInstance()->initializeWith(&initialize_1572970963);
}

DataFactoryInitalizer_1572970963::~DataFactoryInitalizer_1572970963() throw(){
	IAS_TRACER;
}

extern "C" { void ias_dm_init(){ DataFactoryInitalizer_1572970963::GetInstance(); } }
} /* Impl */
} /* AG */
} /* DM */
} /* IAS */
