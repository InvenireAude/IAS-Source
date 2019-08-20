/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Requester.cpp 
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
#include "Requester.h"
#include<qs/log/LogLevel.h>

#include "Session.h"
#include "Connection.h"
#include "Message.h"
#include "VTable.h"

#include <commonlib/commonlib.h>
#include <qs/Impl/shm/System.h>
#include <qs/Impl/shm/shared/Queue.h>
#include <qs/Impl/shm/shared/MsgEntry.h>
#include <qs/Impl/shm/shared/QueueTable.h>

#include "MessageBuffer.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Requester::Requester(Session* pSession,
					const API::Destination& outDestination,
					const API::Destination& inDestination):
		Receiver(pSession),
		Sender(pSession,MQOT_Q,outDestination),
	    outDestination(outDestination),
 	    inDestination(inDestination){

	IAS_TRACER;

	open(inDestination, MQOT_Q, MQOO_INPUT_AS_Q_DEF);
}
/*************************************************************************/
Requester::~Requester() throw(){
	IAS_TRACER;

}
/*************************************************************************/
bool Requester::request(API::Message* pMessage){
	IAS_TRACER;

    if(Sender::ptrObjectHandler.isNull())
    	Sender::openImpl();

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Sending to: "<<Sender::ptrObjectHandler->getName());

	Message* pWMQMessage=dynamic_cast<Message*>(pMessage);

	Sender::ptrMessageHandler=IAS_DFT_FACTORY<Handle::MessageHandle>::Create(Sender::ptrObjectHandler.getPointer());

	MQMD     md  = {MQMD_DEFAULT};
	MQPMO   pmo  = {MQPMO_DEFAULT};

	API::Attributes *pAttributes=pMessage->getAttributes();
	pAttributes->setReplyTo(inDestination.getName());

	pAttributes->setValue(Sender::CJMSRtoAttr,"queue:///"+inDestination.getName());
	pAttributes->setValue(Sender::CJMSDstAttr,"queue:///"+Sender::ptrObjectHandler->getName());

	md.MsgType=MQMT_REQUEST;

	strncpy(md.ReplyToQ,inDestination.getName().c_str(),MQ_Q_NAME_LENGTH);

	MessageBuffer buffer(pWMQMessage);

	if(!buffer.isRFH1()){
		pmo.NewMsgHandle=Sender::ptrMessageHandler->hMsg;
		Sender::ptrMessageHandler->set(pAttributes);
	}else{
		memcpy(md.Format, MQFMT_RF_HEADER_1, MQ_FORMAT_LENGTH);
	}

	Sender::updateMDPMO(md,pmo,pAttributes);

	IAS_LOG(WMQ::LogLevel::INSTANCE.isData(),outDestination.getName());
	IAS_LOG(WMQ::LogLevel::INSTANCE.isData(),"data: ["<<
			String(buffer.getBuffer<const char>(),buffer.getDataLen())<<"]");

	Sender::pVTable->MQPUT(Sender::getSession()->getConnection()->getConnectionHandle()->mqHCONN,
			       Sender::ptrObjectHandler->hObj,&md,&pmo,buffer.getDataLen(),buffer.getBuffer<void>());

	if(!pAttributes->isSet(API::Attributes::CA_MID)){
		String strValue("MQ_");
		MiscTools::BinarytoHex((unsigned char*)md.MsgId,MQ_MSG_ID_LENGTH,strValue);
		pAttributes->setMID(strValue);
	}

	IAS_LOG(WMQ::LogLevel::INSTANCE.isData(),outDestination.getName());

	return true;
}
/*************************************************************************/
API::Message* Requester::receive(int iTimeWait, API::Attributes* pSelector){
	IAS_TRACER;
	return receiveImpl(iTimeWait, pSelector, 0);
}
/*************************************************************************/

}
}
}
