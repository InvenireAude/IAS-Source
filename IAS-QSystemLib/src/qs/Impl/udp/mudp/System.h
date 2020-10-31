/*
 * MUDP: IAS-QSystemLib/src/qs/Impl/sdf/file/System.h
 *
 * Copyright (C) 2020, Albert Krzymowski
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
#ifndef _IAS_QS_UDP_MUDP_System_H_
#define _IAS_QS_UDP_MUDP_System_H_

#include "../System.h"

namespace IAS {
namespace QS {
namespace UDP {
namespace MUDP {

class InputDriver;
class OutputDriver;

/*************************************************************************/
/** The UDP class.
 *
 */
class System : public UDP::System {
public:

	virtual ~System() throw();

	virtual UDP::InputDriver*  createInputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                              const API::Destination& destination);

	virtual UDP::OutputDriver* createOutputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                              const API::Destination& destination);


protected:

	System();

	friend class IAS::Factory<System>;
};
/*************************************************************************/

}
}
}
}

#endif /* _IAS_QS_UDP_MUDP_System_H_ */
