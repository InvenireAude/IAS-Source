/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/ObjectHandle.cpp 
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
#include "ObjectHandle.h"

#include <commonlib/commonlib.h>
#include "../exception/WMQException.h"
#include "../Tools.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {
/*************************************************************************/
ObjectHandle::ObjectHandle(ConnectionHandle *pConnectionHandle,
		 	 	 	 	   const String& strName,
		 	 	 	 	   MQLONG iObjectType,
		 	 	 	 	   MQLONG iOptions):
	hObj(MQHO_NONE),
	pConnectionHandle(pConnectionHandle),
	strName(strName){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"["<<strName<<"], type: "<<iObjectType<<" "<<iOptions);
	VTable* pVTable =pConnectionHandle->getVTable();

	MQOD     od = {MQOD_DEFAULT};
	iOptions |= MQOO_FAIL_IF_QUIESCING;

	od.ObjectType = iObjectType;
    od.Version = MQOD_VERSION_4;

    //TODO what was that ?
      //if(iObjectType == MQOT_TOPIC){
    //od.ObjectString.VSPtr=const_cast<char*>(strName.c_str());
    //od.ObjectString.VSLength=strName.length();

    if(strName.compare(0,6,"mqm://") != 0){
    	strncpy(od.ObjectName,strName.c_str(),MQ_Q_NAME_LENGTH);
    }else{
    	URI uriDestination(strName);
    	strncpy(od.ObjectName,uriDestination.getPath().c_str(),MQ_Q_NAME_LENGTH);
    	strncpy(od.ObjectQMgrName,uriDestination.getHost().c_str(),MQ_Q_MGR_NAME_LENGTH);
    }

	try{
		pVTable->MQOPEN(pConnectionHandle->mqHCONN, &od, iOptions, &hObj);
	}catch(WMQException& e){
		IAS_THROW(ItemNotFoundException(strName+e.toString()));
	}

	strResolvedName = Tools::GetMQMDValue(od.ResolvedQName,MQ_Q_NAME_LENGTH);
}
/*************************************************************************/
ObjectHandle::ObjectHandle(ConnectionHandle *pConnectionHandle,
		const String& strName):
		hObj(MQHO_NONE),
		pConnectionHandle(pConnectionHandle),
		strName(strName){
	IAS_TRACER;
}
/*************************************************************************/
ObjectHandle::~ObjectHandle() throw(){
	IAS_TRACER;

	VTable* pVTable =pConnectionHandle->getVTable();

	if(hObj != MQHO_NONE)
	try{
		pVTable->MQCLOSE(pConnectionHandle->mqHCONN,&hObj,MQCO_NONE);
	}catch(Exception& e){
		IAS_LOG(LogLevel::INSTANCE.isError(),e.toString());
	};

}
/*************************************************************************/

}
}
}
}

