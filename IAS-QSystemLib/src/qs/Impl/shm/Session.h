/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Session.h
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
#ifndef _IAS_QS_System_Session_H_
#define _IAS_QS_System_Session_H_

#include <qs/api/Session.h>
#include <qs/api/Destination.h>

#include "shared/Session.h"

namespace IAS {
namespace QS {
namespace SHM {

class Connection;

/*************************************************************************/
/** The Session class.
 *
 */
class Session : public virtual API::Session {
public:

	virtual ~Session() throw();

	Connection* getConnection()const;

	Shared::Session* getSHMSession(){ return ptrSession.operator->(); }

protected:
	Session(Shared::Session* pSession, Connection* pConnection);

	Connection*              pConnection;
	Shared::Session::Holder  ptrSession;

	virtual API::Controller* createController(const API::Destination& refDestination);

	virtual API::Producer*   createProducer(const API::Destination& refDestination);
	virtual API::Consumer*   createConsumer(const API::Destination& refDestination);
	virtual API::Browser*    createBrowser(const API::Destination& refDestination);
	virtual API::Subscriber* createSubscriber(const API::Destination& refDestination);
	virtual API::Publisher*  createPublisher(const API::Destination& refDestination);

	virtual API::Requester*  createRequester(const API::Destination& outDestination,
											 const API::Destination& inDestination);

	virtual API::Responder*  createResponder();

	friend class Factory<Session>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Session_H_ */
