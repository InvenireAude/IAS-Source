/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/Session.h
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
#ifndef _IAS_DS_Oracle_Session_H_
#define _IAS_DS_Oracle_Session_H_

#include <ds/api/Session.h>
#include <qs/fmt/Formatter.h>
#include <ds/Impl/Session.h>
#include <oci.h>
#include "tools/Handle.h"
#include <ds/api.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

class Connection;
class SessionHandle;

/*************************************************************************/
/** The Session class.
 *API
 */
class Session :
 public Impl::Session{

public:

	virtual ~Session() throw();

	virtual API::StatementInsert*   createInsert();
	virtual API::StatementCall*     createCall();
  virtual API::StatementFunCall*  createFunCall();
	virtual API::StatementSelect*   createSelect();
	virtual API::StatementDelete*   createDelete();
	virtual API::StatementUpdate*   createUpdate();

	Connection* getConnection()const;

	OCIEnv*      getEnvHandle();
	OCIError*    getErrorHandle();
	OCISvcCtx*   getSvcCtxHandle();

protected:
	Session(Connection* pConnection);

	Connection* pConnection;

	IAS_DFT_FACTORY<SessionHandle>::PtrHolder ptrSessionHandle;

	friend class Factory<Session>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Oracle_Session_H_ */
