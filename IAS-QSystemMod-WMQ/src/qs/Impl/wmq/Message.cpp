/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Message.cpp 
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
#include "Message.h"
#include "ContentManager.h"
#include <qs/Impl/base/Attributes.h>

#include "handler/RFH1Utils.h"

#include <commonlib/commonlib.h>

#include <qs/Impl/wmq/log/LogLevel.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Message::Message(){
	IAS_TRACER;
	ptrContent=IAS_DFT_FACTORY<Content>::Create();
	ptrAttributes=IAS_DFT_FACTORY<QS::Base::Attributes>::Create();
}

/*************************************************************************/
Message::Message(PMQMD pMQMD, const char* sData, size_t iDataLen){
	IAS_TRACER;

	ptrContent=IAS_DFT_FACTORY<Content>::Create();
	ptrAttributes=IAS_DFT_FACTORY<QS::Base::Attributes>::Create();

	if(memcmp(pMQMD->Format,MQFMT_RF_HEADER_1, MQ_FORMAT_LENGTH) == 0){

		IAS_LOG(LogLevel::INSTANCE.isInfo(), "RFH V1 detected !");

		size_t iOffset = 0;
		Handle::RFH1Utils::Read(sData,iDataLen,ptrAttributes,iOffset);
		(*ptrContent).write(sData+iOffset,iDataLen-iOffset);

	}else{
		(*ptrContent).write(sData,iDataLen);
	}

	ptrContent->flush();
}
/*************************************************************************/
Message::Message(const String& strText){
	IAS_TRACER;
	(*ptrContent)<<strText;
}
/*************************************************************************/
Message::~Message() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Content* Message::getContent(){
	IAS_TRACER;
	return ptrContent;
}
/*************************************************************************/
API::Attributes* Message::getAttributes(){
	IAS_TRACER;
	return ptrAttributes;
}
/*************************************************************************/

}
}
}
