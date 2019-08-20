/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Session.h 
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License. 
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 * 
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 * 
 */
#ifndef _IAS_QS_WMQ_Session_H_
#define _IAS_QS_WMQ_Session_H_

#include <qs/api/Session.h>
#include <qs/api/Destination.h>

#include <cmqc.h>

namespace IAS {
namespace QS {
namespace WMQ {

class Connection;

/*************************************************************************/
/** The Session class.
 *
 */
class Session : public virtual API::Session {
public:

	virtual ~Session() throw();

	Connection* getConnection()const;


	inline MQLONG getTargetCCSID() const { return iTargetCCSID; }
	inline bool isLazyOpen()const{	return bLazyOpen; }

protected:
	Session(Connection* pConnection);

	Connection* pConnection;

	virtual API::Controller* createController(const API::Destination& refDestination);

	virtual API::Producer*   createProducer(const API::Destination& refDestination);
	virtual API::Consumer*   createConsumer(const API::Destination& refDestination);
	virtual API::Browser*    createBrowser(const API::Destination& refDestination);
	virtual API::Subscriber* createSubscriber(const API::Destination& refDestination);
	virtual API::Publisher*  createPublisher(const API::Destination& refDestination);

	virtual API::Requester*  createRequester(const API::Destination& outDestination,
											 const API::Destination& inDestination);

	virtual API::Responder*  createResponder();

	MQLONG iTargetCCSID;

	bool   bLazyOpen;

	static const String CEnvCCSID;
	static const String CEnvLazyOpen;

	friend class Factory<Session>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_Session_H_ */
