/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/txm/Impl/wmq/System.h 
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
#ifndef _IAS_TXM_WMQ_System_H_
#define _IAS_TXM_WMQ_System_H_

#include <commonlib/commonlib.h>

#include <txm/Impl/System.h>

#include <qs/Impl/wmq/VTable.h>
#include <qs/Impl/wmq/handler/ConnectionHandle.h>
#include <qs/Impl/wmq/log/LogLevel.h>


namespace IAS {
namespace TXM {
namespace WMQ {

class ContentManager;

/*************************************************************************/
/** The WMQ class.
 *
 */
class System : public Impl::System {
public:

	virtual ~System() throw();

	virtual API::Connection* createConnection(const URI& uri);

	inline QS::WMQ::VTable* getVTable(){ return ptrVTable; };


protected:

	System(QS::WMQ::VTable* pVTable, const URI& uri);
	URI uri;

	IAS_DFT_FACTORY< QS::WMQ::VTable >::PtrHolder              ptrVTable;

	friend class ::IAS::Factory<System>;

};
/*************************************************************************/

}
}
}

#endif /* _IAS_TXM_WMQ_System_H_ */
