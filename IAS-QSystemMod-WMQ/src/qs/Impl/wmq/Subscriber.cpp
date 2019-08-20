/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Subscriber.cpp 
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
#include "Subscriber.h"

#include "Session.h"
#include "Connection.h"

#include <commonlib/commonlib.h>

#include "handler/SubscriptionHandle.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Subscriber::Subscriber(Session* pSession, const API::Destination& refDestination):
	Receiver(pSession){
	IAS_TRACER;

	open(refDestination,MQOT_TOPIC,0);
}
/*************************************************************************/
Subscriber::~Subscriber() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Subscriber::openImpl(){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Opening subscription: "<<myDestination.getName());

	setup(IAS_DFT_FACTORY<Handle::SubscriptionHandle>::Create(
			getSession()->getConnection()->getConnectionHandle(),
			myDestination.getName()));
}
/*************************************************************************/
API::Message* Subscriber::receive(int iTimeWait, API::Attributes* pSelector){
	IAS_TRACER;
	return receiveImpl(iTimeWait, pSelector, 0);
}
/*************************************************************************/
}
}
}
