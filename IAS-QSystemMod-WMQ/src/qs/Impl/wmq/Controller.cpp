/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Controller.cpp 
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
#include "Controller.h"
#include<qs/log/LogLevel.h>

#include "Session.h"
#include "System.h"
#include "Connection.h"
#include "Message.h"
#include <commonlib/commonlib.h>
#include <qs/Impl/shm/System.h>
#include <qs/Impl/shm/shared/Queue.h>
#include <qs/Impl/shm/shared/MsgEntry.h>
#include <qs/Impl/shm/shared/QueueTable.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Controller::Controller(Session* pSession, const API::Destination& refDestination):
	Manageable(pSession),
	pVTable(getSession()->getConnection()->getSystem()->getVTable()),
	myDestination(refDestination){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Opening: "<<refDestination.getName());

	MQOD     od = {MQOD_DEFAULT};

	MQLONG iOptions=MQOO_OUTPUT | MQOO_FAIL_IF_QUIESCING;

	strncpy(od.ObjectName,refDestination.getName().c_str(),MQ_Q_NAME_LENGTH);

	ptrObjectHandler=IAS_DFT_FACTORY<Handle::ObjectHandle>::Create(
			getSession()->getConnection()->getConnectionHandle(),
			refDestination.getName(),
			MQOT_Q,
			MQOO_INQUIRE);

}
/*************************************************************************/
Controller::~Controller() throw(){
	IAS_TRACER;

}
/*************************************************************************/
unsigned int Controller::getNumMessages(){
	IAS_TRACER;

	MQLONG tSelectors[1];

	MQLONG tValues[1];

	tSelectors[0]=MQIA_CURRENT_Q_DEPTH;
	pVTable->MQINQ(getSession()->getConnection()->getConnectionHandle()->mqHCONN,
		       	   ptrObjectHandler->hObj,
				   (MQLONG)1,
				   (PMQLONG)tSelectors,
				   (MQLONG)1,
				   (PMQLONG)tValues,
				   (MQLONG)0,
				   (PMQCHAR)0);

	return tValues[0];

}
/*************************************************************************/

}
}
}
