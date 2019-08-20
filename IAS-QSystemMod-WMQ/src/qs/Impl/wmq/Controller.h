/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Controller.h 
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
#ifndef _IAS_QS_System_Controller_H_
#define _IAS_QS_System_Controller_H_

#include "Controller.h"

#include <qs/api/Controller.h>
#include <qs/api/Destination.h>

#include <qs/Impl/shm/shared/Queue.h>

#include "Manageable.h"
#include "handler/ObjectHandle.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The Controller class.
 *
 */
class Controller : public Manageable,
			       public virtual API::Controller{

public:

	virtual ~Controller() throw();

	virtual unsigned int getNumMessages();

protected:
	Controller(Session* pSession, const API::Destination& refDestination);

	VTable  *pVTable;

	IAS_DFT_FACTORY<Handle::ObjectHandle>::PtrHolder ptrObjectHandler;

	API::Destination myDestination;

	friend class Factory<Controller>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Controller_H_ */
