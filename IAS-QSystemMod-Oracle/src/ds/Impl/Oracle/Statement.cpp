/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/Statement.cpp 
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
#include "Statement.h"
#include "exception/OracleException.h"

#include <sqlite3.h>

#include "Session.h"
#include "Connection.h"
#include "System.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
Statement::Statement(Session* pSession):
		pSession(pSession),
		Tools::HandleStatement(pSession->getConnection()->getSystem()->getEnvHandle()),
		iObjectMode(DS::API::Environment::OM_DEFAULT){
	IAS_TRACER;
}
/*************************************************************************/
Statement::~Statement() throw(){
	IAS_TRACER;

}
/*************************************************************************/
void Statement::setSQLText(const String& strSQLText){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"setSQL:["<<strSQLText<<"]");
	this->strSQLText=strSQLText;
}
/*************************************************************************/
void Statement::prepare(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Prepare:["<<strSQLText<<"]");

	sword rc = OCIStmtPrepare( pHandle,
			        pSession->getErrorHandle(),
			        (text *)strSQLText.c_str(),
	                (ub4) strSQLText.length(),
                    (ub4) OCI_NTV_SYNTAX,
                    (ub4) OCI_DEFAULT);

	OracleException::ThrowOnError(strSQLText,
			pSession->getErrorHandle(),
			rc);
}
/*************************************************************************/
void Statement::execute(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execute:["<<strSQLText<<"]");
	sword rc =	OCIStmtExecute(pSession->getSvcCtxHandle(),
							   pHandle,
							   pSession->getErrorHandle(),
							   1,
							   0,
							   (OCISnapshot*)NULL,
							   (OCISnapshot*)NULL,
							   OCI_DEFAULT);

	OracleException::ThrowOnError(strSQLText,
			pSession->getErrorHandle(),
			rc);
}
/*************************************************************************/
}
}
}
}
