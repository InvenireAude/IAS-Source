/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/tools/Handle.h 
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
#ifndef _IAS_DS_Oracle_Tools_Handle_H_
#define _IAS_DS_Oracle_Tools_Handle_H_

#include <commonlib/commonlib.h>
#include <ds/api/Connection.h>

#include "../exception/OracleException.h"

#include <oci.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Tools {
class System;

/*************************************************************************/
/** The Connection class.
 *
 */
template<typename _handle_type, int _handle_id>
class Handle {
public:

	typedef _handle_type handle_type;
	static const int handle_id=_handle_id;

	Handle():pHandle(0){}

	Handle(const void* parent):pHandle(0){
		initialize(parent);
	}

	~Handle(){
		free();
	}

	inline void initialize(const void* parent){
		free();
		sword rc=OCIHandleAlloc(parent, (dvoid **) &pHandle, handle_id, (size_t) 0, (dvoid **) 0);
		OracleException::ThrowOnError("AllocateHandle",NULL,rc);
	}

	inline void free(){
		if(pHandle)
			OCIHandleFree(pHandle,handle_id);
		pHandle=0;
	}


	inline operator handle_type*(){ return pHandle; }
	inline operator const handle_type*()const{ return pHandle; }

	inline handle_type *get(){ return pHandle;};
	inline const handle_type *get()const { return pHandle;};

protected:

	inline bool operator!()const{ return !pHandle;}
	//inline handle_type** operator &(){ return &pHandle; }

	handle_type *pHandle;
};
/*************************************************************************/
//typedef Handle<OCIEnv,OCI_HTYPE_ENV>     HandleEnv;
typedef Handle<OCIError,  OCI_HTYPE_ERROR>  HandleError;
typedef Handle<OCISvcCtx, OCI_HTYPE_SVCCTX> HandleService;
typedef Handle<OCIStmt,   OCI_HTYPE_STMT>   HandleStatement;
/*************************************************************************/

}
}
}
}
}
#endif /* _IAS_DS_Oracle_Tools_Handle_H_ */
