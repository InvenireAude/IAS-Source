/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/System.h 
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
#ifndef _IAS_DS_Oracle_System_H_
#define _IAS_DS_Oracle_System_H_

#include <commonlib/commonlib.h>

#include <ds/api.h>
#include <ds/Impl/System.h>
#include "tools/Handle.h"

#include "log/LogLevel.h"

#include <oci.h>

#include <org/invenireaude/qsystem/workers/ds/Parameter.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

class ContentManager;

class InputDriver;
class OutputDriver;

/*************************************************************************/
/** The Oracle class.
 *
 */
class System : public Impl::System {
public:

	virtual ~System() throw();

	virtual API::Connection* createConnection(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter);

	inline OCIEnv* getEnvHandle(){ return envhp; }

protected:

	System();

	OCIEnv *envhp;

	Tools::HandleError hError;

	friend class Factory<System>;
};
/*************************************************************************/

}
}
}
}

#endif /* _IAS_DS_Oracle_System_H_ */
