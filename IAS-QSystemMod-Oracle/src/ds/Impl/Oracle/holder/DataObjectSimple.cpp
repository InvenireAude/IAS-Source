/*
 * Copyright (C) 2017, Albert Krzymowski
 * Copyright (C) 2017, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/DataObjectSimple.cpp 
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
#include "DataObjectSimple.h"

#include <qs/fmt/FmtFactory.h>
#include "../Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
DataObjectSimple::DataObjectSimple(Statement* pStatement,
		 DM::Tools::Setter* pSetter,
		 bool bOptional,
		 ub2    iOCIType):
		Base(pStatement, pSetter, bOptional, CBufferLen, iOCIType){
	IAS_TRACER;
}
/*************************************************************************/
DataObjectSimple::~DataObjectSimple() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DataObjectSimple::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(bNull == -1) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{

		DM::DataObjectPtr dmValue;
		QS::Fmt::Formatter *pFormatter=pStatement->getSession()->getFormatter();
		StringStream ssValue((char*)bufData);

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value="<<(char*)bufData);
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value="<<iLen);

		pFormatter->read(dmValue,ssValue);
		pSetter->setDataObject(dm,dmValue);
	}

}
/*************************************************************************/
void DataObjectSimple::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());


	if(pSetter->isSet(dm)){

		DM::DataObjectPtr dmValue;
		QS::Fmt::Formatter *pFormatter=pStatement->getSession()->getFormatter();

		StringStream ssValue;
		pFormatter->write(pSetter->getValue(dm),ssValue);

		//TODO avoid this coping.
		String strValue(ssValue.str());
		String::size_type iSize(strValue.length()+1);

		assureBufferSize(iSize);

		memcpy((char*)bufData,strValue.c_str(),iSize);

		iLen = iSize -1 ;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value="<<(char*)bufData);
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value="<<iLen);

		bNull=0;

	}else{
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"is NULL");
		bNull=-1;
	}

}
/*************************************************************************/
}
}
}
}
}
