/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/txm/Impl/wmq/Connection.cpp 
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
#include "Connection.h"

#include <commonlib/commonlib.h>

#include "Session.h"
#include "System.h"

namespace IAS {
namespace TXM {
namespace WMQ {

/*************************************************************************/
Connection::Connection(WMQ::System* pSystem,const URI& uri):
	strName(uri.getHost()), //TODO change to something similar to jms/wqm uri eg.
	//mqic://host:port/QUEUE?QueueManager=queueManager
	//mqm://queueManager/QUEUE
	pSystem(pSystem){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Connection:"<<strName);
	ptrConnectionHandler=IAS_DFT_FACTORY<QS::WMQ::Handle::ConnectionHandle>::Create(pSystem->getVTable(),strName);
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Connection:"<<strName<<" is ok.");
}
/*************************************************************************/
API::Session* Connection::createSession(){
	IAS_TRACER;

	return IAS_DFT_FACTORY<TXM::WMQ::Session>::Create(this);
}
/*************************************************************************/
WMQ::System* Connection::getSystem(){
	IAS_TRACER;
	return pSystem;
}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;

	/* We do not want to disconnect here - assume that resource sessions will close this connection */
	/* I can see no other (except for thread local variables) method to deal with already the connected state.*/

	ptrConnectionHandler->mqHCONN=MQHC_DEF_HCONN;

}
/*************************************************************************/
}
}
}
