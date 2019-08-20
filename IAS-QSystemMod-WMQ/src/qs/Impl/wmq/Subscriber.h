/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Subscriber.h 
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
#ifndef _IAS_QS_WMQ_Subscriber_H_
#define _IAS_QS_WMQ_Subscriber_H_

#include "Receiver.h"

#include <qs/api/Subscriber.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The Subscriber class.
 *
 */
class Subscriber :
		public Receiver,
		public virtual API::Subscriber{
public:

	virtual ~Subscriber() throw();

	virtual API::Message* receive(int iTimeWait, API::Attributes* pSelector);

protected:
	Subscriber(Session* pSession, const API::Destination& refDestination);

	virtual void openImpl();

	friend class Factory<Subscriber>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_Subscriber_H_ */
