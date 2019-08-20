/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/SessionTransacted.cpp 
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

#include <commonlib/commonlib.h>
#include "SessionHandle.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
SessionTransacted::SessionTransacted(Connection* pConnection):
	Session(pConnection){
	IAS_TRACER;
	//IAS_THROW(InternalException("SessionTransacted is not implemented!"));
}
/*************************************************************************/
SessionTransacted::~SessionTransacted() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionTransacted::commit(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Commiting ...");

	sword rc = OCITransCommit(ptrSessionHandle->getSvcCtxHandle(),
							  ptrSessionHandle->getErrorHandle(), OCI_DEFAULT);
	OracleException::ThrowOnError("COMMIT",ptrSessionHandle->getErrorHandle(),rc);

}
/*************************************************************************/
void SessionTransacted::rollback(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Rolling back ...");

	Thread::Cancellation tc(true);

	sword rc = OCITransRollback(ptrSessionHandle->getSvcCtxHandle(),
							    ptrSessionHandle->getErrorHandle(), OCI_DEFAULT);

	OracleException::ThrowOnError("COMMIT",ptrSessionHandle->getErrorHandle(),rc);
}
/*************************************************************************/
Session::TransactionMode SessionTransacted::getMode()const{
	return Session::SM_Transacted;
}
/*************************************************************************/
}
}
}
}
