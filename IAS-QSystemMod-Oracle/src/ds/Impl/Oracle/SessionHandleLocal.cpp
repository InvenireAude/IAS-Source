/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/SessionHandleLocal.cpp
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
#include "SessionHandleLocal.h"

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
#include <org/invenireaude/qsystem/workers/Connection.h>


namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
/*************************************************************************/
SessionHandleLocal::SessionHandleLocal(Connection* pConnection):
	SessionHandle(pConnection->getSystem()->getEnvHandle()){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pConnection);

	const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter=pConnection->getParameter();

	String strLogin(dmParameter->getConnection()->isSetUser() ? dmParameter->getConnection()->getUser() : "");
	String strPassword(dmParameter->getConnection()->isSetPassword() ? dmParameter->getConnection()->getPassword() : "");
	String strDatabase(dmParameter->getConnection()->isSetLocation() ? dmParameter->getConnection()->getLocation() : "");

	hService.initialize(pOCIEnv);

	//TODO ? OCISessionHandleLocalGet ? OCI_LOGON2_?POOL

	sword rc = OCILogon2(pConnection->getSystem()->getEnvHandle(),
						 hError,
						 (OCISvcCtx**)&hService,
						 (const OraText*) strLogin.c_str(),strLogin.length(),
						 (const OraText*) strPassword.c_str(),strPassword.length(),
						 (const OraText*) strDatabase.c_str(),strDatabase.length(),
						 (ub4)OCI_LOGON2_STMTCACHE);

	IAS_LOG(LogLevel::INSTANCE.isError(),"opening:["<<strLogin<<"@"<<strDatabase<<"], rc="<<rc);
	OracleException::ThrowOnError(pConnection->getName(),hError,rc);

}
/*************************************************************************/
SessionHandleLocal::~SessionHandleLocal() throw(){
	IAS_TRACER;

	sword rc = OCILogoff(hService, hError);
  try{
	  OracleException::ThrowOnError("OCILogoff",hError,rc);
  }catch(...){}
}
/*************************************************************************/
OCISvcCtx* SessionHandleLocal::getSvcCtxHandle(){
	IAS_TRACER
	return hService;
}
/*************************************************************************/
}
}
}
}

