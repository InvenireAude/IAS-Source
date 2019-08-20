/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Content.h 
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
#ifndef _IAS_QS_WMQ_Content_H_
#define _IAS_QS_WMQ_Content_H_

#include <qs/api/Content.h>
#include <commonlib/memory/buffer/StreamMemoryBuffer.h>

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The Content class.
 *
 */
class Content : public virtual API::Content{
public:

	virtual ~Content() throw();

protected:
	Content();

	IAS_DFT_FACTORY<StreamMemoryBuffer>::PtrHolder ptrSMB;
	void *pData;
	friend class Factory<Content>;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_Content_H_ */
