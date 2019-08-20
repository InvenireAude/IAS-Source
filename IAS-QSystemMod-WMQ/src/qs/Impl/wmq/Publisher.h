/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Publisher.h 
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
#ifndef _IAS_QS_WMQ_Publisher_H_
#define _IAS_QS_WMQ_Publisher_H_

#include <qs/api/Publisher.h>

#include "Sender.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The Publisher class.
 *
 */
class Publisher :
		    public Sender,
			public virtual API::Publisher{
public:

	virtual ~Publisher() throw();

protected:
	Publisher(Session* pSession, const API::Destination& refDestination);

	friend class Factory<Publisher>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_Publisher_H_ */
