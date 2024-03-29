/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/DataObjectBinary.cpp 
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
#include "DataObjectBinary.h"

#include <qs/fmt/FmtFactory.h>
#include "../Session.h"
#include "../tools/LobOpener.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
DataObjectBinary::DataObjectBinary(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
		DataObjectSimple(pStatement, pSetter, bOptional, SQLT_LBI){
}
/*************************************************************************/
DataObjectBinary::~DataObjectBinary() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
}
