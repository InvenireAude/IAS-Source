/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/SessionHandleLocal.h 
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
#ifndef _IAS_DS_Oracle_SessionHandleLocal_H_
#define _IAS_DS_Oracle_SessionHandleLocal_H_


#include <oci.h>

#include "tools/Handle.h"
#include "SessionHandle.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

class Connection;

/*************************************************************************/
/** The SessionHandleLocal class.
 *
 */
class SessionHandleLocal : public virtual SessionHandle {
public:

	virtual ~SessionHandleLocal() throw();

	virtual OCISvcCtx* getSvcCtxHandle();

protected:
	SessionHandleLocal(Connection* pConnection);

	Tools::HandleService  hService;

	friend class Factory<SessionHandleLocal>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Oracle_SessionHandleLocal_H_ */
