/*
 * File: IAS-QSystemLib/src/qs/net/StateMachineWorkManager.h
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
#ifndef _IAS_QS_Net_StateMachineWorkManager_H_
#define _IAS_QS_Net_StateMachineWorkManager_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Net {

class StateMachineWorker;
class StateMachine;

/*************************************************************************/
/** The StateMachineWorkManager class.
 *
 */
class StateMachineWorkManager {
public:

	virtual ~StateMachineWorkManager() throw();

	void start();
	void stop();
	void join();

protected:

	typedef IAS_DFT_FACTORY<StateMachineWorker>::PtrHoldersCollection WorkersSet;

	WorkersSet phcWorkers;

	StateMachineWorkManager(StateMachine *pStateMachine, int iNumWorkers);
	friend class Factory<StateMachineWorkManager>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_Net_StateMachineWorkManager_H_ */
