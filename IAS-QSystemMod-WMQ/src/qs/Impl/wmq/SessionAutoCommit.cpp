/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/SessionAutoCommit.cpp 
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
#include "SessionAutoCommit.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
SessionAutoCommit::SessionAutoCommit(Connection* pConnection):
	Session(pConnection){
	IAS_TRACER;
}

/*************************************************************************/
SessionAutoCommit::~SessionAutoCommit() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionAutoCommit::commit(){
	IAS_TRACER;
	IAS_THROW(InternalException("TODO  not transacted  !"))
}
/*************************************************************************/
void SessionAutoCommit::rollback(){
	IAS_TRACER;
	IAS_THROW(InternalException("TODO  not transacted  !"))
}
/*************************************************************************/
Session::TransactionMode SessionAutoCommit::getMode()const{
	return Session::SM_NonTransacted;
}
/*************************************************************************/
}
}
}
