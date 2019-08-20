/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/BagHandle.h 
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
#ifndef _IAS_QS_WMQ_BagHandle_H_
#define _IAS_QS_WMQ_BagHandle_H_

#include "BagHandle.h"
#include "../VTable.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {
/*************************************************************************/
/** The BagHandle class.
 *
 */
class BagHandle{
 public:

	virtual ~BagHandle() throw();

	MQHBAG mqHBAG;

	inline VTable* getVTable(){
		return pVTable;
	}

protected:

	BagHandle(VTable* pVTable, MQLONG iOptions);

	VTable* pVTable;

	friend class Factory<BagHandle>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_WMQ_BagHandle_H_ */
