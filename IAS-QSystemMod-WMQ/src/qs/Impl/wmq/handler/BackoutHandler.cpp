/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/handler/BackoutHandler.cpp 
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
#include "BackoutHandler.h"

#include <commonlib/commonlib.h>
#include "../exception/WMQException.h"

#include "ObjectHandle.h"
#include "MessageHandle.h"

#include "../Session.h"
#include "../Connection.h"

#include <unistd.h>
#include "../Tools.h"

namespace IAS {
namespace QS {
namespace WMQ {
namespace Handle {
/*************************************************************************/
BackoutHandler::BackoutHandler(ObjectHandle *pObjectHandle, Session* pSession):
		pObjectHandle(pObjectHandle),
		pSession(pSession),
		iThreshold(3){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pObjectHandle);


	setupBQName();
	setupDLQName();
}
/*************************************************************************/
BackoutHandler::~BackoutHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void BackoutHandler::setupBQName(){
	IAS_TRACER;

	MQLONG tabSelectors[] = {MQIA_BACKOUT_THRESHOLD, MQCA_BACKOUT_REQ_Q_NAME};
	MQLONG tabIntAttrs[1];

	const MQLONG iCharDataSize = MQ_Q_NAME_LENGTH + 1;
	char tabChrAttrs[iCharDataSize + 1] = {0};

	try{
		pObjectHandle->getConnectionHandle()->getVTable()->MQINQ(pObjectHandle->getConnectionHandle()->mqHCONN,
													 pObjectHandle->hObj,
												     2,
													 tabSelectors,
													 1,
													 tabIntAttrs,
													 iCharDataSize,
													 tabChrAttrs);

		iThreshold = tabIntAttrs[0];
		strBQName = Tools::GetMQMDValue(tabChrAttrs,MQ_Q_NAME_LENGTH);

	}catch(WMQException& e){
		if(e.getReason() != MQRC_SELECTOR_NOT_FOR_TYPE)
			throw;

		IAS_DFT_FACTORY<Handle::ObjectHandle>::PtrHolder  ptrResolvedObjectHandler;

		ptrResolvedObjectHandler=IAS_DFT_FACTORY<Handle::ObjectHandle>::Create(
				pObjectHandle->getConnectionHandle(),
				pObjectHandle->getResolvedName(),
				MQOT_Q,
				MQOO_INQUIRE);

			pObjectHandle->getConnectionHandle()->getVTable()->MQINQ(ptrResolvedObjectHandler->getConnectionHandle()->mqHCONN,
														ptrResolvedObjectHandler->hObj,
													     2,
														 tabSelectors,
														 1,
														 tabIntAttrs,
														 iCharDataSize,
														 tabChrAttrs);

			iThreshold = tabIntAttrs[0];
			strBQName = Tools::GetMQMDValue(tabChrAttrs,MQ_Q_NAME_LENGTH);

	}

	IAS_LOG(WMQ::LogLevel::INSTANCE.isInfo(),"BQ:["<<strBQName<<"], threshold"<<iThreshold);
}
/*************************************************************************/
void BackoutHandler::setupDLQName(){
	IAS_TRACER;

	IAS_DFT_FACTORY<Handle::ObjectHandle>::PtrHolder  ptrObjectHandler;

	ptrObjectHandler=IAS_DFT_FACTORY<Handle::ObjectHandle>::Create(
			pObjectHandle->getConnectionHandle(),
			"",
			MQOT_Q_MGR,
			MQOO_INQUIRE);


	MQLONG tabSelectors[] = {MQCA_DEAD_LETTER_Q_NAME};

	const MQLONG iCharDataSize = MQ_Q_NAME_LENGTH + 1;
	char tabChrAttrs[iCharDataSize + 1] = {0};

	pObjectHandle->getConnectionHandle()->getVTable()->MQINQ(pObjectHandle->getConnectionHandle()->mqHCONN,
													     ptrObjectHandler->hObj,
													     1,
														 tabSelectors,
														 0,
														 0,
														 iCharDataSize,
														 tabChrAttrs);


	strDLQName = Tools::GetMQMDValue(tabChrAttrs,MQ_Q_NAME_LENGTH);
	IAS_LOG(WMQ::LogLevel::INSTANCE.isInfo(),"DLQ:["<<strDLQName<<"]");
}
/*************************************************************************/
void BackoutHandler::backout(MQMD& md, PMQVOID pData, MQLONG iDataLen, MessageHandle* pMessageHandle){
	IAS_TRACER;

	bool bSent = false;

	while(1){

		if(!strBQName.empty())
			bSent = sendToBQ(md,pData,iDataLen, pMessageHandle);

		if(!bSent)
			bSent = sendToDLQ(md,pData,iDataLen, pMessageHandle);

		if(bSent || pSession->getMode() == API::Session::SM_NonTransacted)
			return;

		IAS_LOG(WMQ::LogLevel::INSTANCE.isError(),"BQ and/or DLQ failed for a transacted session !!! Sleeping and retrying !");
		usleep(1000000);
	}

}
/*************************************************************************/
bool BackoutHandler::sendToBQ(MQMD& md, PMQVOID pData, MQLONG iDataLen, MessageHandle* pMessageHandle){
	IAS_TRACER;

	IAS_LOG(WMQ::LogLevel::INSTANCE.isError(),"Sending to Backout Queue, iDataLen="<<iDataLen);

	IAS_DFT_FACTORY<Handle::ObjectHandle>::PtrHolder  ptrObjectHandler;

	MQLONG iOptions=MQOO_OUTPUT | MQOO_FAIL_IF_QUIESCING;

	ptrObjectHandler=IAS_DFT_FACTORY<Handle::ObjectHandle>::Create(
			pObjectHandle->getConnectionHandle(),
			strBQName,
			MQOT_Q,
			MQOO_OUTPUT);


	MQPMO   pmo  = {MQPMO_DEFAULT};
	pmo.Version = MQPMO_VERSION_3;

	if(pSession->getMode() != Session::SM_NonTransacted)
		pmo.Options |= MQPMO_SYNCPOINT;

	pmo.NewMsgHandle=pMessageHandle->hMsg;

	pObjectHandle->getConnectionHandle()->getVTable()->MQPUT(pObjectHandle->getConnectionHandle()->mqHCONN,
			ptrObjectHandler->hObj, &md, &pmo, iDataLen, pData);

	return true;

}
/*************************************************************************/
bool BackoutHandler::sendToDLQ(MQMD& md, PMQVOID pData, MQLONG iDataLen, MessageHandle* pMessageHandle){
	IAS_TRACER;
	IAS_LOG(WMQ::LogLevel::INSTANCE.isError(),"Sending to Dead Letter Queue, iDataLen="<<iDataLen);

	IAS_DFT_FACTORY<Buffer>::PtrHolder  ptrBuffer;

	ptrBuffer = IAS_DFT_FACTORY<Buffer>::Create(iDataLen + sizeof(MQDLH));

	memcpy(ptrBuffer->getBuffer<char>()+sizeof(MQDLH),pData,iDataLen);

	MQDLH *pMQDLH =  ptrBuffer->getBuffer<MQDLH>();

	static const MQDLH dftMQDLH = { MQDLH_DEFAULT };
	memcpy(pMQDLH,&dftMQDLH,sizeof(MQDLH));

	pMQDLH->CodedCharSetId = md.CodedCharSetId;
	pMQDLH->Encoding       = md.Encoding;
	memcpy(pMQDLH->Format,   md.Format, MQ_FORMAT_LENGTH);
	pMQDLH->Reason         = 60661;

	strncpy(pMQDLH->DestQName,pObjectHandle->getName().c_str(),MQ_Q_NAME_LENGTH);
	strncpy(pMQDLH->DestQMgrName,pSession->getConnection()->getQMgrName().c_str(),MQ_Q_NAME_LENGTH);

	memcpy(pMQDLH->PutApplName,   md.PutApplName, MQ_PUT_APPL_NAME_LENGTH);
	pMQDLH->PutApplType       =   md.PutApplType;
	memcpy(pMQDLH->PutDate,   md.PutDate, MQ_PUT_DATE_LENGTH);
	memcpy(pMQDLH->PutTime,   md.PutTime, MQ_PUT_TIME_LENGTH);

	memcpy(md.Format,   MQFMT_DEAD_LETTER_HEADER, MQ_FORMAT_LENGTH);
	md.Encoding       = MQENC_NATIVE;
	md.CodedCharSetId = MQCCSI_Q_MGR;

	IAS_DFT_FACTORY<Handle::ObjectHandle>::PtrHolder  ptrObjectHandler;

	MQLONG iOptions=MQOO_OUTPUT | MQOO_FAIL_IF_QUIESCING;

	ptrObjectHandler=IAS_DFT_FACTORY<Handle::ObjectHandle>::Create(
			pObjectHandle->getConnectionHandle(),
			strDLQName,
			MQOT_Q,
			MQOO_OUTPUT);


	MQPMO   pmo  = {MQPMO_DEFAULT};
	pmo.Version = MQPMO_VERSION_3;

	if(pSession->getMode() != Session::SM_NonTransacted)
		pmo.Options |= MQPMO_SYNCPOINT;

	pmo.NewMsgHandle=pMessageHandle->hMsg;

	pObjectHandle->getConnectionHandle()->getVTable()->MQPUT(pObjectHandle->getConnectionHandle()->mqHCONN,
			ptrObjectHandler->hObj, &md, &pmo, iDataLen+sizeof(MQDLH), ptrBuffer->getBuffer<void>());

	return true;
}
/*************************************************************************/
}
}
}
}
