/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/SessionTransacted.cpp 
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
#include "SessionTransacted.h"
#include "Connection.h"
#include "handler/ConnectionHandle.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
SessionTransacted::SessionTransacted(Connection* pConnection):
	Session(pConnection){
	IAS_TRACER;
	//TODO property to do MQBEGIN
}
/*************************************************************************/
SessionTransacted::~SessionTransacted() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionTransacted::commit(){
	IAS_TRACER;

	pConnection->getConnectionHandle()->getVTable()->MQCMIT(
			pConnection->getConnectionHandle()->mqHCONN);

}
/*************************************************************************/
void SessionTransacted::rollback(){
	IAS_TRACER;

	pConnection->getConnectionHandle()->getVTable()->MQBACK(
			pConnection->getConnectionHandle()->mqHCONN);
}
/*************************************************************************/
Session::TransactionMode SessionTransacted::getMode()const{
	return Session::SM_Transacted;
}
/*************************************************************************/
}
}
}
