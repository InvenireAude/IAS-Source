/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/txm/Impl/wmq/Connection.h 
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
#ifndef _IAS_TXM_WMQ_Connection_H_
#define _IAS_TXM_WMQ_Connection_H_

#include <commonlib/commonlib.h>
#include <txm/api/Connection.h>

#include <qs/Impl/wmq/VTable.h>
#include <qs/Impl/wmq/handler/ConnectionHandle.h>
#include <qs/Impl/wmq/log/LogLevel.h>

namespace IAS {
namespace TXM {
namespace WMQ {

class System;

/*************************************************************************/
/** The Connection class.
 *
 */
class Connection : public virtual API::Connection {
public:

	virtual ~Connection() throw();

	virtual API::Session* createSession();

	WMQ::System *getSystem();

	QS::WMQ::Handle::ConnectionHandle* getConnectionHandle(){
		return ptrConnectionHandler;
	}

protected:
	Connection(WMQ::System* pSystem, const URI& uri);

	String strName;
	WMQ::System *pSystem;

	IAS_DFT_FACTORY<QS::WMQ::Handle::ConnectionHandle>::PtrHolder ptrConnectionHandler;

	friend class Factory<Connection>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_TXM_WMQ_Connection_H_ */
