/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/BackoutHandler.h 
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
#ifndef _IAS_QS_WMQ_BackoutHandler_H_
#define _IAS_QS_WMQ_BackoutHandler_H_

#include "BackoutHandler.h"
#include "../VTable.h"

namespace IAS {
namespace QS {
namespace WMQ {
class Session;

namespace Handle {
class ObjectHandle;
class MessageHandle;

/*************************************************************************/
/** The BackoutHandler class.
 *
 */
class BackoutHandler{
 public:

	virtual ~BackoutHandler() throw();

	void backout(MQMD& md, PMQVOID pData, MQLONG iDataLen, MessageHandle* pMessageHandle);

	inline MQLONG getThreshold()const{
		return iThreshold;
	};

protected:

	BackoutHandler(ObjectHandle *pObjectHandle, Session* pSession);

	ObjectHandle *pObjectHandle;

	MQLONG iThreshold;

	String strBQName;
	String strDLQName;

	bool sendToBQ(MQMD& md, PMQVOID pData, MQLONG iDataLen, MessageHandle* pMessageHandle);
	bool sendToDLQ(MQMD& md, PMQVOID pData, MQLONG iDataLen, MessageHandle* pMessageHandle);

	void setupBQName();
	void setupDLQName();

	Session* pSession;

	friend class Factory<BackoutHandler>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_WMQ_BackoutHandler_H_ */
