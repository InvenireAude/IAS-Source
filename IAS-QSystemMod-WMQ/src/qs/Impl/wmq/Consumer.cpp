/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Consumer.cpp 
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
#include "Consumer.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Consumer::Consumer(Session* pSession,
				   const API::Destination& refDestination):
	Receiver(pSession){
	IAS_TRACER;

	open(refDestination, MQOT_Q, MQOO_INPUT_AS_Q_DEF);
}
/*************************************************************************/
Consumer::~Consumer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Message* Consumer::receive(int iTimeWait, API::Attributes* pSelector){
	IAS_TRACER;
	return receiveImpl(iTimeWait,pSelector,0);
}
/*************************************************************************/
}
}
}
