/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/tools/Descriptor.h
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
#ifndef _IAS_DS_Oracle_Tools_Descriptor_H_
#define _IAS_DS_Oracle_Tools_Descriptor_H_

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
template<typename _descriptor_type, int _descriptor_id>
class Descriptor {
public:

	typedef _descriptor_type descriptor_type;
	static const int descriptor_id=_descriptor_id;

	Descriptor():pDescriptor(0){}

	Descriptor(const void* parent):pDescriptor(0){
		initialize(parent);
	}

	~Descriptor(){
		free();
	}

	inline void initialize(const void* parent){
		free();
		sword rc=OCIDescriptorAlloc(parent, (dvoid **) &pDescriptor, descriptor_id, (size_t) 0, (dvoid **) 0);
		OracleException::ThrowOnError("AllocateDescriptor",NULL,rc);
	}

	inline void free(){
		if(pDescriptor)
			OCIDescriptorFree(pDescriptor,descriptor_id);
		pDescriptor=0;
	}


	inline operator descriptor_type*(){ return pDescriptor; }
	inline operator const descriptor_type*()const{ return pDescriptor; }

	inline descriptor_type *get(){ return pDescriptor;};
	inline const descriptor_type *get()const { return pDescriptor;};

protected:

	inline bool operator!()const{ return !pDescriptor;}
	//inline descriptor_type** operator &(){ return &pDescriptor; }

	descriptor_type *pDescriptor;
};
/*************************************************************************/
typedef Descriptor<OCILobLocator, OCI_DTYPE_LOB>   DescriptorLOB;
typedef Descriptor<OCIDateTime,   OCI_DTYPE_TIMESTAMP>  DescriptorDate;
typedef Descriptor<OCIDateTime,   OCI_DTYPE_TIMESTAMP>  DescriptorTimeStamp;
typedef Descriptor<OCIDateTime,   OCI_DTYPE_TIMESTAMP_TZ>  DescriptorTimeStampTZ;
typedef Descriptor<OCIDateTime,   OCI_DTYPE_TIMESTAMP_LTZ>  DescriptorTimeStampLTZ;
/*************************************************************************/

}
}
}
}
}
#endif /* _IAS_DS_Oracle_Tools_Descriptor_H_ */
