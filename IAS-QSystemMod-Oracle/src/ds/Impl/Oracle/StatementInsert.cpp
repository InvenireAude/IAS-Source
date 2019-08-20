/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/StatementInsert.cpp 
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
#include "StatementInsert.h"
#include "exception/OracleException.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
StatementInsert::StatementInsert(Session* pSession):
		Oracle::Statement(pSession),
		Input(*(Oracle::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementInsert::~StatementInsert() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
