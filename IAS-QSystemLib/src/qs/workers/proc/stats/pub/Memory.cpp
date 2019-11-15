/*
 * File: Memory.cpp
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

#include "Memory.h"
#include <iomanip>

#include <org/invenireaude/qsystem/workers/stats/LogicSample.h>
#include <org/invenireaude/qsystem/workers/stats/LogicSamplesSet.h>
#include <org/invenireaude/qsystem/stats/Sample.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>
#include "../PublisherStore.h"

using namespace ::org::invenireaude::qsystem::workers;
using namespace ::org::invenireaude;

using namespace std;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Stats {
namespace Pub {

/*************************************************************************/
Memory::Memory(){
	IAS_TRACER;
}
/*************************************************************************/
Memory::~Memory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Memory::publish(stats::LogicSamplesSet* dmLogicSamplesSet,
					  WCM::WorkContextManager* pWorkContextManager)const{
	IAS_TRACER;

}
/*************************************************************************/

}
}
}
}
}
}
