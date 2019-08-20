/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Administrator.cpp 
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
#include "Administrator.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "System.h"

#include <org/invenireaude/qsystem/stats/SystemStats.h>
#include <org/invenireaude/qsystem/stats/QueueStats.h>
#include <org/invenireaude/qsystem/stats/TopicStats.h>
#include <org/invenireaude/qsystem/stats/Sample.h>
#include <org/invenireaude/qsystem/stats/DataFactory.h>

#include <cmqcfc.h>

#include "handler/BagHandle.h"
#include "exception/WMQException.h"

#include "System.h"
#include "Connection.h"

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
Administrator::Administrator(Connection* pConnection):
		pConnection(pConnection){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pConnection);
}
/*************************************************************************/
Administrator::~Administrator() throw(){
	IAS_TRACER;
}
/*************************************************************************/
stats::Ext::SystemStatsPtr Administrator::getStats(bool bReset){
	IAS_TRACER;

	stats::Ext::SystemStatsPtr dmStats(stats::DataFactory::GetInstance()->createSystemStats());

	System* pSystem = pConnection->getSystem();

	dmStats->setName(pConnection->getName());

	IAS_DFT_FACTORY<Handle::BagHandle>::PtrHolder ptrAdminBag(
			IAS_DFT_FACTORY<Handle::BagHandle>::Create(pSystem->getVTable(),MQCBO_ADMIN_BAG));

	IAS_DFT_FACTORY<Handle::BagHandle>::PtrHolder ptrResponseBag(
			IAS_DFT_FACTORY<Handle::BagHandle>::Create(pSystem->getVTable(),MQCBO_ADMIN_BAG));

	pSystem->getVTable()->mqAddString(ptrAdminBag->mqHBAG,MQCA_Q_NAME,MQBL_NULL_TERMINATED,const_cast<char*>("*"));

	pSystem->getVTable()->mqAddInteger(ptrAdminBag->mqHBAG,MQIA_Q_TYPE,MQQT_LOCAL);

	try{
		pSystem->getVTable()->mqExecute(pConnection->getConnectionHandle()->mqHCONN,
										MQCMD_INQUIRE_Q,
										MQHB_NONE,
										ptrAdminBag->mqHBAG,
										ptrResponseBag->mqHBAG,
										MQHO_NONE,
										MQHO_NONE);

	}catch(WMQException& e){

		if(e.getReason() != MQRCCF_COMMAND_FAILED)
			throw;

		MQHBAG hErrorBag;
		MQLONG rc;
		pSystem->getVTable()->mqInquireBag(ptrResponseBag->mqHBAG, MQHA_BAG_HANDLE, 0, &hErrorBag);
		pSystem->getVTable()->mqInquireInteger(hErrorBag, MQIASY_REASON, MQIND_NONE,&rc);

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Error: "<<rc);

	}

	MQLONG iNumberOfBags;
	pSystem->getVTable()->mqCountItems(ptrResponseBag->mqHBAG, MQHA_BAG_HANDLE, &iNumberOfBags);


	for(int iIdx=0;iIdx<iNumberOfBags;iIdx++){

		MQHBAG hAttrsBag;
		MQLONG iQDepth;
		MQLONG iQMaxDepth;
		MQLONG iQNumInProc;
		MQLONG iQNumOutProc;

		MQLONG iNameLength;
		MQCHAR sName[MQ_Q_NAME_LENGTH+1];

		pSystem->getVTable()->mqInquireBag(ptrResponseBag->mqHBAG, MQHA_BAG_HANDLE, iIdx, &hAttrsBag);

		pSystem->getVTable()->mqInquireString(hAttrsBag, MQCA_Q_NAME, 0, MQ_Q_NAME_LENGTH, sName,
											  &iNameLength, NULL);

		if(strncmp(sName,"SYSTEM.",7) == 0 || strncmp(sName,"MQAI.",5)==0)
			continue;

		pSystem->getVTable()->mqInquireInteger(hAttrsBag, MQIA_CURRENT_Q_DEPTH, MQIND_NONE, &iQDepth);
		pSystem->getVTable()->mqInquireInteger(hAttrsBag, MQIA_MAX_Q_DEPTH, MQIND_NONE, &iQMaxDepth);
		pSystem->getVTable()->mqInquireInteger(hAttrsBag, MQIA_OPEN_INPUT_COUNT, MQIND_NONE, &iQNumInProc);
		pSystem->getVTable()->mqInquireInteger(hAttrsBag, MQIA_OPEN_OUTPUT_COUNT, MQIND_NONE, &iQNumOutProc);
		pSystem->getVTable()->mqTrim(MQ_Q_NAME_LENGTH, sName, sName);

		stats::QueueStats* pQueue=dmStats->createQueues();
		stats::Sample* pSample=0;
		pQueue->setName(sName);
		pQueue->setNumMsgs(iQDepth);
		pQueue->setSize(iQMaxDepth);
		pQueue->setHanders(iQNumInProc+iQNumOutProc);
		pSample=pQueue->createPuts();
		pSample->setNum(0);
		pSample=pQueue->createGets();
		pSample->setNum(0);
		pQueue->setWaits(0);
	}

	dmStats->setGeneratedOn(DateTime(true));

	return dmStats;
}
/*************************************************************************/
}
}
}
