/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/Date.cpp
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
#include "Date.h"

#include "../Session.h"
#include "../Connection.h"
#include "../System.h"

#include <time.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
Date::Date(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQLT_DATE),
	 descDate(pStatement->getSession()->getConnection()->getSystem()->getEnvHandle()){
	IAS_TRACER;
	*(bufData.getBuffer<OCIDateTime*>())=descDate.get();
}
/*************************************************************************/
Date::~Date() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Date::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(bNull == -1) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{

		sb2 iYear;
		ub1 iMonth;
		ub1 iDay;

		sword rc =OCIDateTimeGetDate(
				pStatement->getSession()->getEnvHandle(),
				pStatement->getSession()->getErrorHandle(),
				descDate.get(),
				&iYear,
				&iMonth,
				&iDay);

		OracleException::ThrowOnError("OCIDateTimeGetDate",
						pStatement->getSession()->getErrorHandle(),
						rc);

		::IAS::DateTime tsValue;

		tsValue.setDate(iYear,iMonth,iDay);

		pSetter->setDateTime(dm,tsValue);
	}

}
/*************************************************************************/
void Date::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(pSetter->isNotNull(dm)){

	::IAS::DateTime tsValue(pSetter->getValue(dm)->toDateTime());

		short    iYear;
		short    iMonth;
		short    iDay;

		tsValue.getDate(iYear,iMonth,iDay);

		sword rc =OCIDateTimeConstruct(
					pStatement->getSession()->getEnvHandle(),
					pStatement->getSession()->getErrorHandle(),
					descDate.get(),
					iYear,
					iMonth,
					iDay,
					0,
					0,
					0,
					0,
					0,0);

		OracleException::ThrowOnError("OCIDateTimeTimeConstruct",
						pStatement->getSession()->getErrorHandle(),
				rc);

    IAS_LOG(LogLevel::INSTANCE.isData(),"value:["<<pSetter->getValue(dm)->toString()<<"]");

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
