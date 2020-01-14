/*
 * Copyright (C) 2017, Albert Krzymowski
 * Copyright (C) 2017, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/RawBLOB.cpp
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
#include "RawBLOB.h"

#include <qs/fmt/FmtFactory.h>
#include "../Session.h"
#include "../tools/LobOpener.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
RawBLOB::RawBLOB(Statement* pStatement,
		 DM::Tools::Setter* pSetter,
		 bool bOptional):
		Base(pStatement, pSetter, bOptional, CBufferLen, SQLT_BLOB){
	IAS_TRACER;


	*bufData.getBuffer<OCILobLocator*>() = 0;

	sword rc =  OCIDescriptorAlloc(pStatement->getSession()->getEnvHandle(),
								   bufData.getBuffer<void*>(),
	                               (ub4)OCI_DTYPE_LOB,
								   (size_t)0,
							       (dvoid **)0);

	OracleException::ThrowOnError(pStatement->getSQLText()+", BLOB allocation.",
				pStatement->getSession()->getErrorHandle(),
				rc);

}
/*************************************************************************/
RawBLOB::~RawBLOB() throw(){
	IAS_TRACER;
	if(bufData.getBuffer<OCILobLocator*>() != 0)
		OCIDescriptorFree( bufData.getBuffer<void*>(), (ub4) OCI_DTYPE_LOB);
}

/*************************************************************************/
void RawBLOB::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());

	if(bNull == -1) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{

		 Tools::LobOpener BLOBOpener(pStatement->getSession(), *bufData.getBuffer<OCILobLocator*>(), OCI_LOB_READONLY);

		 sword rc = OCI_NEED_DATA;

		 Buffer          bufBLOBData(32000);
     DM::RawContent  bufResult(32000);

     size_t       iDataLen = 0;

		 while(rc == OCI_NEED_DATA){

			 ub4 iBLOBDataLen = 0;

			 rc = OCILobRead(pStatement->getSession()->getSvcCtxHandle(),
                 	 	 	 pStatement->getSession()->getErrorHandle(),
							 BLOBOpener,
							 &iBLOBDataLen,
							 1,
							 bufBLOBData.getBuffer<void>(),
							 (ub4)bufBLOBData.getSize(),
							 NULL,
							 NULL,
							 0,
							 SQLCS_IMPLICIT);


				if(rc != OCI_NEED_DATA)
						OracleException::ThrowOnError(pStatement->getSQLText()+", error when reading the BLOB.",
						 				pStatement->getSession()->getErrorHandle(),
						 				rc);

				IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value="<<String((char*)bufBLOBData,iBLOBDataLen));
				IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"len="<<iBLOBDataLen);

        if(iBLOBDataLen > 0){

          if(bufResult.getSize() < iDataLen + iBLOBDataLen ){
            bufResult.resize(iDataLen + iBLOBDataLen + 32000);
          }
          memcpy(bufResult.getBuffer<char>() + iDataLen, bufBLOBData.getBuffer<char>(), iBLOBDataLen);
          iDataLen += iBLOBDataLen;
        }

        bufResult.resize(iDataLen);

		 }


		pSetter->setRaw(dm,&bufResult);


	}

}
/*************************************************************************/
void RawBLOB::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());


	if(pSetter->isNotNull(dm)){

    DM::RawContent  bufResult;
		pSetter->getValue(dm)->toRaw(&bufResult);

		sword rc = OCILobCreateTemporary(pStatement->getSession()->getSvcCtxHandle(),
    	 	 	   pStatement->getSession()->getErrorHandle(), *bufData.getBuffer<OCILobLocator*>(),
				   (ub2)0,
				        SQLCS_IMPLICIT,
                OCI_TEMP_BLOB,
				        OCI_ATTR_NOCACHE,
                OCI_DURATION_SESSION);

		OracleException::ThrowOnError(pStatement->getSQLText()+", error when writing to the BLOB.",
						 				pStatement->getSession()->getErrorHandle(),
						 				rc);

		ub4    iBLOBDataLen = bufResult.getSize();

		Tools::LobOpener BLOBOpener(pStatement->getSession(), *bufData.getBuffer<OCILobLocator*>(), OCI_LOB_READWRITE);

		rc = OCILobWrite(pStatement->getSession()->getSvcCtxHandle(),
		           	 	 	   pStatement->getSession()->getErrorHandle(),
							   *bufData.getBuffer<OCILobLocator*>(),
							   &iBLOBDataLen,
							   1,
							   (void*)bufResult.getBuffer<char>(),
							   iBLOBDataLen,
							   OCI_ONE_PIECE,
							   NULL,
							   NULL,
							   0,
							   SQLCS_IMPLICIT);



				OracleException::ThrowOnError(pStatement->getSQLText()+", error when writing to the BLOB.",
						 				pStatement->getSession()->getErrorHandle(),
						 				rc);


		bNull=0;

    IAS_LOG(LogLevel::INSTANCE.isData(),"value: BLOB, "<<iBLOBDataLen<<" bytes.");

	}else{
		IAS_LOG(LogLevel::INSTANCE.isData(),"is NULL");
		bNull=-1;
	}

}
/*************************************************************************/
}
}
}
}
}
