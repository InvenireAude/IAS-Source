/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/txm/Impl/wmq/System.cpp 
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

namespace IAS {
namespace TXM {
namespace WMQ {

/*
 * We assume no connection pooling at this time.
 */

/*************************************************************************/
System::System(QS::WMQ::VTable* pVTable,const URI& uri):
    ptrVTable(pVTable),
	uri(uri){

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** WMQ instance created for TXM:"<<this->uri.getURIString());
}
/*************************************************************************/
API::Connection* System::createConnection(const URI& uri){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Connection for :"<<uri.getURIString());
	return IAS_DFT_FACTORY<TXM::WMQ::Connection>::Create< WMQ::System* >(this,uri);
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
#else
#define _IAS_MQM_LIB  "libmqm_r.a(libmqm_r.o)"
#endif

/*************************************************************************/
extern "C"{

::IAS::TXM::Impl::System* _ias_txm_system_mqm(const ::IAS::URI& uri){

	return IAS_DFT_FACTORY< ::IAS::TXM::WMQ::System >::Create(
			IAS_DFT_FACTORY< ::IAS::QS::WMQ::VTable >::Create(_IAS_MQM_LIB),
			uri);
}

}
/*************************************************************************/
