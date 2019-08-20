/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Session.cpp 
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
#include "Session.h"

#include <commonlib/commonlib.h>

#include "Connection.h"
#include "log/LogLevel.h"

#include "Producer.h"
#include "Consumer.h"
#include "Subscriber.h"
#include "Publisher.h"
#include "Browser.h"
#include "Requester.h"
#include "Responder.h"
#include "Controller.h"
namespace IAS {
namespace QS {
namespace WMQ {

const String Session::CEnvCCSID("IAS_QS_WMQ_CCSID");
const String Session::CEnvLazyOpen("IAS_QS_WMQ_LAZY_OPEN");

/*************************************************************************/
Session::Session(Connection* pConnection):
	pConnection(pConnection),
	iTargetCCSID(MQCCSI_Q_MGR),
	bLazyOpen(false){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);

	try{
		String sCCSID(EnvTools::GetEnv(CEnvCCSID));
		iTargetCCSID = TypeTools::StringToInt(sCCSID);
		IAS_LOG(WMQ::LogLevel::INSTANCE.isInfo(),"Target CCSID="<<iTargetCCSID);
	}catch(ItemNotFoundException &e){};

	String strLazyOpen;
	bLazyOpen = EnvTools::GetEnv(CEnvLazyOpen,strLazyOpen) &&
									(!strLazyOpen.compare("Y") || !strLazyOpen.compare("y"));

	IAS_LOG(WMQ::LogLevel::INSTANCE.isInfo(),"bLazyOpen = "<<bLazyOpen);
}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Connection* Session::getConnection()const{
	IAS_TRACER;
	return pConnection;
}
/*************************************************************************/
API::Controller*  Session::createController(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Controller>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Producer*  Session::createProducer(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Producer>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Consumer*  Session::createConsumer(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Consumer>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Browser*  Session::createBrowser(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Browser>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Subscriber*  Session::createSubscriber(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Subscriber>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Publisher*  Session::createPublisher(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Publisher>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Requester*  Session::createRequester(const API::Destination& outDestination,
										  const API::Destination& inDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Requester>::Create<Session*, const API::Destination&,const API::Destination&>
			(this, outDestination,inDestination);
}
/*************************************************************************/
API::Responder* Session::createResponder(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Responder>::Create<Session*>(this);
}
/*************************************************************************/
}
}
}
