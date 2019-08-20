/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Connection.h 
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
#ifndef _IAS_QS_WMQ_Connection_H_
#define _IAS_QS_WMQ_Connection_H_

#include <commonlib/commonlib.h>
#include <qs/api/Connection.h>

#include "VTable.h"

#include "handler/ConnectionHandle.h"

namespace IAS {
namespace QS {
namespace WMQ {

class System;

/*************************************************************************/
/** The Connection class.
 *
 */
class Connection : public virtual API::Connection {
public:

	virtual ~Connection() throw();

	virtual API::Session* createSession(API::Session::TransactionMode iMode);
	virtual API::Administrator*   createAdministrator();

	virtual API::Message*         createMessage();
	virtual API::ContentManager*  getContentManager();

	WMQ::System *getSystem();

	Handle::ConnectionHandle* getConnectionHandle(){
		return ptrConnectionHandler;
	}

	const String& getName()const{ return strName; };
	const String& getQMgrName()const{ return strQMgrName; };

protected:
	Connection(WMQ::System* pSystem, const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	String strName;
	String strQMgrName;

	WMQ::System *pSystem;

	::org::invenireaude::qsystem::workers::Ext::ConnectionPtr dmConnection;

	IAS_DFT_FACTORY<Handle::ConnectionHandle>::PtrHolder ptrConnectionHandler;

	int iNumTransacted;
	friend class Factory<Connection>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_Connection_H_ */
