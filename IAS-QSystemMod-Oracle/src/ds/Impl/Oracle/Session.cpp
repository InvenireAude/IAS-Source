/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/Session.cpp
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
#include "System.h"

#include "SessionHandle.h"
#include "SessionHandleLocal.h"
#include "SessionHandleXA.h"

#include "StatementInsert.h"
#include "StatementCall.h"
#include "StatementFunCall.h"
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
Session::Session(Connection* pConnection):
	Impl::Session(pConnection),
	pConnection(pConnection){
	IAS_TRACER;


	if(!pConnection->getParameter()->isSetXaResource())
		ptrSessionHandle=IAS_DFT_FACTORY<SessionHandleLocal>::Create(pConnection);
	else
		ptrSessionHandle=IAS_DFT_FACTORY<SessionHandleXA>::Create(pConnection);


	IAS_CHECK_IF_NULL(pConnection);

}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
}
/*************************************************************************/
OCIEnv* Session::getEnvHandle(){
	IAS_TRACER;
	return ptrSessionHandle->getEnvHandle();
}
/*************************************************************************/
OCIError* Session::getErrorHandle(){
	IAS_TRACER;
	return ptrSessionHandle->getErrorHandle();
}
/*************************************************************************/
OCISvcCtx* Session::getSvcCtxHandle(){
	IAS_TRACER;
	return ptrSessionHandle->getSvcCtxHandle();
}
/*************************************************************************/
Connection* Session::getConnection()const{
	IAS_TRACER;
	return pConnection;
}
/*************************************************************************/
API::StatementInsert*  Session::createInsert(){
	return IAS_DFT_FACTORY<StatementInsert>::Create(this);
}
/*************************************************************************/
API::StatementCall*  Session::createCall(){
	return IAS_DFT_FACTORY<StatementCall>::Create(this);
}
/*************************************************************************/
API::StatementFunCall*  Session::createFunCall(){
	return IAS_DFT_FACTORY<StatementFunCall>::Create(this);
}
/*************************************************************************/
API::StatementSelect*  Session::createSelect(){
	return IAS_DFT_FACTORY<Oracle::StatementSelect>::Create(this);
}
/*************************************************************************/
API::StatementDelete*  Session::createDelete(){
	return IAS_DFT_FACTORY<Oracle::StatementDelete>::Create(this);
}
/*************************************************************************/
API::StatementUpdate*  Session::createUpdate(){
	return IAS_DFT_FACTORY<Oracle::StatementUpdate>::Create(this);
}
/*************************************************************************/
}
}
}
}

