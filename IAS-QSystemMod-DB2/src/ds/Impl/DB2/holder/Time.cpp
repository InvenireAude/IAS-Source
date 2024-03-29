/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/holder/Time.cpp 
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
#include "Time.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {
namespace Holder {

/*************************************************************************/
Time::Time(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQL_C_TYPE_TIME,SQL_TYPE_TIME){
	IAS_TRACER;
}
/*************************************************************************/
Time::~Time() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Time::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(iStrLenOrInd==SQL_NULL_DATA) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{


		TIME_STRUCT *pTime=bufData.getBuffer<TIME_STRUCT>();

		short    iHour;
		short    iMin;
		short    iSec;
		short    iFSec=0;


		iHour=pTime->hour;
		iMin=pTime->minute;
		iSec=pTime->second;

		::IAS::Time tsValue;
		tsValue.setTime(iHour,iMin,iSec,(int)1000*iFSec);

		pSetter->setTime(dm,tsValue);
	}

}
/*************************************************************************/
void Time::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(pSetter->isSet(dm)){

		::IAS::Time tsValue(pSetter->getValue(dm)->toTime());

		short    iHour;
		short    iMin;
		short    iSec;

		int      iFSec;

		tsValue.getTime(iHour,iMin,iSec,iFSec);
		std::cerr<<"AK:"<<tsValue.toString()<<std::endl;
		iFSec/=1000;

		TIME_STRUCT *pTime=bufData.getBuffer<TIME_STRUCT>();

		pTime->hour=iHour;
		pTime->minute=iMin;
		pTime->second=iSec;

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
