/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/VTable.cpp 
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
#include <pthread.h>

#include "VTable.h"

#include <commonlib/commonlib.h>

#include "ContentManager.h"
#include "Connection.h"
#include "exception/WMQException.h"

#include <unistd.h>

/*
 * MQSeries Application Programming Guide
 * ===========================================
 *
 * In the case of C++ destructor methods, which may be called automatically during
 * program exit, you may not be able to stop the MQI functions from being called.
 * Therefore, ignore any errors about MQRC_CALL_IN_PROGRESS.
 *
 */

#ifndef _AIX
#define _IAS_RTLD_OPTIONS (RTLD_NOW |RTLD_GLOBAL)
#else
#define _IAS_RTLD_OPTIONS (RTLD_NOW |RTLD_GLOBAL | RTLD_MEMBER)
#endif

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
const String VTable::CWaitOnExclusive("IAS_QS_MQ_WAIT_ON_EXCL");
/*************************************************************************/
VTable::VTable(const String& strLibraryName):
	::IAS::SYS::DynamicLibrary(strLibraryName, _IAS_RTLD_OPTIONS ),
	 iWaitOnExclusiveOpen(0){
	IAS_TRACER;

	pMQCONN=(PMQCONN)(getSymbol("MQCONN"));
	pMQDISC=(PMQDISC)(getSymbol("MQDISC"));

	pMQOPEN =(PMQOPEN) (getSymbol("MQOPEN"));
	pMQSUB  =(PMQSUB)  (getSymbol("MQSUB"));
	pMQCLOSE=(PMQCLOSE)(getSymbol("MQCLOSE"));

	pMQSET  =(PMQSET)  (getSymbol("MQSET"));
	pMQINQ  =(PMQINQ)  (getSymbol("MQINQ"));

	pMQCRTMH = (PMQCRTMH) (getSymbol("MQCRTMH"));
	pMQINQMP = (PMQINQMP) (getSymbol("MQINQMP"));
	pMQSETMP = (PMQSETMP) (getSymbol("MQSETMP"));
	pMQDLTMH = (PMQDLTMH) (getSymbol("MQDLTMH"));

	pMQGET=(PMQGET)(getSymbol("MQGET"));
	pMQPUT=(PMQPUT)(getSymbol("MQPUT"));
	pMQPUT1=(PMQPUT1)(getSymbol("MQPUT1"));

	pMQBEGIN = (PMQBEGIN)(getSymbol("MQBEGIN"));
	pMQCMIT  = (PMQCMIT)(getSymbol("MQCMIT"));
	pMQBACK  = (PMQBACK)(getSymbol("MQBACK"));

	pmqAddInquiry  = (PtrAddInquiry)(getSymbol("mqAddInquiry"));
	pmqAddInteger  = (PtrAddInteger)(getSymbol("mqAddInteger"));
	pmqAddString   = (PtrAddString)(getSymbol("mqAddString"));

	pmqCountItems = (PtrCountItems)(getSymbol("mqCountItems"));
	pmqCreateBag  = (PtrCreateBag)(getSymbol("mqCreateBag"));
	pmqDeleteBag  = (PtrDeleteBag)(getSymbol("mqDeleteBag"));

	pmqExecute = (PtrExecute)(getSymbol("mqExecute"));

	pmqInquireBag     = (PtrInquireBag)(getSymbol("mqInquireBag"));
	pmqInquireInteger = (PtrInquireInteger)(getSymbol("mqInquireInteger"));
	pmqInquireString  = (PtrInquireString)(getSymbol("mqInquireString"));

	pmqTrim = (PtrTrim)(getSymbol("mqTrim"));

	String strWaitOnExclusiveOpen("0");

	if(EnvTools::GetEnv(CWaitOnExclusive, strWaitOnExclusiveOpen)){
		iWaitOnExclusiveOpen=TypeTools::StringToInt(strWaitOnExclusiveOpen);
	}
}
/*************************************************************************/
VTable::~VTable()throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool VTable::MQCONN(PMQCHAR sConnection,PMQHCONN pHandle)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	Thread::Cancellation::Test();
	Thread::Cancellation tc(true);


	(*pMQCONN)(sConnection,pHandle,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc<<", pHandle="<<(void*)(long)(*pHandle));

	if(cc == MQCC_FAILED &&
			rc != MQRC_ALREADY_CONNECTED)
		IAS_THROW(WMQException(String("MQCONN")+" ["+sConnection+"]",rc));

	return rc != MQRC_ALREADY_CONNECTED;
}
/*************************************************************************/
void VTable::MQDISC(PMQHCONN pHandle)const{
	IAS_TRACER;

	MQLONG cc=0;
	MQLONG rc=0;

	if(! std::uncaught_exception())
		if(!SYS::Signal::GetInstance()->isStopping())
			(*pMQDISC)(pHandle,&cc,&rc);


	IAS_LOG(LogLevel::INSTANCE.isInfo()|| (rc != MQCC_OK && rc != MQRC_CALL_IN_PROGRESS) ,"CC="<<cc<<", RC="<<rc);


	if(cc == MQCC_FAILED &&
	   rc != MQRC_CALL_IN_PROGRESS)
		IAS_THROW(WMQException("MQDISC",rc));

}
/*************************************************************************/
void VTable::MQOPEN(MQHCONN hConn, PMQVOID pMQDesc, MQLONG iOpts, PMQHOBJ pHObj)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	bool bDone=false;

	while(!bDone){

		(*pMQOPEN)(hConn,pMQDesc,iOpts,pHObj,&cc,&rc);

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

		if(rc != MQRC_OBJECT_IN_USE || !iWaitOnExclusiveOpen){

			if(cc == MQCC_FAILED)
				IAS_THROW(WMQException("MQOPEN",rc));

			bDone = true;

		}else{

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"Waiting: MQRC_OBJECT_IN_USE, "<<iWaitOnExclusiveOpen<<"s.");

			Thread::Cancellation::Test();
			Thread::Cancellation tc(true);

			sleep(iWaitOnExclusiveOpen);
		}

	}

}
/*************************************************************************/
void VTable::MQSUB(MQHCONN hConn, PMQVOID pSubDesc, PMQHOBJ pHObj, PMQHOBJ  pHsub)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQSUB)(hConn,pSubDesc,pHObj,pHsub,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQSUB",rc));

}
/*************************************************************************/
void VTable::MQCLOSE(MQHCONN hConn, PMQHOBJ pHObj, MQLONG iOpts)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	if(SYS::Signal::GetInstance()->isStopping())
		return;

	(*pMQCLOSE)(hConn,pHObj,iOpts,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED &&
			rc != MQRC_CALL_IN_PROGRESS)
		IAS_THROW(WMQException("MQCLOSE",rc));

}
/*************************************************************************/
void VTable::MQINQ(MQHCONN hConn, MQHOBJ hObj, MQLONG iSelectorCount, PMQLONG  pSelectors,
					MQLONG   iAttrCount,PMQLONG  pIntAttrs, MQLONG   iCharAttrLength, PMQCHAR  pCharAttrs)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQINQ)(hConn,hObj,iSelectorCount,pSelectors,iAttrCount,pIntAttrs,iCharAttrLength,pCharAttrs,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED || rc == MQRC_SELECTOR_NOT_FOR_TYPE)
		IAS_THROW(WMQException("MQINQ",rc));

}
/*************************************************************************/
void VTable::MQSET(MQHCONN hConn, MQHOBJ hObj, MQLONG iSelectorCount, PMQLONG  pSelectors,
					MQLONG   iAttrCount,PMQLONG  pIntAttrs, MQLONG   iCharAttrLength, PMQCHAR  pCharAttrs)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQSET)(hConn,hObj,iSelectorCount,pSelectors,iAttrCount,pIntAttrs,iCharAttrLength,pCharAttrs,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQSET",rc));

}
/*************************************************************************/
void VTable::MQCRTMH(MQHCONN hConn, PMQVOID   pCrtMsgHOpts, PMQHMSG   pHmsg)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQCRTMH)(hConn,pCrtMsgHOpts,pHmsg,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQCRTMH",rc));

}
/*************************************************************************/
void VTable::MQDLTMH(MQHCONN   hConn,PMQHMSG   pHmsg,PMQVOID   pDltMsgHOpts)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQDLTMH)(hConn,pHmsg,pDltMsgHOpts,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED &&
			rc != MQRC_CALL_IN_PROGRESS)
		IAS_THROW(WMQException("MQDLTMH",rc));

}
/*************************************************************************/
bool VTable::MQINQMP(MQHCONN hConn, MQHMSG    Hmsg, PMQVOID   pInqPropOpts, PMQVOID   pName,
		     PMQVOID   pPropDesc, PMQLONG   pType, MQLONG    iValueLength, PMQVOID   pValue,
		     PMQLONG   pDataLength)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQINQMP)(hConn,Hmsg,pInqPropOpts,pName,pPropDesc,pType,iValueLength,pValue,pDataLength,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(rc == MQRC_PROPERTY_NOT_AVAILABLE)
			return false;

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQINQMP",rc));

	return true;
}
/*************************************************************************/
void VTable::MQSETMP(MQHCONN hConn, MQHMSG hMsg, PMQVOID   pSetPropOpts, PMQVOID   pName,
					 PMQVOID   pPropDesc, MQLONG iType, MQLONG iValueLength, PMQVOID   pValue)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQSETMP)(hConn,hMsg,pSetPropOpts,pName,pPropDesc,iType,iValueLength,pValue,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQSETMP",rc));

}
/*************************************************************************/
bool VTable::MQGET(MQHCONN hConn, MQHOBJ hObj, PMQVOID pMD, PMQGMO pGMO, MQLONG iBufferLen, PMQVOID pBuffer, PMQLONG pDataLen)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	{
		Thread::Cancellation::Test();
		Thread::Cancellation tc(true);
		(*pMQGET)(hConn,hObj,pMD,pGMO,iBufferLen,pBuffer,pDataLen,&cc,&rc);
	}

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(rc == MQRC_NO_MSG_AVAILABLE)
		IAS_THROW(EndOfDataException("MQGET"));

	if(rc == MQRC_TRUNCATED_MSG_FAILED)
		return false;

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQGET",rc));

	return true;
}
/*************************************************************************/
void VTable::MQPUT(MQHCONN hConn, MQHOBJ hObj, PMQVOID pMD, PMQVOID pPMO, MQLONG iBufferLen ,PMQVOID pBuffer)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQPUT)(hConn,hObj,pMD,pPMO,iBufferLen,pBuffer,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQPUT",rc));
}
/*************************************************************************/
void VTable::MQPUT1(MQHCONN hConn, PMQVOID  pObjDesc, PMQVOID pMD, PMQVOID pPMO, MQLONG iBufferLen ,PMQVOID pBuffer)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQPUT1)(hConn,pObjDesc,pMD,pPMO,iBufferLen,pBuffer,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQPUT1",rc));
}
/*************************************************************************/
void VTable::MQBEGIN(MQHCONN hConn)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	MQBO bo = {MQBO_DEFAULT};
	(*pMQBEGIN)(hConn,&bo,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQBEGIN",rc));
}
/*************************************************************************/
void VTable::MQCMIT(MQHCONN hConn)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQCMIT)(hConn,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("MQCMIT",rc));
}
/*************************************************************************/
void VTable::MQBACK(MQHCONN hConn)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pMQBACK)(hConn,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED &&
			rc != MQRC_CALL_IN_PROGRESS)
		IAS_THROW(WMQException("MQBACK",rc));
}
/*************************************************************************/
void VTable::mqAddInquiry (MQHBAG   bag, MQLONG   selector)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pmqAddInquiry)(bag,selector,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("mqAddInquiry",rc));
}
/*************************************************************************/
void VTable::mqAddInteger(MQHBAG   bag, MQLONG   selector,  MQLONG   value)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pmqAddInteger)(bag,selector,value,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("mqAddInteger",rc));
}
/*************************************************************************/
void VTable::mqAddString(MQHBAG   bag, MQLONG   selector,  MQLONG   len, PMQCHAR value)const{
	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pmqAddString)(bag,selector,len,value,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("mqAddString",rc));
}
/*************************************************************************/
void VTable::mqCountItems (MQHBAG   bag, MQLONG   selector,  PMQLONG  result)const{

	IAS_TRACER;

	MQLONG cc;
	MQLONG rc;

	(*pmqCountItems)(bag,selector,result,&cc,&rc);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

	if(cc == MQCC_FAILED)
		IAS_THROW(WMQException("mqCountItems",rc));
}
/*************************************************************************/
void VTable::mqCreateBag(MQLONG options, PMQHBAG  pBag)const{

   	IAS_TRACER;

   	MQLONG cc;
   	MQLONG rc;

   	(*pmqCreateBag)(options,pBag,&cc,&rc);

   	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

   	if(cc == MQCC_FAILED)
   		IAS_THROW(WMQException("mqCreateBag",rc));
}
/*************************************************************************/
 void VTable::mqDeleteBag  (PMQHBAG  pBag)const{

   	IAS_TRACER;

   	MQLONG cc;
   	MQLONG rc;

   	(*pmqDeleteBag)(pBag,&cc,&rc);

   	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

   	if(cc == MQCC_FAILED)
   		IAS_THROW(WMQException("mqDeleteBag",rc));
 }
