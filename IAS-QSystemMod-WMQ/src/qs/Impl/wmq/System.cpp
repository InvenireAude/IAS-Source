/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/System.cpp 
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

#include "ContentManager.h"
#include "Connection.h"
#include "VTable.h"

#ifdef  IAS_DEMO_EXPIRATION
#include "demodist.h"
#endif

namespace IAS {
namespace QS {
namespace WMQ {

/*
 * We assume no connection pooling at this time.
 */

/*************************************************************************/
System::System(VTable* pVTable):
    ptrVTable(pVTable){
	IAS_TRACER;

#ifdef  IAS_DEMO_EXPIRATION
IAS::DemoNotice(IAS_DEMO_EXPIRATION," (QS) for IBM WebSphere MQ");
#endif

}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;
	return IAS_DFT_FACTORY<QS::WMQ::Connection>::Create(this,dmConnection);
}
/*************************************************************************/
ContentManager*  System::getContentManager(){
	IAS_TRACER;
	IAS_THROW(InternalException("No content created"));
	return 0;
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** WMQ instance destroyed.");
}
/*************************************************************************/
}
}
}

#ifndef _AIX
#define _IAS_MQM_LIB  "libmqm_r.so"
#define _IAS_MQIC_LIB "libmqic_r.so"
#else
#define _IAS_MQM_LIB  "libmqm_r.a(libmqm_r.o)"
#define _IAS_MQIC_LIB "libmqic_r.a(mqic_r.o)"
#endif

/*************************************************************************/
extern "C"{

::IAS::QS::Impl::System* _ias_qs_system_mqic(){

	return IAS_DFT_FACTORY< ::IAS::QS::WMQ::System >::Create(
			IAS_DFT_FACTORY< ::IAS::QS::WMQ::VTable >::Create(_IAS_MQIC_LIB));

 }

::IAS::QS::Impl::System* _ias_qs_system_mqm(){

	return IAS_DFT_FACTORY< ::IAS::QS::WMQ::System >::Create(
			IAS_DFT_FACTORY< ::IAS::QS::WMQ::VTable >::Create(_IAS_MQM_LIB));

 }

}
/*************************************************************************/
