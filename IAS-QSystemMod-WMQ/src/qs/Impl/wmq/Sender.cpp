/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Sender.cpp 
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
#include "Sender.h"

#include "Session.h"
#include "Connection.h"
#include "Message.h"
#include "System.h"

#include "exception/WMQException.h"
#include <algorithm>

#include "MessageBuffer.h"

namespace IAS {
namespace QS {
namespace WMQ {



/*************************************************************************/
Sender::Sender(Session* pSession,
				MQLONG iObjectType,
				const API::Destination& refDestination):
	Manageable(pSession),
	pVTable(getSession()->getConnection()->getSystem()->getVTable()),
	myDestination(refDestination),
	iObjectType(iObjectType){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Opening: "<<refDestination.getName());

	if(! getSession()->isLazyOpen())
		openImpl();
}
/*************************************************************************/
Sender::~Sender() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Sender::openImpl(){
	IAS_TRACER;
	MQOD     od = {MQOD_DEFAULT};

	MQLONG iOptions=MQOO_OUTPUT | MQOO_FAIL_IF_QUIESCING;

	strncpy(od.ObjectName,myDestination.getName().c_str(),MQ_Q_NAME_LENGTH);

	ptrObjectHandler=IAS_DFT_FACTORY<Handle::ObjectHandle>::Create(
			getSession()->getConnection()->getConnectionHandle(),
			myDestination.getName(),
			iObjectType,
			MQOO_OUTPUT);
}
/*************************************************************************/
bool Sender::send(API::Message* pMessage){
	IAS_TRACER;

	if(ptrObjectHandler.isNull())
		openImpl();

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Sending to: "<<ptrObjectHandler->getName());

	ptrMessageHandler=IAS_DFT_FACTORY<Handle::MessageHandle>::Create(ptrObjectHandler.getPointer());

	IAS_CHECK_IF_NULL(pMessage);

	Message* pWMQMessage=dynamic_cast<Message*>(pMessage);

	MQMD     md = {MQMD_DEFAULT};
	MQPMO   pmo  = {MQPMO_DEFAULT};

	API::Attributes *pAttributes=pMessage->getAttributes();

	/* Copy requests */
	if(pAttributes->isSet(API::Attributes::CA_ReplyTo)){

		URI uriReplyTo(pAttributes->getReplyTo());

		if(uriReplyTo.getProtocol().compare("mqm") == 0 ||
		   uriReplyTo.getProtocol().compare("mqic") == 0){

			md.MsgType=MQMT_REQUEST;
			strncpy(md.ReplyToQMgr, uriReplyTo.getHost().c_str(), MQ_Q_MGR_NAME_LENGTH);
			strncpy(md.ReplyToQ, uriReplyTo.getPath().c_str(), MQ_Q_NAME_LENGTH);

			pAttributes->unset(API::Attributes::CA_ReplyTo);

			pAttributes->setValue(CJMSRtoAttr,"queue://"+uriReplyTo.getHost()+"/"+uriReplyTo.getPath());
		}

	}else{
		md.MsgType=MQMT_DATAGRAM;
	}

	pAttributes->setValue(CJMSDstAttr,"queue:///"+ptrObjectHandler->getName());

	MessageBuffer buffer(pWMQMessage);

	if(!buffer.isRFH1()){
		pmo.NewMsgHandle=Sender::ptrMessageHandler->hMsg;
		Sender::ptrMessageHandler->set(pAttributes);
	}else{
		memcpy(md.Format, MQFMT_RF_HEADER, MQ_FORMAT_LENGTH);
	}

	updateMDPMO(md,pmo,pAttributes);


	IAS_LOG(WMQ::LogLevel::INSTANCE.isData(),myDestination.getName());
	IAS_LOG(WMQ::LogLevel::INSTANCE.isData(),"data: ["<<
			String(buffer.getBuffer<const char>(),buffer.getDataLen())<<"]");

	pVTable->MQPUT(getSession()->getConnection()->getConnectionHandle()->mqHCONN,
			       ptrObjectHandler->hObj,&md,&pmo,buffer.getDataLen(),buffer.getBuffer<void>());


	return true;
}
/*************************************************************************/

}
}
}
