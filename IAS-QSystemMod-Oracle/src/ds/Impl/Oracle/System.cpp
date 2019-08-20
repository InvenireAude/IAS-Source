/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/System.cpp
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License.
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 *
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 *
 */
#include "System.h"

#include <commonlib/commonlib.h>

#include "Connection.h"
#include "exception/OracleException.h"

#include "SQLTricks.h"

#ifdef  IAS_DEMO_EXPIRATION
#include "demodist.h"
#endif

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
System::System():
 IAS::DS::Impl::System(IAS_DFT_FACTORY<Oracle::SQLTricks>::Create()){

	IAS_TRACER;

#ifdef  IAS_DEMO_EXPIRATION
IAS::DemoNotice(IAS_DEMO_EXPIRATION," (DS) for Oracle Databases");
#endif

	(void) OCIInitialize((ub4) OCI_THREADED, (dvoid *)0,
			(dvoid * (*)(dvoid *, size_t)) 0,
			(dvoid * (*)(dvoid *, dvoid *, size_t))0,
			(void (*)(dvoid *, dvoid *)) 0 );

	if(OCIEnvCreate((OCIEnv **)&envhp,
	         (ub4)OCI_THREADED,
	         (void  *)0, (void  * (*)(void  *, size_t))0,
	         (void  * (*)(void  *, void  *, size_t))0,
	         (void (*)(void  *, void  *))0,
	         (size_t)0, (void  **)0)){
	  IAS_THROW(OracleException("OCIEnvCreate",0))
	}

	hError.initialize(envhp);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** Oracle instance created.");
}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter){
	IAS_TRACER;
	 	 return IAS_DFT_FACTORY<Oracle::Connection>::Create< Oracle::System* >(this,dmParameter);
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** Oracle instance destroyed.");
}
/*************************************************************************/
}
}
}
}
/*************************************************************************/
extern "C"{
::IAS::DS::Impl::System* _ias_ds_system_oracle(){
	return IAS_DFT_FACTORY< ::IAS::DS::Impl::Oracle::System >::Create();
  }

}
