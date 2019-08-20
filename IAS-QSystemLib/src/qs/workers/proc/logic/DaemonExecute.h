/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/DaemonExecute.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_DaemonExecute_H_
#define _IAS_QS_Workers_Proc_Logic_DaemonExecute_H_

#include <commonlib/commonlib.h>


#include <org/invenireaude/qsystem/workers/logic/DaemonExecute.h>
#include <org/invenireaude/qsystem/workers/DaemonControl.h>

#include "Execute.h"

#include <lang/interpreter/TypeList.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
/** The DaemonExecute class.
 *
 */
class DaemonExecute :
		public Execute{
public:

	virtual ~DaemonExecute() throw();

	virtual void compute();
	virtual void receive(bool bNoWait);

protected:
	DaemonExecute(const ::org::invenireaude::qsystem::workers::logic::DaemonExecute* dmParameters,
			  	    WCM::WorkContextManager* pWorkContextManager);

	virtual void computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						   DM::DataObjectPtr& dmData);


  ::org::invenireaude::qsystem::workers::Ext::DaemonControlPtr dmDaemonControl;
  int iNextInterval;
	friend class Factory<DaemonExecute>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_DaemonExecute_H_ */
