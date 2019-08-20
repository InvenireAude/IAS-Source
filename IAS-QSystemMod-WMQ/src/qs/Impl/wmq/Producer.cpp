/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Producer.cpp 
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
#include "Producer.h"
#include "Session.h"
#include "Connection.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Producer::Producer(Session* pSession, const API::Destination& refDestination):
	Sender(pSession,MQOT_Q,refDestination){
	IAS_TRACER;
}

/*************************************************************************/
Producer::~Producer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
