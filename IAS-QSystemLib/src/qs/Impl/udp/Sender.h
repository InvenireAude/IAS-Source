/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Sender.h
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
#ifndef _IAS_QS_UDP_Sender_H_
#define _IAS_QS_UDP_Sender_H_

#include "Sender.h"

#include <qs/api/Sender.h>
#include <qs/api/Destination.h>

#include <qs/Impl/shm/shared/Queue.h>

#include "Manageable.h"

namespace IAS {
namespace QS {
namespace UDP {

class OutputDriver;
/*************************************************************************/
/** The Sender class.
 *
 */
class Sender : public Manageable,
			   public virtual API::Sender{

public:

	virtual ~Sender() throw();

	virtual bool send(API::Message* pMessage);

protected:
	Sender(Session* pSession, const API::Destination& refDestination);

	API::Destination myDestination;

	OutputDriver*	 pDriver;

	friend class Factory<Sender>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_UDP_Sender_H_ */
