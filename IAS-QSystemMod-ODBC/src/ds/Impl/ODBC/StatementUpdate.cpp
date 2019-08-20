/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/StatementUpdate.cpp 
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
#include "StatementUpdate.h"
#include "exception/ODBCException.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

/*************************************************************************/
StatementUpdate::StatementUpdate(Session* pSession):
		ODBC::Statement(pSession),
		Input(*(ODBC::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementUpdate::~StatementUpdate() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
