/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/holder/Date.cpp 
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

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {
namespace Holder {

/*************************************************************************/
Date::Date(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQL_C_TYPE_DATE,SQL_TYPE_DATE){
	IAS_TRACER;
}
/*************************************************************************/
Date::~Date() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Date::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(iStrLenOrInd==SQL_NULL_DATA) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{


		DATE_STRUCT *pDatestamp=bufData.getBuffer<DATE_STRUCT>();

		short    iYear;
		short    iMonth;
		short    iDay;


		iYear=pDatestamp->year;
		iMonth=pDatestamp->month;
		iDay=pDatestamp->day;

		::IAS::Date tsValue;
		tsValue.setDate(iYear,iMonth,iDay);
		pSetter->setDate(dm,tsValue);
	}

}
/*************************************************************************/
void Date::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(pSetter->isSet(dm)){

		::IAS::Date tsValue(pSetter->getValue(dm)->toDate());

		short    iYear;
		short    iMonth;
		short    iDay;

		tsValue.getDate(iYear,iMonth,iDay);
		std::cerr<<"AK:"<<tsValue.toString()<<std::endl;

		DATE_STRUCT *pDatestamp=bufData.getBuffer<DATE_STRUCT>();

		pDatestamp->year=iYear;
		pDatestamp->month=iMonth;
		pDatestamp->day=iDay;

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
