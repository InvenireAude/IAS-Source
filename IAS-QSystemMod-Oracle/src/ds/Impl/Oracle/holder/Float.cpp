/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/Float.cpp
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
#include "Float.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
Float::Float(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQLT_BDOUBLE){
	IAS_TRACER;
}
/*************************************************************************/
Float::~Float() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Float::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath()<<"="<<*bufData.getBuffer<double>());

	if(bNull == -1) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{

		pSetter->setFloat(dm,*(bufData.getBuffer<double>()));
	}

}
/*************************************************************************/
void Float::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());


	if(pSetter->isNotNull(dm)){

		*(bufData.getBuffer<double>())=pSetter->getValue(dm)->toFloat();
   	IAS_LOG(LogLevel::INSTANCE.isData(),"value:["<<pSetter->getValue(dm)->toFloat()<<"]");

		bNull=0;

	}else{
		IAS_LOG(LogLevel::INSTANCE.isData()," is NULL");
		bNull=-1;
	}

}
/*************************************************************************/
}
}
}
}
}
