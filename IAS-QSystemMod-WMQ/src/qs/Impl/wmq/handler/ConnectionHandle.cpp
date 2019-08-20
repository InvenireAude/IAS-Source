/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/ConnectionHandle.cpp 
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
#include "ConnectionHandle.h"

#include <commonlib/commonlib.h>
#include "../exception/WMQException.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {
/*************************************************************************/
ConnectionHandle::ConnectionHandle(VTable* pVTable, const String& strName):
	mqHCONN(MQHC_DEF_HCONN),
	pVTable(pVTable){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pVTable);
	IAS_LOG(LogLevel::INSTANCE.isInfo(),strName);
	MQCHAR sConnection[MQ_CONN_NAME_LENGTH];
	strncpy(sConnection,strName.c_str(),MQ_CONN_NAME_LENGTH);

	pVTable->MQCONN(sConnection,&mqHCONN);


}
/*************************************************************************/
ConnectionHandle::~ConnectionHandle() throw(){
	IAS_TRACER;

	if(mqHCONN != MQHC_DEF_HCONN){

		try{
			pVTable->MQDISC(&mqHCONN);
		}catch(Exception& e){
			IAS_LOG(LogLevel::INSTANCE.isError(),e.toString());
		};

	}
}
/*************************************************************************/

}
}
}
}
