/*
 * Copyright (C) 2017, Albert Krzymowski
 * Copyright (C) 2017, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/DataObjectLOB.cpp 
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
#include "DataObjectLOB.h"

#include <qs/fmt/FmtFactory.h>
#include "../Session.h"
#include "../tools/LobOpener.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
DataObjectLOB::DataObjectLOB(Statement* pStatement,
		 DM::Tools::Setter* pSetter,
		 bool bOptional,
		 ub2    iOCIType):
		Base(pStatement, pSetter, bOptional, CBufferLen, iOCIType){
	IAS_TRACER;


	*bufData.getBuffer<OCILobLocator*>() = 0;

	sword rc =  OCIDescriptorAlloc(pStatement->getSession()->getEnvHandle(),
								   bufData.getBuffer<void*>(),
	                               (ub4)OCI_DTYPE_LOB,
								   (size_t)0,
							       (dvoid **)0);

	OracleException::ThrowOnError(pStatement->getSQLText()+", clob allocation.",
				pStatement->getSession()->getErrorHandle(),
				rc);

}
/*************************************************************************/
DataObjectLOB::~DataObjectLOB() throw(){
	IAS_TRACER;
	if(bufData.getBuffer<OCILobLocator*>() != 0)
		OCIDescriptorFree( bufData.getBuffer<void*>(), (ub4) OCI_DTYPE_LOB);
}

/*************************************************************************/
void DataObjectLOB::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(bNull == -1) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{

		 Tools::LobOpener clobOpener(pStatement->getSession(), *bufData.getBuffer<OCILobLocator*>(), OCI_LOB_READONLY);

		 sword rc = OCI_NEED_DATA;

		 Buffer       bufCLobData(32000);
		 StringStream ssValue;

		 while(rc == OCI_NEED_DATA){

			 ub4 iCLobDataLen = 0;

			 rc = OCILobRead(pStatement->getSession()->getSvcCtxHandle(),
                 	 	 	 pStatement->getSession()->getErrorHandle(),
							 clobOpener,
							 &iCLobDataLen,
							 1,
							 bufCLobData.getBuffer<void>(),
							 (ub4)bufCLobData.getSize(),
							 NULL,
							 NULL,
							 0,
							 SQLCS_IMPLICIT);


				if(rc != OCI_NEED_DATA)
						OracleException::ThrowOnError(pStatement->getSQLText()+", error when reading the clob.",
						 				pStatement->getSession()->getErrorHandle(),
						 				rc);

				IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value="<<String((char*)bufCLobData,iCLobDataLen));
				IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"len="<<iCLobDataLen);

				if(iCLobDataLen)
					ssValue.write((char*)bufCLobData,iCLobDataLen);


		 }


		DM::DataObjectPtr dmValue;
		QS::Fmt::Formatter *pFormatter=pStatement->getSession()->getFormatter();

		pFormatter->read(dmValue,ssValue);
		pSetter->setDataObject(dm,dmValue);


	}

}
/*************************************************************************/
void DataObjectLOB::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(pSetter->isNotNull(dm)){

		DM::DataObjectPtr dmValue;
		QS::Fmt::Formatter *pFormatter=pStatement->getSession()->getFormatter();

		StringStream ssValue;
		pFormatter->write(pSetter->getValue(dm),ssValue);

		sword rc = OCILobCreateTemporary(pStatement->getSession()->getSvcCtxHandle(),
    	 	 	   pStatement->getSession()->getErrorHandle(), *bufData.getBuffer<OCILobLocator*>(),
				   (ub2)0,
				   SQLCS_IMPLICIT,
                   OCI_TEMP_BLOB,
				   OCI_ATTR_NOCACHE,
                   OCI_DURATION_SESSION);

		OracleException::ThrowOnError(pStatement->getSQLText()+", error when writing to the clob.",
						 				pStatement->getSession()->getErrorHandle(),
						 				rc);

		String strData(ssValue.str());
		ub4    iCLobDataLen = strData.length();

		Tools::LobOpener clobOpener(pStatement->getSession(), *bufData.getBuffer<OCILobLocator*>(), OCI_LOB_READWRITE);

		rc = OCILobWrite(pStatement->getSession()->getSvcCtxHandle(),
		           	 	 	   pStatement->getSession()->getErrorHandle(),
							   *bufData.getBuffer<OCILobLocator*>(),
							   &iCLobDataLen,
							   1,
							   (void*)strData.c_str(),
							   iCLobDataLen,
							   OCI_ONE_PIECE,
							   NULL,
							   NULL,
							   0,
							   SQLCS_IMPLICIT);



				OracleException::ThrowOnError(pStatement->getSQLText()+", error when writing to the clob.",
						 				pStatement->getSession()->getErrorHandle(),
						 				rc);


		bNull=0;

	}else{
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"is NULL");
		bNull=-1;
	}

}
/*************************************************************************/
}
}
}
}
}
