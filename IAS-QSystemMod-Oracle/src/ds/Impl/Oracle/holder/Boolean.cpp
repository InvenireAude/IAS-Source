/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/Boolean.cpp
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
#include "Boolean.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
Boolean::Boolean(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQLT_INT){
	IAS_TRACER;
}
/*************************************************************************/
Boolean::~Boolean() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Boolean::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(bNull == -1) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{
		pSetter->setBoolean(dm,*(bufData.getBuffer<bool>()));
	}

}
/*************************************************************************/
void Boolean::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());


	if(pSetter->isNotNull(dm)){

    *(bufData.getBuffer<int>())=(pSetter->getValue(dm)->toBoolean() ? 1 : 0);
		bNull=0;

    IAS_LOG(LogLevel::INSTANCE.isData(),"value:["<<pSetter->getValue(dm)->toBoolean()<<"]");

	}else{
		IAS_LOG(LogLevel::INSTANCE.isData(),"is NULL");
		bNull=-1;
	}

}
/*************************************************************************/
}
}
}
}
}
