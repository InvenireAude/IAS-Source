/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/StatementCall.cpp
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
#include "StatementCall.h"
#include "exception/OracleException.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
StatementCall::StatementCall(Session* pSession):
		Oracle::Statement(pSession),
		Output(*(Oracle::Statement*)this){
	IAS_TRACER;
}
/*************************************************************************/
StatementCall::~StatementCall() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
