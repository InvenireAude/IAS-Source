/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/MessageHandle.cpp 
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
#include "MessageHandle.h"

#include <commonlib/commonlib.h>

#include "../exception/WMQException.h"

#include "MessageHandle.h"
#include "ConnectionHandle.h"
#include "ObjectHandle.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {
/*************************************************************************/
MessageHandle::MessageHandle(ObjectHandle *pObjectHandle):
	hMsg(MQHM_NONE),
	pObjectHandle(pObjectHandle){
	IAS_TRACER;

	VTable* pVTable = pObjectHandle->getVTable();

	MQCMHO cmho = {MQCMHO_DEFAULT};
	cmho.Options = MQCMHO_VALIDATE; // ??

	pVTable->MQCRTMH(pObjectHandle->getConnectionHandle()->mqHCONN,&cmho,&hMsg);

}
/*************************************************************************/
MessageHandle::~MessageHandle() throw(){
	IAS_TRACER;

	VTable* pVTable =pObjectHandle->getVTable();

	if(hMsg != MQHM_NONE)
		try{
			MQDMHO dmho = {MQDMHO_DEFAULT};
			pVTable->MQDLTMH(pObjectHandle->getConnectionHandle()->mqHCONN,&hMsg,&dmho);
		}catch(Exception& e){
			IAS_LOG(LogLevel::INSTANCE.isError(),e.toString());
	};

}
/*************************************************************************/
void MessageHandle::get(API::Attributes* pAttributes){
	IAS_TRACER;

	MQIMPO impo = {MQIMPO_DEFAULT};
	MQPD   pd   = {MQPD_DEFAULT};

	impo.Options = MQIMPO_INQ_NEXT | MQIMPO_CONVERT_TYPE
	              | MQIMPO_CONVERT_VALUE;


	impo.ReturnedName.VSPtr = sName;
	impo.ReturnedName.VSBufSize = iBufLen-1;

	 MQLONG   iDataLen;
	 MQLONG   iType = MQTYPE_STRING;
	 MQCHARV  inqnames = {MQPROP_INQUIRE_ALL};

	 VTable* pVTable = pObjectHandle->getVTable();

	 while(pVTable->MQINQMP(pObjectHandle->getConnectionHandle()->mqHCONN,
	    					hMsg,&impo, &inqnames, &pd, &iType,
	    					iBufLen-1,sValue,&iDataLen)){

	    	sName[impo.ReturnedName.VSLength]=0;
	    	sValue[iDataLen] = 0;

	        String strName(sName);
	        String strValue(sValue);

	    	IAS_LOG(LogLevel::INSTANCE.isData(),strName<<"="<<strValue<<"");

	        if(!strName.compare("mcd.Fmt")){
	        	pAttributes->setValue("FMT",strValue);
	        }else if(!strName.compare("mcd.Set")){
	        	pAttributes->setValue("SET",strValue);
	        }else if(!strName.compare("mcd.Type")){
	        	pAttributes->setValue("TYPE",strValue);
	        }else{
	        	pAttributes->setValue(strName,strValue);
	        }
	    }
}
/*************************************************************************/
void MessageHandle::set(const API::Attributes* pAttributes){
	IAS_TRACER;

	MQCHARV name        = {MQCHARV_DEFAULT};
	MQSMPO  smpo        = {MQSMPO_DEFAULT};
	MQPD    mqpd        = {MQPD_DEFAULT};
	MQLONG  iType       = MQTYPE_STRING;

	for(API::Attributes::const_iterator it=pAttributes->begin();
		it!=pAttributes->end();it++){

		String                strName(it->first);
		String                strValue(it->second);

        if(!strName.compare("FMT")){
        	strName="mcd.Fmt";
        }else if(!strName.compare("SET")){
        	strName="mcd.Set";
        }else if(!strName.compare("TYPE")){
        	strName="mcd.Type";
        }else if(strName[0] == '.'){
         	continue;
        }else if(!strName.substr(0,7).compare("IAS_MQ_")){
        	continue;
        }else if(!strName.compare(QS::API::Attributes::CA_Expiration)){
        	continue;
        }

		name.VSPtr            = const_cast<char*>(strName.c_str());
		name.VSLength         = strName.length();

		VTable* pVTable = pObjectHandle->getVTable();

		IAS_LOG(LogLevel::INSTANCE.isData(),strName<<"="<<strValue<<"");

		pVTable->MQSETMP(pObjectHandle->getConnectionHandle()->mqHCONN,
					  hMsg, &smpo, &name,&mqpd,iType,
					  strValue.length(),(void*)strValue.c_str());
	}

}
/*************************************************************************/

}
}
}
}

