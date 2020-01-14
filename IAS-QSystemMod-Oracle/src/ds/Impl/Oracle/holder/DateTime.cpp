/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/DateTime.cpp
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
#include "DateTime.h"

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
DateTime::DateTime(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQLT_TIMESTAMP),
	 descTimeStamp(pStatement->getSession()->getConnection()->getSystem()->getEnvHandle()){
	IAS_TRACER;
	*(bufData.getBuffer<OCIDateTime*>())=descTimeStamp.get();
}
/*************************************************************************/
DateTime::~DateTime() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DateTime::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(bNull == -1) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{

		sb2 iYear;
		ub1 iMonth;
		ub1 iDay;

		ub1 iHour;
		ub1 iMin;
		ub1 iSec;
		ub4 iFSec;

		sword rc =OCIDateTimeGetDate(
				pStatement->getSession()->getEnvHandle(),
				pStatement->getSession()->getErrorHandle(),
				descTimeStamp.get(),
				&iYear,
				&iMonth,
				&iDay);

		OracleException::ThrowOnError("OCIDateTimeGetDate",
				pStatement->getSession()->getErrorHandle(),
						rc);

		rc =OCIDateTimeGetTime(
						pStatement->getSession()->getEnvHandle(),
						pStatement->getSession()->getErrorHandle(),
						descTimeStamp.get(),
						&iHour,
						&iMin,
						&iSec,
						&iFSec);

		OracleException::ThrowOnError("OCIDateTimeTimeGetDateTime",
							pStatement->getSession()->getErrorHandle(),
							rc);


		::IAS::DateTime tsValue;

		tsValue.setDateTime(iYear,iMonth,iDay,iHour,iMin,iSec,iFSec/1000);

		pSetter->setDateTime(dm,tsValue);
	}

}
/*************************************************************************/
void DateTime::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(pSetter->isNotNull(dm)){

		::IAS::DateTime tsValue(pSetter->getValue(dm)->toDateTime());

		short    iYear;
		short    iMonth;
		short    iDay;
		short    iHour;
		short    iMin;
		short    iSec;
		int      iFSec;

		tsValue.getDateTime(iYear,iMonth,iDay,iHour,iMin,iSec,iFSec);

		iFSec*=1000;
		sword rc =OCIDateTimeConstruct(
					pStatement->getSession()->getEnvHandle(),
					pStatement->getSession()->getErrorHandle(),
					descTimeStamp.get(),
					iYear,
					iMonth,
					iDay,
					iHour,
					iMin,
					iSec,
					iFSec,
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
