/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/Long.cpp
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
#include "Long.h"
#include <ds/Impl/Oracle/Session.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
Long::Long(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQLT_VNU){
	IAS_TRACER;
}
/*************************************************************************/
Long::~Long() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Long::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(bNull == -1) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{
    ::IAS::Long lValue;
    sword rc = OCINumberToInt(
                pStatement->getSession()->getErrorHandle(),
                bufData.getBuffer<OCINumber>(),
                sizeof(::IAS::Long),
                OCI_NUMBER_SIGNED,
			          &lValue);

	  OracleException::ThrowOnError("OCINumberToInt", pStatement->getSession()->getErrorHandle(), rc);
		pSetter->setLong(dm,lValue);
	}

}
/*************************************************************************/
void Long::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());


	if(pSetter->isNotNull(dm)){

  	IAS_LOG(LogLevel::INSTANCE.isData(),"value:["<<pSetter->getValue(dm)->toLong()<<"]");

    ::IAS::Long lValue(pSetter->getValue(dm)->toLong());

    sword rc = OCINumberFromInt(
                pStatement->getSession()->getErrorHandle(),
                &lValue,
                sizeof(::IAS::Long),
                OCI_NUMBER_SIGNED,
			          bufData.getBuffer<OCINumber>());

	  OracleException::ThrowOnError("OCINumberFromInt", pStatement->getSession()->getErrorHandle(), rc);

		bNull=0;

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
