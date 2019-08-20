/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/ObjectHandle.h 
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
#ifndef _IAS_QS_WMQ_ObjectHandle_H_
#define _IAS_QS_WMQ_ObjectHandle_H_

#include "../VTable.h"
#include "ConnectionHandle.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {

/*************************************************************************/
/** The ObjectHandle class.
 *
 */
class ObjectHandle{
 public:

	virtual ~ObjectHandle() throw();

	MQHOBJ  hObj;

	inline VTable* getVTable(){
		return pConnectionHandle->getVTable();
	}

	inline ConnectionHandle* getConnectionHandle(){
		return pConnectionHandle;
	}

	inline const String& getName()const{
		return strName;
	}

	inline const String& getResolvedName()const{
		return strResolvedName;
	}

protected:

	ObjectHandle(ConnectionHandle *pConnectionHandle,
				 const String& strName,
				 MQLONG iObjectType,
				 MQLONG iOptions);


	ObjectHandle(ConnectionHandle *pConnectionHandle, const String& strName);

	ConnectionHandle *pConnectionHandle;
	String strName;
	String strResolvedName;
	friend class Factory<ObjectHandle>;
};

}
}
}
}

#endif /* _IAS_QS_WMQ_ObjectHandle_H_ */
