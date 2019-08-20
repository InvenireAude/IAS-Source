/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Browser.h 
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
#ifndef _IAS_QS_WMQ_Browser_H_
#define _IAS_QS_WMQ_Browser_H_

#include <qs/api/Browser.h>
#include "Receiver.h"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
/** The Browser class.
 *
 */
class Browser :
		public Receiver,
		public virtual API::Browser {
public:

	virtual ~Browser() throw();


	virtual API::Message* receive(int iTimeWait, API::Attributes* pSelector);

	virtual unsigned int skip(unsigned int iOffset);

protected:
	Browser(Session* pSession, const API::Destination& refDestination);

	bool bFirst;
    virtual bool isBrowser()const;

	friend class Factory<Browser>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_Browser_H_ */
