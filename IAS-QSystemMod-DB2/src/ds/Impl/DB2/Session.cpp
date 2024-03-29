/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/Session.cpp
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

#include "StatementInsert.h"
#include "StatementSelect.h"
#include "StatementDelete.h"
#include "StatementUpdate.h"
#include "StatementCall.h"
#include "StatementFunCall.h"

#include "exception/DB2Exception.h"

#include <org/invenireaude/qsystem/workers/Connection.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
Session::Session(Connection* pConnection, SQLSMALLINT iAutoCommit):
  DS::Impl::Session(pConnection),
	pConnection(pConnection),
	hdbc(0){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);

	int rc=SQL_SUCCESS;

	const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter=pConnection->getParameter();

	String strLogin(dmParameter->getConnection()->isSetUser() ? dmParameter->getConnection()->getUser() : "");
	String strPassword(dmParameter->getConnection()->isSetPassword() ? dmParameter->getConnection()->getPassword() : "");
	String strDatabase(dmParameter->getConnection()->isSetLocation() ? dmParameter->getConnection()->getLocation() : "");

	if(dmParameter->isSetXaResource()){
		strDatabase=dmParameter->getXaResource();
	}

	rc = SQLAllocHandle(SQL_HANDLE_DBC, pConnection->getSystem()->getEnvHandle(), &hdbc);
	DB2Exception::ThrowOnError("SQL_HANDLE_DBC",rc,SQL_HANDLE_ENV,pConnection->getSystem()->getEnvHandle());

	rc = SQLConnect(hdbc,
					(SQLCHAR *)strDatabase.c_str(),	SQL_NTS,
					(SQLCHAR *)strLogin.c_str(), SQL_NTS,
					(SQLCHAR *)strPassword.c_str(), SQL_NTS);

	IAS_LOG(LogLevel::INSTANCE.isError(),"opening:["<<pConnection->getName()<<"], rc="<<rc<<", hdbc="<<hdbc);

	DB2Exception::ThrowOnError(pConnection->getName(),rc,SQL_HANDLE_DBC, hdbc);

	//Funny specs say that this is a POINTER  to the value (32bit integer).

	rc = SQLSetConnectAttr(this->hdbc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)(long)iAutoCommit,0);
	DB2Exception::ThrowOnError("SQLSetConnectAttr",rc,SQL_HANDLE_DBC, (SQLHANDLE)hdbc);

}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
	if(hdbc != 0)
		SQLDisconnect(hdbc);
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
	return IAS_DFT_FACTORY<DB2::StatementSelect>::Create(this);
}
/*************************************************************************/
API::StatementDelete*  Session::createDelete(){
	return IAS_DFT_FACTORY<DB2::StatementDelete>::Create(this);
}
/*************************************************************************/
API::StatementUpdate*  Session::createUpdate(){
	return IAS_DFT_FACTORY<DB2::StatementUpdate>::Create(this);
}
/*************************************************************************/
}
}
}
}

