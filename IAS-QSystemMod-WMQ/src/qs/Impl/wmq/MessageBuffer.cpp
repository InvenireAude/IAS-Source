/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/MessageBuffer.cpp 
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
#include "MessageBuffer.h"

#include "Message.h"
#include "log/LogLevel.h"

#include "handler/RFH1Utils.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
MessageBuffer::MessageBuffer(Message* pWMQMessage):
		iDataLen(0),
		bIsRFH1(false){
	IAS_TRACER;

	std::istream& is(*(pWMQMessage->getContent()));

	if(!is.good()){
		resize(1);
		return;
	}

	bIsRFH1 = pWMQMessage->getAttributes()->isSet("IAS_MQ_RFH1");

	if(bIsRFH1)
		Handle::RFH1Utils::Write(this, pWMQMessage->getAttributes(),iDataLen);

	size_t iChunkSize=64000;

	while(is.good()){
		resize(iDataLen+iChunkSize);
		is.read(getBuffer<char>()+iDataLen, iChunkSize);
		iDataLen+=is.gcount();
		iChunkSize*=2;
	}

}
/*************************************************************************/
MessageBuffer::~MessageBuffer(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
