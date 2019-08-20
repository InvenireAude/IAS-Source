/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/System.h 
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
#ifndef _IAS_QS_WMQ_System_H_
#define _IAS_QS_WMQ_System_H_

#include <commonlib/commonlib.h>

#include <qs/api.h>
#include <qs/Impl/System.h>

#include "VTable.h"

#include "log/LogLevel.h"


namespace IAS {
namespace QS {
namespace WMQ {

class ContentManager;

/*************************************************************************/
/** The WMQ class.
 *
 */
class System : public Impl::System {
public:

	virtual ~System() throw();

	virtual API::Connection* createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	ContentManager*  	getContentManager();

	inline VTable* getVTable(){ return ptrVTable; };


protected:

	System(VTable* pVTable);

	IAS_DFT_FACTORY< ContentManager >::PtrHolder               ptrContentManager;


	IAS_DFT_FACTORY< VTable >::PtrHolder                       ptrVTable;

	friend class ::IAS::Factory<System>;

};
/*************************************************************************/

}
}
}

#endif /* _IAS_QS_WMQ_System_H_ */
