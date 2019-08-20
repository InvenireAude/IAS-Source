/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/exception/WMQException.cpp 
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
#include "WMQException.h"

namespace IAS{
namespace QS {
namespace WMQ {

bool WMQException::bStopOnConnectionLost = IAS::EnvTools::GetBooleanEnv("IAS_WMQ_STOP_ON_CONNECTION_LOST");

/*************************************************************************/
WMQException::WMQException():
	iReason(MQRC_NONE){
	IAS_TRACER;		
}
/*************************************************************************/
WMQException::WMQException(const String& strInfo, int iReason):iReason(iReason){
	IAS_TRACER;

	(*this)<<strInfo<<", reason="<<iReason;

	if(iReason == MQRC_CONNECTION_BROKEN && bStopOnConnectionLost)
		SYS::Signal::SignalHandler(15);
}
/*************************************************************************/
WMQException::~WMQException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* WMQException::getName(){
	IAS_TRACER;
	return "WMQException";
}

/*************************************************************************/
}
}
} /* namespace IAS */
