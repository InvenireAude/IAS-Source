/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Sender.h 
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
#ifndef _IAS_QS_WMQ_Sender_H_
#define _IAS_QS_WMQ_Sender_H_

#include "Sender.h"

#include <qs/api/Sender.h>
#include <qs/api/Destination.h>

#include <qs/Impl/shm/shared/Queue.h>

#include "Manageable.h"
#include "VTable.h"

#include "handler/MessageHandle.h"
#include "handler/ObjectHandle.h"

namespace IAS {
namespace QS {
namespace WMQ {

class OutputDriver;
/*************************************************************************/
/** The Sender class.
 *
 */
class Sender : public Manageable,
			   public virtual API::Sender{

public:

	virtual ~Sender() throw();

	virtual bool send(API::Message* pMessage);

protected:
	Sender(Session* pSession,
			 MQLONG iObjectType,
			 const API::Destination& refDestination);

	API::Destination myDestination;
	MQLONG iObjectType;

	IAS_DFT_FACTORY<Handle::ObjectHandle>::PtrHolder ptrObjectHandler;
	IAS_DFT_FACTORY<Handle::MessageHandle>::PtrHolder ptrMessageHandler;

	VTable  *pVTable;

	void openImpl();

	friend class Factory<Sender>;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_Sender_H_ */
