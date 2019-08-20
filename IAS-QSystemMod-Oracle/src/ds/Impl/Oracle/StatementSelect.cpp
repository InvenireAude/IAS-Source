/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/StatementSelect.cpp 
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
#include "StatementSelect.h"
#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
StatementSelect::StatementSelect(Session* pSession):
		Oracle::Statement(pSession),
		Input(*(Oracle::Statement*)this),
		ResultSetOutput(*(Oracle::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementSelect::~StatementSelect() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementSelect::execute(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execute:["<<strSQLText<<"]");
	sword rc =	OCIStmtExecute(pSession->getSvcCtxHandle(),
							   pHandle,
							   pSession->getErrorHandle(),
							   0,
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
