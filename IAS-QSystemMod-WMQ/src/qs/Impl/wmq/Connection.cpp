/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Connection.cpp 
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

#include "SessionAutoCommit.h"
#include "SessionTransacted.h"
#include "SessionXAManaged.h"

#include "Content.h"
#include "Message.h"
#include "ContentManager.h"
#include "System.h"
#include "Administrator.h"
#include "Tools.h"
#include "handler/ObjectHandle.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Connection::Connection(WMQ::System* pSystem,const ::org::invenireaude::qsystem::workers::Connection* dmConnection):
	strName(dmConnection->getHost()), //TODO change to something similar to jms/wqm uri eg.
	//mqic://host:port/QUEUE?QueueManager=queueManager
	//mqm://queueManager/QUEUE
	dmConnection(dmConnection->duplicateConnection()),
	pSystem(pSystem),
	iNumTransacted(0){
	IAS_TRACER;

	ptrConnectionHandler=IAS_DFT_FACTORY<Handle::ConnectionHandle>::Create(pSystem->getVTable(),strName);

	IAS_DFT_FACTORY<Handle::ObjectHandle>::PtrHolder  ptrObjectHandler;
	ptrObjectHandler=IAS_DFT_FACTORY<Handle::ObjectHandle>::Create(
				ptrConnectionHandler,
				"",
				MQOT_Q_MGR,
				MQOO_INQUIRE);


	MQLONG tabSelectors[] = {MQCA_Q_MGR_NAME};

	const MQLONG iCharDataSize = MQ_Q_MGR_NAME_LENGTH + 1;
	char tabChrAttrs[iCharDataSize + 1] = {0};

	ptrConnectionHandler->getVTable()->MQINQ(ptrConnectionHandler->mqHCONN,
														     ptrObjectHandler->hObj,
														     1,
															 tabSelectors,
															 0,
															 0,
															 iCharDataSize,
															 tabChrAttrs);

	strQMgrName = Tools::GetMQMDValue(tabChrAttrs,MQ_Q_MGR_NAME_LENGTH);
	IAS_LOG(WMQ::LogLevel::INSTANCE.isInfo(),"strQMgrName:["<<strQMgrName<<"]");
}
/*************************************************************************/
API::Session* Connection::createSession(API::Session::TransactionMode iMode){
	IAS_TRACER;

	switch(iMode){

		case API::Session::SM_Transacted:
			return IAS_DFT_FACTORY<QS::WMQ::SessionTransacted>::Create(this);

		case API::Session::SM_NonTransacted:
			return IAS_DFT_FACTORY<QS::WMQ::SessionAutoCommit>::Create(this);

		case API::Session::SM_XAManaged:
			return IAS_DFT_FACTORY<QS::WMQ::SessionXAManaged>::Create(this);

	default:
		IAS_THROW(BadUsageException("Unsupported session mode requested for the WMQ module."));
	}

}
/*************************************************************************/
API::Message* Connection::createMessage(){
	IAS_TRACER;
	return IAS_DFT_FACTORY< QS::WMQ::Message >::Create();
}
/*************************************************************************/
API::ContentManager* Connection::getContentManager(){
	IAS_TRACER;
	return pSystem->getContentManager();
}
/*************************************************************************/
WMQ::System* Connection::getSystem(){
	IAS_TRACER;
	return pSystem;
}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Administrator* Connection::createAdministrator(){
	IAS_TRACER;

	return IAS_DFT_FACTORY<Administrator>::Create(this);
}
/*************************************************************************/
}
}
}
