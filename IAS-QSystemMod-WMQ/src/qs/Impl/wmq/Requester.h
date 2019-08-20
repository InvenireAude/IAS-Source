/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Requester.h 
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
#ifndef _IAS_QS_System_Requester_H_
#define _IAS_QS_System_Requester_H_

#include "Requester.h"

#include <qs/api/Requester.h>
#include <qs/api/Destination.h>

#include <qs/Impl/shm/shared/Queue.h>

#include "Receiver.h"
#include "Sender.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The Requester class.
 *
 */
class Requester : public Receiver,
				  public Sender,
			      public virtual API::Requester{

public:

	virtual ~Requester() throw();

	virtual API::Message* receive(int iTimeWait, API::Attributes* pSelector);
	virtual bool request(API::Message* pMessage);

protected:
	Requester(Session* pSession,
			const API::Destination& outDestination,
			const API::Destination& inDestination);

	API::Destination outDestination;
	API::Destination inDestination;

	friend class Factory<Requester>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Requester_H_ */
