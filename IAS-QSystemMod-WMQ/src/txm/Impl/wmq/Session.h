/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/txm/Impl/wmq/Session.h 
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
#ifndef _IAS_TXM_WMQ_Session_H_
#define _IAS_TXM_WMQ_Session_H_

#include <txm/api/Session.h>

namespace IAS {
namespace TXM {
namespace WMQ {

class Connection;

/*************************************************************************/
/** The Session class.
 *
 */
class Session : public virtual API::Session {
public:

	virtual ~Session() throw();

	virtual void begin();
	virtual void commit();
	virtual void rollback();

	Connection* getConnection()const;

protected:
	Session(Connection* pConnection);

	Connection* pConnection;
	friend class Factory<Session>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_TXM_WMQ_Session_H_ */
