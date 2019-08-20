/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/RFH1Utils.h 
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
#ifndef _IAS_QS_WMQ_RFH1Utils_H_
#define _IAS_QS_WMQ_RFH1Utils_H_

#include "RFH1Utils.h"
#include "../VTable.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {

class ObjectHandle;
/*************************************************************************/
/** The RFH1Utils class.
 *
 */
class RFH1Utils{
 public:

	static void Read(const char* sData, size_t iDataLen, API::Attributes* pAttributes, size_t& iOffset);
	static void Write(Buffer* pBuffer,const API::Attributes* pAttributes, size_t& iDataLen);
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_WMQ_RFH1Utils_H_ */
