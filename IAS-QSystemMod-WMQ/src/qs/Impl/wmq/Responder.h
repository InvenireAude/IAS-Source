/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Responder.h 
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
#ifndef _IAS_QS_System_Responder_H_
#define _IAS_QS_System_Responder_H_

#include "Responder.h"

#include <qs/api/Responder.h>
#include <qs/api/Destination.h>

#include <qs/Impl/shm/shared/Queue.h>

#include "Manageable.h"
#include "VTable.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The Responder class.
 *
 */
class Responder : public Manageable,
			   public virtual API::Responder{

public:

	virtual ~Responder() throw();

	virtual bool respond(API::Message* pMessage, const API::Destination& refDestination);

protected:
	Responder(Session* pSession);

	VTable  *pVTable;

	friend class Factory<Responder>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Responder_H_ */
