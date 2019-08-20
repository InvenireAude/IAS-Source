/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/VTable.h 
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
#ifndef _IAS_QS_WMQ_VTable_H_
#define _IAS_QS_WMQ_VTable_H_

#include <commonlib/commonlib.h>

#include <qs/api.h>
#include <cmqc.h>
#include <cmqbc.h>

#include "log/LogLevel.h"

namespace IAS {
namespace QS {
namespace WMQ {
/*************************************************************************/
/** The WMQ class.
 *
 */
class VTable : protected ::IAS::SYS::DynamicLibrary {
public:

	virtual ~VTable() throw();

	bool MQCONN(PMQCHAR sConnection, PMQHCONN pHandle)const;
	void MQDISC(PMQHCONN pHandle)const;

	void MQOPEN(MQHCONN hConn, PMQVOID pObjDesc, MQLONG iOpts,  PMQHOBJ pHObj)const;
	void MQSUB(MQHCONN hConn, PMQVOID pSubDesc, PMQHOBJ pHObj, PMQHOBJ  pHsub)const;
	void MQCLOSE(MQHCONN hConn, PMQHOBJ pHObj, MQLONG iOpts)const;

	void MQINQ (MQHCONN hConn, MQHOBJ hObj, MQLONG iSelectorCount, PMQLONG  pSelectors,
				MQLONG   iAttrCount,PMQLONG  pIntAttrs, MQLONG   iCharAttrLength, PMQCHAR  pCharAttrs)const;

	void MQSET (MQHCONN hConn, MQHOBJ hObj, MQLONG iSelectorCount, PMQLONG  pSelectors,
				MQLONG   iAttrCount,PMQLONG  pIntAttrs, MQLONG   iCharAttrLength, PMQCHAR  pCharAttrs)const;

	void MQCRTMH(MQHCONN hConn, PMQVOID   pCrtMsgHOpts, PMQHMSG   pHmsg)const;
	bool MQINQMP(MQHCONN hConn, MQHMSG    Hmsg, PMQVOID   pInqPropOpts, PMQVOID   pName,
			     PMQVOID   pPropDesc, PMQLONG   pType, MQLONG    ValueLength, PMQVOID   pValue,
			     PMQLONG   pDataLength)const;

	void MQSETMP(MQHCONN hConn, MQHMSG hMsg, PMQVOID   pSetPropOpts, PMQVOID   pName,
				 PMQVOID   pPropDesc, MQLONG    Type, MQLONG    ValueLength, PMQVOID   pValue)const;

	void MQDLTMH(MQHCONN   hConn,PMQHMSG   pHmsg,PMQVOID   pDltMsgHOpts)const;

	bool MQGET(MQHCONN hConn,  MQHOBJ hObj, PMQVOID pMD, PMQGMO pGMO, MQLONG iBufferLen, PMQVOID pBuffer, PMQLONG pDataLen)const;
	void MQPUT(MQHCONN hConn,  MQHOBJ hObj, PMQVOID pMD, PMQVOID pPMO, MQLONG iBufferLen ,PMQVOID pBuffer)const;
	void MQPUT1(MQHCONN hConn, PMQVOID  pObjDesc, PMQVOID pMD, PMQVOID pPMO, MQLONG iBufferLen ,PMQVOID pBuffer)const;

	void MQBEGIN(MQHCONN hConn)const;
	void MQCMIT(MQHCONN hConn)const;
	void MQBACK(MQHCONN hConn)const;


	void mqAddInquiry (MQHBAG   bag, MQLONG   selector)const;
    void mqAddInteger (MQHBAG   bag, MQLONG   selector,  MQLONG   value)const;
    void mqAddString  (MQHBAG   bag, MQLONG   selector,  MQLONG   len, PMQCHAR value)const;
    void mqCountItems (MQHBAG   bag, MQLONG   selector,  PMQLONG  result)const;
    void mqCreateBag  (MQLONG   options, PMQHBAG  pBag)const;
    void mqDeleteBag  (PMQHBAG  pBag)const;

    void mqExecute    (MQHCONN  Hconn,
    			       MQLONG   Command,
					   MQHBAG   OptionsBag,
					   MQHBAG   AdminBag,
					   MQHBAG   ResponseBag,
					   MQHOBJ   AdminQ,
					   MQHOBJ   ResponseQ)const;

    void mqInquireBag     (MQHBAG bag, MQLONG selector, MQLONG index, PMQHBAG  pItemValue)const;
    void mqInquireInteger (MQHBAG bag, MQLONG selector, MQLONG index, PMQLONG  pItemValue)const;
    void mqInquireString  (MQHBAG bag, MQLONG selector, MQLONG index, MQLONG buflen, PMQCHAR buf, PMQLONG strlen,
    							   PMQLONG ccsid)const;

    void mqTrim(MQLONG buflen, PMQCHAR  buf, PMQCHAR str)const;

protected:

	typedef void (*PMQCONN) (PMQCHAR,PMQHCONN,PMQLONG,PMQLONG);
	typedef void (*PMQDISC) (PMQHCONN,PMQLONG,PMQLONG);

	typedef void (*PMQOPEN)  (MQHCONN, PMQVOID, MQLONG, PMQHOBJ,PMQLONG,PMQLONG);
	typedef void (*PMQSUB)   (MQHCONN, PMQVOID, PMQHOBJ, PMQHOBJ, PMQLONG,PMQLONG);

