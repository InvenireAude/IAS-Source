/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Manageable.cpp 
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
#include "Manageable.h"

#include <commonlib/commonlib.h>

#include "Message.h"
#include "Session.h"
#include "Connection.h"
#include "System.h"

#include "exception/WMQException.h"

namespace IAS {
namespace QS {
namespace WMQ {

struct _MQROMapper {

	typedef HashMapWithStringKey<MQLONG> Map;

	Map hmValues;

	_MQROMapper(){
		 hmValues["EXCEPTION"]=MQRO_EXCEPTION;
		 hmValues["EXCEPTION_WITH_DATA"]=MQRO_EXCEPTION_WITH_DATA;
		 hmValues["EXCEPTION_WITH_FULL_DATA"]=MQRO_EXCEPTION_WITH_FULL_DATA;
		 hmValues["EXPIRATION"]=MQRO_EXPIRATION;
		 hmValues["EXPIRATION_WITH_DATA"]=MQRO_EXPIRATION_WITH_DATA;
		 hmValues["EXPIRATION_WITH_FULL_DATA"]=MQRO_EXPIRATION_WITH_FULL_DATA;
		 hmValues["COA"]=MQRO_COA;
		 hmValues["COA_WITH_DATA"]=MQRO_COA_WITH_DATA;
		 hmValues["COA_WITH_FULL_DATA"]=MQRO_COA_WITH_FULL_DATA;
		 hmValues["COD"]=MQRO_COD;
		 hmValues["COD_WITH_DATA"]=MQRO_COD_WITH_DATA;
		 hmValues["COD_WITH_FULL_DATA"]=MQRO_COD_WITH_FULL_DATA;
		 hmValues["PAN"]=MQRO_PAN;
		 hmValues["NAN"]=MQRO_NAN;
		 hmValues["ACTIVITY"]=MQRO_ACTIVITY;
		 hmValues["NEW_MSG_ID"]=MQRO_NEW_MSG_ID;
		 hmValues["PASS_MSG_ID"]=MQRO_PASS_MSG_ID;
		 hmValues["COPY_MSG_ID_TO_CORREL_ID"]=MQRO_COPY_MSG_ID_TO_CORREL_ID;
		 hmValues["PASS_CORREL_ID"]=MQRO_PASS_CORREL_ID;
		 hmValues["DEAD_LETTER_Q"]=MQRO_DEAD_LETTER_Q;
		 hmValues["DISCARD_MSG"]=MQRO_DISCARD_MSG;
		 hmValues["PASS_DISCARD_AND_EXPIRY"]=MQRO_PASS_MSG_ID;
		 hmValues["NONE"]=MQRO_NONE;
	}


	MQLONG parse(const String& strValue){
		IAS_TRACER;
		StringList lstValues;
		TypeTools::Tokenize(strValue,lstValues,',');

		MQLONG iResult = MQRO_NONE;

		for(StringList::const_iterator it=lstValues.begin(); it != lstValues.end(); it++){
			Map::const_iterator vit=hmValues.find((*it));
			if(vit == hmValues.end())
				IAS_THROW(BadUsageException("Bad Value for MQReport options string."));

			iResult|=vit->second;
		}

		return iResult;
	}
};
/*************************************************************************/
static _MQROMapper _mqroMapper;

const String Manageable::CJMSDstAttr("jms.Dst");
const String Manageable::CJMSRtoAttr("Rto");

/*************************************************************************/
Manageable::Manageable(Session* pSession):
		pSession(pSession){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSession)
}
/*************************************************************************/
Manageable::~Manageable() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Manageable::updateID(unsigned char* sId, const String& strValue)const{
	IAS_TRACER;

	if(strncmp(strValue.c_str(),"MQ_",3)==0){
		//TODO const char* version
		MiscTools::HexToBinary(strValue.substr(3),sId,MQ_MSG_ID_LENGTH);
	}else{
		memset(sId,0,MQ_MSG_ID_LENGTH);
		strncpy((char*)sId,strValue.c_str(),MQ_MSG_ID_LENGTH);
	}

}
/*************************************************************************/
void Manageable::updateMDPMO(MQMD& md, MQPMO& pmo, const ::IAS::QS::API::Attributes* pAttributes)const{
	IAS_TRACER;

	String strFormat(pAttributes->getFormat());

	if(strFormat.compare("MQADMIN") == 0){
		memcpy(md.Format,MQFMT_ADMIN,MQ_FORMAT_LENGTH);
	}

	if(pAttributes->isSet(API::Attributes::CA_MID))
		updateID((unsigned char*)&md.MsgId,pAttributes->getMID());

	if(pAttributes->isSet(API::Attributes::CA_CID))
		updateID((unsigned char*)&md.CorrelId,pAttributes->getCID());

	if(pAttributes->isSet("IAS_MQ_GID")){
		updateID((unsigned char*)&md.GroupId,pAttributes->getValue("IAS_MQ_GID"));
        md.MsgFlags = MQMF_MSG_IN_GROUP;
	}

	if(pAttributes->isSet(API::Attributes::CA_Priority))
		md.Priority=pAttributes->getPriority();

	if(pAttributes->isSet(API::Attributes::CA_Expiration))
		md.Expiry=pAttributes->getExpiration();

	if(pAttributes->isSet("IAS_MQ_REPORT")){
		md.Report = _mqroMapper.parse(pAttributes->getValue("IAS_MQ_REPORT"));
	}

	if(pAttributes->isSet(API::Attributes::CA_Persistance)){
		md.Persistence = pAttributes->getPersistance() ? MQPER_PERSISTENT : MQPER_NOT_PERSISTENT;
	}

	pmo.Version = MQPMO_VERSION_3;

	if(pSession->getMode() != Session::SM_NonTransacted)
		pmo.Options |= MQPMO_SYNCPOINT;

}
/*************************************************************************/
}
}
}
