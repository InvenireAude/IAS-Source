/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Browser.cpp 
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
#include "Browser.h"

#include <commonlib/commonlib.h>

#include "Session.h"
#include "System.h"
#include "Connection.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Browser::Browser(Session* pSession, const API::Destination& refDestination):
	Receiver(pSession),
	bFirst(true){
	IAS_TRACER;
	open(refDestination, MQOT_Q, MQOO_BROWSE);
}
/*************************************************************************/
Browser::~Browser() throw(){
	IAS_TRACER;
}
/*************************************************************************/
unsigned int Browser::skip(unsigned int iOffset){
	IAS_TRACER;

	API::Message *pResult;

	size_t iBufferSize=buffer.getSize();
	buffer.resize(64);

	unsigned int iResult=0;
	try{

		while(iOffset--){
			receiveImpl(0, NULL,
					bFirst ? MQGMO_BROWSE_FIRST | MQGMO_ACCEPT_TRUNCATED_MSG
						   : MQGMO_BROWSE_NEXT  | MQGMO_ACCEPT_TRUNCATED_MSG);
			bFirst=false;
			iResult++;
		}

	}catch(EndOfDataException& e){}

	buffer.resize(iBufferSize);

	bFirst=false;

	return iResult;
}
/*************************************************************************/
API::Message* Browser::receive(int iTimeWait, API::Attributes* pSelector){
	IAS_TRACER;

	API::Message *pResult = receiveImpl(iTimeWait,
						pSelector,
						bFirst ? MQGMO_BROWSE_FIRST : MQGMO_BROWSE_NEXT);

	bFirst=false;

	return pResult;
}
/*************************************************************************/
bool Browser::isBrowser()const{
	return true;
}
/*************************************************************************/
}
}
}
