/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Manageable.h
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
#ifndef _IAS_QS_UDP_Manageable_H_
#define _IAS_QS_UDP_Manageable_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace UDP {

class Session;

/*************************************************************************/
/** The Manageable class.
 *
 */
class Manageable {
public:

	virtual ~Manageable() throw();

protected:
	Manageable(Session* pSession);

	inline Session* getSession() {return pSession;}

private:
	Session* pSession;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Manageable_H_ */
