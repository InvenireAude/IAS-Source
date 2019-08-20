/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/BagHandle.cpp 
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
#include "BagHandle.h"

#include <commonlib/commonlib.h>
#include "../exception/WMQException.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {
/*************************************************************************/
BagHandle::BagHandle(VTable* pVTable, MQLONG iOptions):
	mqHBAG(MQHB_UNUSABLE_HBAG),
	pVTable(pVTable){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pVTable);
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"mqBag="<<iOptions);

	pVTable->mqCreateBag(iOptions,&mqHBAG);

}
/*************************************************************************/
BagHandle::~BagHandle() throw(){
	IAS_TRACER;

	if(mqHBAG != MQHB_UNUSABLE_HBAG){

		try{
			pVTable->mqDeleteBag(&mqHBAG);
		}catch(Exception& e){
			IAS_LOG(LogLevel::INSTANCE.isError(),e.toString());
		};

	}
}
/*************************************************************************/

}
}
}
}