/*************************************************************************/
void VTable::mqExecute(MQHCONN  Hconn,
   			           MQLONG   Command,
					   MQHBAG   OptionsBag,
					   MQHBAG   AdminBag,
					   MQHBAG   ResponseBag,
					   MQHOBJ   AdminQ,
					   MQHOBJ   ResponseQ)const{
   	IAS_TRACER;

   	MQLONG cc;
   	MQLONG rc;

   	(*pmqExecute)(Hconn,Command,OptionsBag,AdminBag,ResponseBag,AdminQ,ResponseQ,&cc,&rc);

   	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

   	if(cc == MQCC_FAILED)
   		IAS_THROW(WMQException("mqExecute",rc));
}
/*************************************************************************/
void VTable::mqInquireBag(MQHBAG bag, MQLONG selector, MQLONG index, PMQHBAG  pItemValue)const{

	IAS_TRACER;

   	MQLONG cc;
   	MQLONG rc;

   	(*pmqInquireBag)(bag,selector,index,pItemValue,&cc,&rc);

   	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

   	if(cc == MQCC_FAILED)
   		IAS_THROW(WMQException("mqInquireBag",rc));
}
/*************************************************************************/
void VTable::mqInquireInteger (MQHBAG bag, MQLONG selector, MQLONG index, PMQLONG  pItemValue)const{

   	IAS_TRACER;

   	MQLONG cc;
   	MQLONG rc;

   	(*pmqInquireInteger)(bag,selector,index,pItemValue,&cc,&rc);

   	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

   	if(cc == MQCC_FAILED)
   		IAS_THROW(WMQException("mqInquireInteger",rc));
}
/*************************************************************************/
void VTable::mqInquireString  (MQHBAG bag, MQLONG selector, MQLONG index, MQLONG buflen, PMQCHAR buf, PMQLONG strlen,
   							   PMQLONG ccsid)const{
   	IAS_TRACER;

   	MQLONG cc;
   	MQLONG rc;

   	(*pmqInquireString)(bag,selector,index,buflen,buf,strlen,ccsid,&cc,&rc);

   	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

   	if(cc == MQCC_FAILED)
   		IAS_THROW(WMQException("mqInquireString",rc));
}
/*************************************************************************/
void VTable::mqTrim(MQLONG buflen, PMQCHAR  buf, PMQCHAR str)const{

   	IAS_TRACER;

   	MQLONG cc;
   	MQLONG rc;

   	(*pmqTrim)(buflen,buf,str,&cc,&rc);

   	IAS_LOG(LogLevel::INSTANCE.isInfo(),"CC="<<cc<<", RC="<<rc);

   	if(cc == MQCC_FAILED)
   		IAS_THROW(WMQException("mqTrim",rc));
   }
   /*************************************************************************/
}
}
}
