/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/SubscriptionHandle.h 
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
#ifndef _IAS_QS_WMQ_SubscriptionHandle_H_
#define _IAS_QS_WMQ_SubscriptionHandle_H_

#include "../VTable.h"
#include "ConnectionHandle.h"
#include "ObjectHandle.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {

/*************************************************************************/
/** The SubscriptionHandle class.
 *
 */
class SubscriptionHandle : public ObjectHandle {
 public:

	virtual ~SubscriptionHandle() throw();

	MQHOBJ  hSub;

protected:

	SubscriptionHandle(ConnectionHandle *pConnectionHandle,
				 const String& strName);

	friend class Factory<SubscriptionHandle>;
};

}
}
}
}

#endif /* _IAS_QS_WMQ_SubscriptionHandle_H_ */
