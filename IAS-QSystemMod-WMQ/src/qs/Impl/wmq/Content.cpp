/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Content.cpp 
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
#include "Content.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Content::Content(){

	IAS_TRACER;

	pData=StreamMemoryBuffer::Create(MemoryManager::GetInstance());

	ptrSMB=IAS_DFT_FACTORY<StreamMemoryBuffer>::Create(pData,MemoryManager::GetInstance());

	this->init(ptrSMB);
}
/*************************************************************************/
Content::~Content() throw(){
	IAS_TRACER;
	if(pData){
	   	StreamMemoryBuffer::Destroy(pData,MemoryManager::GetInstance());
	}
}
/*************************************************************************/

}
}
}
