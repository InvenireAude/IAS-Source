/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Administrator.h 
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
#ifndef _IAS_QS_WMQ_Administrator_H_
#define _IAS_QS_WMQ_Administrator_H_

#include <commonlib/commonlib.h>
#include <qs/api/Administrator.h>
#include <qs/Impl/shm/System.h>

#include "handler/ConnectionHandle.h"


namespace IAS {
namespace QS {
namespace WMQ {

class Connection;

/*************************************************************************/
/** The Administrator class.
 *
 */
class Administrator : public virtual API::Administrator {
public:

	virtual ~Administrator() throw();

	virtual ::org::invenireaude::qsystem::stats::Ext::SystemStatsPtr getStats(bool bReset);

protected:
	Administrator(Connection* pConnection);

	Connection* pConnection;

	friend class Factory<Administrator>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Administrator_H_ */