	typedef void (*PMQCLOSE) (MQHCONN, PMQHOBJ, MQLONG, PMQLONG,PMQLONG);

	typedef void (*PMQINQ) (MQHCONN, MQHOBJ, MQLONG, PMQLONG, MQLONG,PMQLONG,MQLONG,PMQCHAR,PMQLONG,PMQLONG);
	typedef void (*PMQSET) (MQHCONN, MQHOBJ, MQLONG, PMQLONG, MQLONG,PMQLONG,MQLONG,PMQCHAR,PMQLONG,PMQLONG);

	typedef void (*PMQCRTMH)(MQHCONN, PMQVOID, PMQHMSG, PMQLONG, PMQLONG);
	typedef void (*PMQINQMP)(MQHCONN, MQHMSG, PMQVOID, PMQVOID, PMQVOID,
			           PMQLONG, MQLONG, PMQVOID,PMQLONG, PMQLONG, PMQLONG);

	typedef void (*PMQSETMP)(MQHCONN, MQHMSG, PMQVOID, PMQVOID, PMQVOID, MQLONG,
							 MQLONG, PMQVOID,PMQLONG, PMQLONG);;

	typedef void (*PMQDLTMH)(MQHCONN, PMQHMSG, PMQVOID, PMQLONG, PMQLONG);

	typedef void (*PMQGET)  (MQHCONN, MQHOBJ, PMQVOID, PMQVOID, MQLONG, PMQVOID, PMQLONG, PMQLONG,PMQLONG);
	typedef void (*PMQPUT)  (MQHCONN, MQHOBJ, PMQVOID, PMQVOID, MQLONG, PMQVOID, PMQLONG, PMQLONG);
	typedef void (*PMQPUT1)  (MQHCONN, PMQVOID, PMQVOID, PMQVOID, MQLONG, PMQVOID, PMQLONG, PMQLONG);

	typedef void (*PMQBEGIN) (MQHCONN,PMQBO,PMQLONG,PMQLONG);
	typedef void (*PMQCMIT)  (MQHCONN,PMQLONG,PMQLONG);
	typedef void (*PMQBACK)  (MQHCONN,PMQLONG,PMQLONG);

	/* Administration API */
	typedef void (*PtrAddInquiry)  (MQHBAG, MQLONG, PMQLONG, PMQLONG);
	typedef void (*PtrAddInteger)  (MQHBAG, MQLONG, MQLONG, PMQLONG, PMQLONG);
	typedef void (*PtrAddString)  (MQHBAG, MQLONG, MQLONG, PMQCHAR, PMQLONG, PMQLONG);

	typedef void (*PtrCountItems) (MQHBAG,  MQLONG, PMQLONG, PMQLONG, PMQLONG);
	typedef void (*PtrCreateBag)  (MQLONG,  PMQHBAG, PMQLONG, PMQLONG);
	typedef void (*PtrDeleteBag)  (PMQHBAG, PMQLONG, PMQLONG);

	typedef void (*PtrExecute)    (MQHCONN, MQLONG, MQHBAG, MQHBAG, MQHBAG, MQHOBJ,
						 	       MQHOBJ, PMQLONG, PMQLONG);

	typedef void (*PtrInquireBag)     (MQHBAG, MQLONG, MQLONG, PMQHBAG, PMQLONG, PMQLONG);
	typedef void (*PtrInquireInteger) (MQHBAG, MQLONG, MQLONG, PMQLONG, PMQLONG, PMQLONG);
	typedef void (*PtrInquireString)  (MQHBAG, MQLONG, MQLONG, MQLONG, PMQCHAR, PMQLONG,
	    							   PMQLONG, PMQLONG, PMQLONG);

	typedef void (*PtrTrim)(MQLONG, PMQCHAR, PMQCHAR, PMQLONG, PMQLONG);

	PMQCONN pMQCONN;
	PMQDISC pMQDISC;

	PMQOPEN  pMQOPEN;
	PMQSUB   pMQSUB;
	PMQCLOSE pMQCLOSE;

	PMQINQ   pMQINQ;
	PMQSET   pMQSET;

	PMQCRTMH pMQCRTMH;
	PMQINQMP pMQINQMP;
	PMQSETMP pMQSETMP;
	PMQDLTMH pMQDLTMH;

	PMQGET  pMQGET;
	PMQPUT  pMQPUT;
	PMQPUT1 pMQPUT1;

	PMQBEGIN pMQBEGIN;
	PMQCMIT  pMQCMIT;
	PMQBACK  pMQBACK;

	/* Administration API */
	PtrAddInquiry pmqAddInquiry;
	PtrAddInteger pmqAddInteger;
	PtrAddString  pmqAddString;

	PtrCountItems pmqCountItems;
	PtrCreateBag  pmqCreateBag;
	PtrDeleteBag  pmqDeleteBag;

	PtrExecute    pmqExecute;

	PtrInquireBag     pmqInquireBag;
	PtrInquireInteger pmqInquireInteger;
	PtrInquireString  pmqInquireString;

	PtrTrim pmqTrim;

	VTable(const String& strLibraryName);

	int iWaitOnExclusiveOpen;
	static const String CWaitOnExclusive;

	friend class ::IAS::Factory<VTable>;

};
/*************************************************************************/

}
}
}

#endif /* _IAS_QS_WMQ_VTable_H_ */
