/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/SessionHandle.h 
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
#ifndef _IAS_DS_Oracle_SessionHandle_H_
#define _IAS_DS_Oracle_SessionHandle_H_

#include <oci.h>
#include "tools/Handle.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

class Connection;

/*************************************************************************/
/** The SessionHandle class.
 *
 */
class SessionHandle {

public:

	virtual ~SessionHandle() throw();


	virtual OCISvcCtx* getSvcCtxHandle()=0;

	inline OCIEnv*    getEnvHandle(){ return pOCIEnv; };
	inline OCIError*  getErrorHandle() { return hError; };

protected:
	SessionHandle(OCIEnv* pOCIEnv);

	Tools::HandleError    hError;
	OCIEnv*               pOCIEnv;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Oracle_SessionHandle_H_ */
