/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/SessionAutoCommit.h 
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
#ifndef _IAS_DS_Oracle_SessionAutoCommit_H_
#define _IAS_DS_Oracle_SessionAutoCommit_H_

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

class Connection;

/*************************************************************************/
/** The SessionAutoCommit class.
 *
 */
class SessionAutoCommit :
		public virtual Session{
public:

	virtual ~SessionAutoCommit() throw();

	virtual void commit();
	virtual void rollback();

	virtual TransactionMode getMode()const;

protected:
	SessionAutoCommit(Connection* pConnection);

	friend class Factory<SessionAutoCommit>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DS_Oracle_SessionAutoCommit_H_ */
