/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/holder/DateTime.cpp
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

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {
namespace Holder {

/*************************************************************************/
DateTime::DateTime(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQL_C_TYPE_TIMESTAMP,SQL_TYPE_TIMESTAMP){
	IAS_TRACER;
}
/*************************************************************************/
DateTime::~DateTime() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DateTime::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

  IAS_LOG(LogLevel::INSTANCE.isInfo(),"Unsetme? "<<iStrLenOrInd<<" "<<SQL_NULL_DATA);

	if(iStrLenOrInd == SQL_NULL_DATA) {

		if(!bOptional)
			pSetter->unset(dm);

    IAS_LOG(LogLevel::INSTANCE.isInfo(),"Unsetme");
	}else{


		TIMESTAMP_STRUCT *pTimestamp=bufData.getBuffer<TIMESTAMP_STRUCT>();

		short    iYear;
		short    iMonth;
		short    iDay;
		short    iHour;
		short    iMin;
		short    iSec;
		short    iFSec = 0;

		iYear=pTimestamp->year;
		iMonth=pTimestamp->month;
		iDay=pTimestamp->day;
		iHour=pTimestamp->hour;
		iMin=pTimestamp->minute;
		iSec=pTimestamp->second;
		iFSec=pTimestamp->fraction*1000;

		::IAS::DateTime tsValue;
		tsValue.setDateTime(iYear,iMonth,iDay,iHour,iMin,iSec,(unsigned int)1000*iFSec);

		pSetter->setDateTime(dm,tsValue);
	}

}
/*************************************************************************/
void DateTime::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(pSetter->isSet(dm)){

		::IAS::DateTime tsValue(pSetter->getValue(dm)->toDateTime());

		short    iYear;
		short    iMonth;
		short    iDay;
		short    iHour;
		short    iMin;
		short    iSec;

		int      iFSec;

		tsValue.getDateTime(iYear,iMonth,iDay,iHour,iMin,iSec,iFSec);
		//iFSec/=1000;

		TIMESTAMP_STRUCT *pTimestamp=bufData.getBuffer<TIMESTAMP_STRUCT>();

		pTimestamp->year=iYear;
		pTimestamp->month=iMonth;
		pTimestamp->day=iDay;
		pTimestamp->hour=iHour;
		pTimestamp->minute=iMin;
		pTimestamp->second=iSec;
		pTimestamp->fraction=iFSec/1000;

		iStrLenOrInd=CBufferLen;

	}else{
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"is NULL");
		iStrLenOrInd=SQL_NULL_DATA;
	}

}
/*************************************************************************/
}
}
}
}
}
