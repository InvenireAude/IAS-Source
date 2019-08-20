/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/SubscriptionHandle.cpp 
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
#include "SubscriptionHandle.h"

#include <commonlib/commonlib.h>
#include "../exception/WMQException.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {
/*************************************************************************/
SubscriptionHandle::SubscriptionHandle(ConnectionHandle *pConnectionHandle,
		 	 	 	 	   const String& strName):
	ObjectHandle(pConnectionHandle,strName){
	IAS_TRACER;

	VTable* pVTable =pConnectionHandle->getVTable();

	MQSD     sd        = {MQSD_DEFAULT};
	MQOD     od        = {MQOD_DEFAULT};
	MQLONG   iOptions  = MQOO_FAIL_IF_QUIESCING;

	strncpy(sd.ObjectName,strName.c_str(),MQ_Q_NAME_LENGTH);

	sd.Options =  MQSO_CREATE
	                | MQSO_NON_DURABLE
	                | MQSO_FAIL_IF_QUIESCING
	                | MQSO_MANAGED;

	try{
		pVTable->MQSUB(pConnectionHandle->mqHCONN, &sd, &hObj, &hSub);
	}catch(WMQException& e){
		IAS_THROW(ItemNotFoundException(strName+e.toString()));
	}

}
/*************************************************************************/
SubscriptionHandle::~SubscriptionHandle() throw(){
	IAS_TRACER;

	VTable* pVTable =pConnectionHandle->getVTable();

	if(hSub != MQHO_NONE)
	try{
		pVTable->MQCLOSE(pConnectionHandle->mqHCONN,&hSub,MQCO_NONE);
	}catch(Exception& e){
		IAS_LOG(LogLevel::INSTANCE.isError(),e.toString());
	};
}
/*************************************************************************/

}
}
}
}

