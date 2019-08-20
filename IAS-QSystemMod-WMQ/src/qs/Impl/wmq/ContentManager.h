/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/ContentManager.h 
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
#ifndef _IAS_QS_WMQ_ContentManager_H_
#define _IAS_QS_WMQ_ContentManager_H_

#include <qs/api/ContentManager.h>
#include "Content.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The ContentManager class.
 *
 */
class ContentManager : public virtual API::ContentManager {
public:

	virtual ~ContentManager() throw();

	virtual API::Content* allocate();

	Content* allocateImpl();

protected:
	ContentManager();

	friend class Factory<ContentManager>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_ContentManager_H_ */
