/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Receiver.h 
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
#ifndef _IAS_QS_WMQ_Receiver_H_
#define _IAS_QS_WMQ_Receiver_H_

#include "Receiver.h"

#include <qs/api/Receiver.h>
#include <qs/api/Destination.h>

#include "Manageable.h"

#include "handler/MessageHandle.h"
#include "handler/ObjectHandle.h"
#include "handler/BackoutHandler.h"


#include "VTable.h"


namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The Receiver class.
 *
 */
class Receiver : public Manageable,
 	 	 	 	 public virtual API::Receiver{

 public:

	virtual ~Receiver() throw();

protected:
	Receiver(Session* pSession);

	void open(const API::Destination& refDestination,
			  MQLONG iObjectType,
			  MQLONG iExtraOptions);

	API::Message* receiveImpl(int iTimeWait, API::Attributes* pSelector, MQLONG iExtraOptions);

	virtual void openImpl();

	void updateAttributesFromMD(MQMD& mqmd, API::Attributes* pAttributes);

	API::Destination myDestination;

	/*************************************************************************/

    Buffer buffer;

    virtual bool isBrowser()const;
	void setup(Handle::ObjectHandle* pObjectHandle);

	friend class Factory<Receiver>;

private:
	IAS_DFT_FACTORY<Handle::ObjectHandle>::PtrHolder ptrObjectHandler;
	IAS_DFT_FACTORY<Handle::MessageHandle>::PtrHolder ptrMessageHandler;
	IAS_DFT_FACTORY<Handle::BackoutHandler>::PtrHolder ptrBackoutHandler;

	VTable  *pVTable;

	MQLONG iObjectType;
	MQLONG iExtraOptions;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_Receiver_H_ */
