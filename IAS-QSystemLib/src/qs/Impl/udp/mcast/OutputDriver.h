/*
 * MCast: IAS-QSystemLib/src/qs/Impl/sdf/file/OutputDriver.h
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
#ifndef _IAS_QS_UDP_MCast_OutputDriver_H_
#define _IAS_QS_UDP_MCast_OutputDriver_H_

#include "../Driver.h"
#include <qs/api.h>

namespace IAS {
namespace QS {
namespace UDP {
namespace MCast {

/*************************************************************************/
/** The OutputDriver class.
 *
 */
class OutputDriver : public UDP::OutputDriver {
public:

	virtual ~OutputDriver() throw();

	virtual bool send(Message* pMessage);

protected:

	OutputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection, const API::Destination& destination);

	String strMCastName;
	int    iCount;

  Net::MCast::Sender sender;
  API::Destination   destination;

	Mutex mutex;

  Buffer buffer;

	friend class Factory<OutputDriver>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_UDP_MCast_OutputDriver_H_ */
