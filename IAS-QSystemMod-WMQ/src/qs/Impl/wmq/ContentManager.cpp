/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/ContentManager.cpp 
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
#include "ContentManager.h"
#include "Content.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
ContentManager::ContentManager(){
	IAS_TRACER;
}
/*************************************************************************/
ContentManager::~ContentManager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Content* ContentManager::allocate(){
	IAS_TRACER;
	return allocateImpl();
}
/*************************************************************************/
Content* ContentManager::allocateImpl(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Content>::Create();
}
/*************************************************************************/
}
}
}
