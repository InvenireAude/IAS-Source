/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/MessageHandle.h 
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
#ifndef _IAS_QS_WMQ_MessageHandle_H_
#define _IAS_QS_WMQ_MessageHandle_H_

#include "MessageHandle.h"
#include "../VTable.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {

class ObjectHandle;
/*************************************************************************/
/** The MessageHandle class.
 *
 */
class MessageHandle{
 public:

	virtual ~MessageHandle() throw();

    MQHMSG   hMsg;

    void set(const API::Attributes* pAttributes);
    void get(API::Attributes* pAttributes);

protected:

	MessageHandle(ObjectHandle *pObjectHandle);

	ObjectHandle *pObjectHandle;


	friend class Factory<MessageHandle>;

	static const int iBufLen=4096;
	char sName[iBufLen];
	char sValue[iBufLen];
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_WMQ_MessageHandle_H_ */
