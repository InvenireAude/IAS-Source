/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Responder.cpp 
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
#include "Responder.h"

#include "System.h"
#include "Session.h"
#include "Connection.h"
#include "Message.h"
#include "handler/ObjectHandle.h"
#include "handler/MessageHandle.h"

#include <commonlib/commonlib.h>
#include <qs/Impl/shm/System.h>
#include <qs/Impl/shm/shared/Queue.h>
#include <qs/Impl/shm/shared/MsgEntry.h>
#include <qs/Impl/shm/shared/QueueTable.h>
#include "VTable.h"

#include "MessageBuffer.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Responder::Responder(Session* pSession):
			Manageable(pSession),
			pVTable(getSession()->getConnection()->getSystem()->getVTable()){

	IAS_TRACER;

}
/*************************************************************************/
Responder::~Responder() throw(){
	IAS_TRACER;

}
/*************************************************************************/
bool Responder::respond(API::Message* pMessage, const API::Destination& refDestination){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pMessage);

	IAS_DFT_FACTORY<Handle::ObjectHandle>::PtrHolder  ptrObjectHandler;
	IAS_DFT_FACTORY<Handle::MessageHandle>::PtrHolder ptrMessageHandler;

	MQLONG iOptions=MQOO_OUTPUT | MQOO_FAIL_IF_QUIESCING;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"ReplyTo: "<<refDestination.getName());
	//TODO MQPUT1 - is it possible with message handles ?

	ptrObjectHandler=IAS_DFT_FACTORY<Handle::ObjectHandle>::Create(
			getSession()->getConnection()->getConnectionHandle(),
			refDestination.getName(),
			MQOT_Q,
			MQOO_OUTPUT);

	ptrMessageHandler=IAS_DFT_FACTORY<Handle::MessageHandle>::Create(ptrObjectHandler.getPointer());

	Message* pWMQMessage=dynamic_cast<Message*>(pMessage);

	MQMD     md = {MQMD_DEFAULT};
	MQPMO   pmo  = {MQPMO_DEFAULT};

	API::Attributes *pAttributes=pMessage->getAttributes();

	ptrMessageHandler->set(pAttributes);
	pmo.NewMsgHandle=ptrMessageHandler->hMsg;
	updateMDPMO(md,pmo,pAttributes);
	md.MsgType=MQMT_REPLY;

	MessageBuffer buffer(pWMQMessage);

	IAS_LOG(WMQ::LogLevel::INSTANCE.isData(),refDestination.getName());
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
