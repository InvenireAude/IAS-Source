/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/RFH1Utils.cpp 
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
#include "RFH1Utils.h"

#include <commonlib/commonlib.h>

#include "../exception/WMQException.h"

#include "RFH1Utils.h"
#include "ConnectionHandle.h"
#include "ObjectHandle.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {
/*************************************************************************/
void RFH1Utils::Read(const char* sData, size_t iDataLen, API::Attributes* pAttributes, size_t& iOffset){
	IAS_TRACER;

	PMQRFH pRFH = (PMQRFH)sData;

	if(pRFH->StrucLength > iDataLen)
		IAS_THROW(BadUsageException("pRFH->StrucLength < iDataLen"));

	IAS_DFT_FACTORY<Buffer>::PtrHolder ptrBuffer(IAS_DFT_FACTORY<Buffer>::Create(pRFH->StrucLength+1));

	memcpy(ptrBuffer->getBuffer<char>(), sData, pRFH->StrucLength);

	ptrBuffer->getBuffer<char>()[pRFH->StrucLength] = 0;

	char* sValues = ptrBuffer->getBuffer<char>() + sizeof(MQRFH);

	while(*sValues){

		const char *sName = sValues;

		while(*sValues && *sValues > ' ')
			sValues++;

		if(!*sValues)
			IAS_THROW(BadUsageException("Parse error in RFH V1, no value provided."));

		*sValues++ = 0;

		while(*sValues && *sValues == ' ')
			sValues++;

		if(*sValues != '"')
			IAS_THROW(BadUsageException("Parse error in RFH V1, expected '\"'."));

		*sValues++;
		const char *sValue = sValues;

		while(*sValues && *sValues != '"')
			sValues++;

		if(*sValues != '"')
			IAS_THROW(BadUsageException("Parse error in RFH V1, expected second '\"'."));

		*sValues++ = 0;

		while(*sValues && *sValues == ' ')
			sValues++;

		pAttributes->setValue(sName,sValue);
	}

	iOffset = pRFH->StrucLength;
}

/*************************************************************************/
void RFH1Utils::Write(Buffer* pBuffer,const API::Attributes* pAttributes, size_t& iDataLen){
	IAS_TRACER;

	StringStream ssResult;

	for(API::Attributes::const_iterator it=pAttributes->begin();
			it!=pAttributes->end();it++){

		String strName(it->first);
		String strValue(it->second);

		if(!strName.substr(0,3).compare("jms") ||
		   !strName.substr(0,3).compare("MID") ||
		   !strName.substr(0,3).compare("CID") ||
		   !strName.substr(0,7).compare("IAS_MQ_")){
			continue;
		} else if(!strName.compare(QS::API::Attributes::CA_Expiration)) {
			continue;
		}

		ssResult<<strName<<" \""<<strValue<<"\" ";
	}

	ssResult<<"        ";

	const String strResult(ssResult.str());

	pBuffer->reserve(sizeof(MQRFH) + strResult.length() + 32);

	static const MQRFH _dftMQRFH = { MQRFH_DEFAULT };

	PMQRFH pMQRFH = pBuffer->getBuffer<MQRFH>();

	memcpy(pMQRFH, &_dftMQRFH, sizeof(MQRFH));
	memcpy((void*)(pMQRFH+1), strResult.c_str(), strResult.length());

	iDataLen = sizeof(MQRFH)+strResult.length();
	iDataLen &= 0xffffff8;

	pMQRFH->StrucLength =  iDataLen;


}
/*************************************************************************/

}
}
}
}

