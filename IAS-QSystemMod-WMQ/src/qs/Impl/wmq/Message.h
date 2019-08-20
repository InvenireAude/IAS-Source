/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Message.h 
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
#ifndef _IAS_QS_WMQ_Message_H_
#define _IAS_QS_WMQ_Message_H_

#include <qs/api/Message.h>
#include <qs/api/Content.h>

#include "Content.h"
#include <qs/Impl/base/Attributes.h>

#include <cmqc.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The Message class.
 *
 */
class Message : public virtual API::Message {
public:

	virtual ~Message() throw();

	virtual API::Content*    getContent();
	virtual API::Attributes* getAttributes();

protected:
	Message();
	Message(PMQMD pMQMD, const char* sData, size_t iDataLen);
	Message(const String& strText);

	IAS_DFT_FACTORY<Content>::PtrHolder ptrContent;
	IAS_DFT_FACTORY<QS::Base::Attributes>::PtrHolder ptrAttributes;

	friend class Factory<Message>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_Message_H_ */
