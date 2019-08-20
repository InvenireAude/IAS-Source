/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/txm/Impl/wmq/Session.cpp 
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
#include "Session.h"

#include <commonlib/commonlib.h>

#include "Connection.h"

namespace IAS {
namespace TXM {
namespace WMQ {

/*************************************************************************/
Session::Session(Connection* pConnection):
	pConnection(pConnection){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);
}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Connection* Session::getConnection()const{
	IAS_TRACER;
	return pConnection;
}
/*************************************************************************/
void Session::begin(){
	IAS_TRACER;

	pConnection->getConnectionHandle()->getVTable()->MQBEGIN(
			pConnection->getConnectionHandle()->mqHCONN);

}
/*************************************************************************/
void Session::commit(){
	IAS_TRACER;

	pConnection->getConnectionHandle()->getVTable()->MQCMIT(
			pConnection->getConnectionHandle()->mqHCONN);

}
/*************************************************************************/
void Session::rollback(){
	IAS_TRACER;

	pConnection->getConnectionHandle()->getVTable()->MQBACK(
			pConnection->getConnectionHandle()->mqHCONN);
}
/*************************************************************************/
}
}
}
