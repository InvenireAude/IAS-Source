/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Receiver.cpp 
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
#include "Receiver.h"

#include <commonlib/commonlib.h>

#include "Message.h"
#include "Session.h"
#include "Connection.h"
#include "System.h"

#include "exception/WMQException.h"
#include <qs/api/exception/BackoutHandledException.h>

#include <algorithm>

#include "Tools.h"

#include <string.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Receiver::Receiver(Session* pSession):
	Manageable(pSession),
	pVTable(getSession()->getConnection()->getSystem()->getVTable()),
	myDestination("__FAKE__"),
	iObjectType(MQOT_NONE),
	iExtraOptions(0){
	IAS_TRACER;

	buffer.reserve(32000);

}
/*************************************************************************/
Receiver::~Receiver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Receiver::open(const API::Destination& refDestination,
		            MQLONG iObjectType,
					MQLONG iExtraOptions){
	IAS_TRACER;


	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Ready to open: "<<refDestination.getName());

	this->myDestination=refDestination;
	this->iObjectType=iObjectType;
	this->iExtraOptions=iExtraOptions;

	if(! getSession()->isLazyOpen())
		openImpl();

}
/*************************************************************************/
void Receiver::openImpl(){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Opening: "<<myDestination.getName());

	setup(IAS_DFT_FACTORY<Handle::ObjectHandle>::Create(
			getSession()->getConnection()->getConnectionHandle(),
			myDestination.getName(),
			iObjectType,
			iExtraOptions | MQOO_INQUIRE));

}
/*************************************************************************/
void Receiver::setup(Handle::ObjectHandle* pObjectHandle){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(pObjectHandle);

	ptrObjectHandler = pObjectHandle;

	ptrMessageHandler=IAS_DFT_FACTORY<Handle::MessageHandle>::Create(ptrObjectHandler.getPointer());
	ptrBackoutHandler=IAS_DFT_FACTORY<Handle::BackoutHandler>::Create(ptrObjectHandler,getSession());
}
/*************************************************************************/
API::Message* Receiver::receiveImpl(int iTimeWait, API::Attributes* pSelector, MQLONG iExtraOptions){

	IAS_TRACER;

    IAS_DFT_FACTORY<Message>::PtrHolder ptrMessage;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Receive: "<<myDestination.getName());

    if(ptrObjectHandler.isNull())
    	openImpl();

    bool bGotValidMessage=false;
 	MQLONG iDataLen;

	static   MQMD  defaultMD = { MQMD_DEFAULT };

	MQMD    md;
  	MQMD 	 mdWorking;

    while(!bGotValidMessage){

    	md = defaultMD;
    	md.Version = MQMD_VERSION_2;

    	MQGMO   gmo = {MQGMO_DEFAULT};

    	gmo.Version = MQGMO_VERSION_4;
    	gmo.Options=iExtraOptions | MQGMO_FAIL_IF_QUIESCING | MQGMO_PROPERTIES_IN_HANDLE | MQGMO_WAIT;
    	gmo.WaitInterval=iTimeWait;
    	gmo.MsgHandle=ptrMessageHandler->hMsg;

    	if(pSelector){

    		if(pSelector->isSet(API::Attributes::CA_MID)){
    			IAS_LOG(LogLevel::INSTANCE.isInfo(),"Match MID: "<<pSelector->getMID());
    			updateID((unsigned char*)&md.MsgId,pSelector->getMID());
    			gmo.MatchOptions |= MQMO_MATCH_MSG_ID;
    		}

			if(pSelector->isSet(API::Attributes::CA_CID)) {
				IAS_LOG(LogLevel::INSTANCE.isInfo(),"Match CID: "<<pSelector->getCID());
				updateID((unsigned char*)&md.CorrelId,pSelector->getCID());
				gmo.MatchOptions |= MQMO_MATCH_CORREL_ID;
			}

		}

    	if(getSession()->getMode() != Session::SM_NonTransacted)
    		gmo.Options |= MQGMO_SYNCPOINT;

    	md.CodedCharSetId=getSession()->getTargetCCSID();
    	gmo.Options |= MQGMO_CONVERT;

    	IAS_LOG(LogLevel::INSTANCE.isData(),"MQGET: "<<ptrObjectHandler->getName());


    	mdWorking = md;

    	while(!pVTable->MQGET(getSession()->getConnection()->getConnectionHandle()->mqHCONN,
    			   	   	   ptrObjectHandler->hObj,
    			   	   	   &mdWorking,&gmo,
    			   	   	   buffer.getSize(),
    			   	   	   buffer.getBuffer<void>(),
    			   	   	   &iDataLen)){
    		mdWorking = md;
    		buffer.reserve(iDataLen);
    	}

    	if(mdWorking.BackoutCount <= ptrBackoutHandler->getThreshold()){
    			bGotValidMessage=true;
    	}else{
			IAS_LOG(WMQ::LogLevel::INSTANCE.isInfo(),"Backout threshold exceeded.");
    		if(!isBrowser()){
    			ptrBackoutHandler->backout(mdWorking,(buffer.getBuffer<char>()),iDataLen,ptrMessageHandler);
    			IAS_THROW(QS::API::BackoutHandledException(getSession()->getConnection()->getName()));
    		}else{
    			IAS_LOG(WMQ::LogLevel::INSTANCE.isInfo(),"Skipping backout for the browser.");
    		}

    	}


    }

	IAS_LOG(LogLevel::INSTANCE.isData(),"first 6k: ["<<String(buffer.getBuffer<const char>(),(int)std::min((size_t)iDataLen,(size_t)6000))<<"]");

   	//TODO release buffer if too big !
    ptrMessage=IAS_DFT_FACTORY<Message>::Create(&mdWorking,(buffer.getBuffer<char>()),iDataLen);

    ptrMessageHandler->get(ptrMessage->getAttributes());
	updateAttributesFromMD(mdWorking,ptrMessage->getAttributes());

	return ptrMessage.pass();
}
/*************************************************************************/
void Receiver::updateAttributesFromMD(MQMD& md, API::Attributes* pAttributes){
	IAS_TRACER;

	/*
	 * We assume that if the message was sent by this library,
	 * MID is set correctly;
	 */

	if(!pAttributes->isSet(API::Attributes::CA_MID)){
		String strValue("MQ_");
		MiscTools::BinarytoHex((unsigned char*)md.MsgId,MQ_MSG_ID_LENGTH,strValue);
		pAttributes->setMID(strValue);
	}

	static MQBYTE24 emptyID = { MQMI_NONE_ARRAY };

	if(!pAttributes->isSet(API::Attributes::CA_CID) &&
	    memcmp((const void*)md.CorrelId, (const void*) emptyID, MQ_CORREL_ID_LENGTH) != 0){

		String strValue("MQ_");
		MiscTools::BinarytoHex((unsigned char*)md.CorrelId, MQ_CORREL_ID_LENGTH, strValue);
		pAttributes->setCID(strValue);
	}

	if(!pAttributes->isSet("IAS_MQ_GID") &&
	    memcmp((const void*)md.CorrelId, (const void*) emptyID, MQ_CORREL_ID_LENGTH) != 0){

		String strValue;
		MiscTools::BinarytoHex((unsigned char*)md.CorrelId, MQ_CORREL_ID_LENGTH, strValue);
		pAttributes->setValue("IAS_MQ_GID",strValue);
	}

	if(!pAttributes->isSet(API::Attributes::CA_Expiration)){
		pAttributes->setExpiration(md.Expiry ==  MQEI_UNLIMITED ? API::Attributes::CA_Unlimited_Expiration : md.Expiry);
	}

	if(!pAttributes->isSet(API::Attributes::CA_Persistance)){
		pAttributes->setPersistance(md.Persistence == MQPER_PERSISTENT);
	}

	if(!pAttributes->isSet(API::Attributes::CA_Priority)){
		pAttributes->setPriority(md.Priority);
	}

	if(md.MsgType == MQMT_REQUEST)
		pAttributes->setReplyTo(String("mqm://") +
					Tools::GetMQMDValue(md.ReplyToQMgr,MQ_Q_MGR_NAME_LENGTH) + "/" +
					Tools::GetMQMDValue(md.ReplyToQ,MQ_Q_NAME_LENGTH));
	else
		pAttributes->unset(API::Attributes::CA_ReplyTo);

	if(md.MsgType == MQMT_REPORT){
		pAttributes->setValue("IAS_MQ_REPORT_FB",TypeTools::IntToString(md.Feedback));
	}

	if(!pAttributes->isSet(API::Attributes::CA_Format)){
		pAttributes->setFormat(Tools::GetMQMDValue(md.Format,MQ_FORMAT_LENGTH));
	}

	pAttributes->setValue("IAS_MQ_PDT",Tools::GetMQMDValue(md.PutDate,sizeof(MQCHAR8))+Tools::GetMQMDValue(md.PutTime,sizeof(MQCHAR8)));

}
/*************************************************************************/
bool Receiver::isBrowser()const{
	return false;
}
/*************************************************************************/
}
}
}
