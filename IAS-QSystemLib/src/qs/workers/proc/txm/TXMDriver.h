/*
 * File: IAS-QSystemLib/src/qs/workers/proc/txm/TXMDriver.h
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _IAS_QS_Workers_Proc_TXM_TXMDriver_H_
#define _IAS_QS_Workers_Proc_TXM_TXMDriver_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/txm/Parameter.h>

#include <txm/api.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM{
class WorkContextManager;
}
namespace TXM {

/*************************************************************************/
/** The TXMDriver class.
 *
 */
class TXMDriver {
public:

	virtual ~TXMDriver() throw();

	::IAS::TXM::API::Session* getSession();

protected:
	TXMDriver(const ::org::invenireaude::qsystem::workers::txm::Parameter* dmParameter,
			  WCM::WorkContextManager* pWorkContextManager);

	WCM::WorkContextManager* pWorkContextManager;

	::org::invenireaude::qsystem::workers::txm::Ext::ParameterPtr dmParameter;

	URI uriConnectionKey;
	friend class Factory<TXMDriver>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_TXM_TXMDriver_H_ */
