/*
 * MCast: IAS-QSystemLib/src/qs/Impl/sdf/file/InputDriver.h
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
#ifndef _IAS_QS_UDP_MCast_InputDriver_H_
#define _IAS_QS_UDP_MCast_InputDriver_H_

#include <qs/api.h>

#include "../InputDriver.h"

namespace IAS {
namespace QS {
namespace UDP {
namespace MCast {

/*************************************************************************/
/** The InputDriver class.
 *
 */
class InputDriver : public UDP::InputDriver {
public:

	virtual ~InputDriver() throw();

	virtual Message* receive(int iTimeWait, API::Attributes* pSelector);

  virtual unsigned int skip(unsigned int iOffset);

protected:
	InputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
              const API::Destination& destination);

  Net::MCast::Receiver receiver;

	friend class Factory<InputDriver>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_UDP_MCast_InputDriver_H_ */
