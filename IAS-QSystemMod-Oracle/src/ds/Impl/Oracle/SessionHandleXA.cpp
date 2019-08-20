/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/SessionHandleXA.cpp 
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
#include "SessionHandleXA.h"

#include <commonlib/commonlib.h>

#include "Connection.h"
#include "System.h"

#include "StatementInsert.h"
#include "StatementCall.h"
#include "StatementSelect.h"
#include "StatementDelete.h"
#include "StatementUpdate.h"

#include "exception/OracleException.h"

#include <qs/fmt/FmtFactory.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
static OCIEnv* _call_xaoEnv(Connection* pConnection){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(pConnection);

	if(!pConnection->getParameter()->isSetXaResource())
			IAS_THROW(InternalException("Missing XA resource name"));

	String strDBName(pConnection->getParameter()->getXaResource());

	OCIEnv*	pOCIEnv = xaoEnv((unsigned char*)strDBName.c_str());

	if(pOCIEnv == NULL){
		IAS_THROW(OracleException("OCIEnv not initialized for XA Session."));
	}

	return pOCIEnv;
}
/*************************************************************************/
SessionHandleXA::SessionHandleXA(Connection* pConnection):
	SessionHandle(_call_xaoEnv(pConnection)){

	IAS_TRACER;

	String strDBName(pConnection->getParameter()->getXaResource());

	pOCISvcCtx=xaoSvcCtx((unsigned char*)strDBName.c_str());

	if(pOCISvcCtx == NULL){
		IAS_THROW(OracleException("OCISvcCtx not initialized for XA Session."));
	}

}
/*************************************************************************/
SessionHandleXA::~SessionHandleXA() throw(){
	IAS_TRACER;

}
/*************************************************************************/
OCISvcCtx* SessionHandleXA::getSvcCtxHandle(){
	IAS_TRACER
	return pOCISvcCtx;
}
/*************************************************************************/
}
}
}
}

