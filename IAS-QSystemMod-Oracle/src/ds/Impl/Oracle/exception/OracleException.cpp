/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/exception/OracleException.cpp 
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
#include "OracleException.h"
#include <ds/api/exception/ConstraintViolationException.h>

#include <commonlib/commonlib.h>
#include <sqlite3.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace Oracle{

/*************************************************************************/
OracleException::OracleException(){
	IAS_TRACER;		
}
/*************************************************************************/
OracleException::OracleException(const String& strInfo){
	IAS_TRACER;
	this->setInfo(strInfo);
}
/*************************************************************************/
OracleException::OracleException(const String& strInfo, int rc){
	IAS_TRACER;
	//this->setInfo(strInfo+", Error: ("+TypeTools::IntToString(rc)+") "+GetErrorString(rc));
}
/*************************************************************************/
OracleException::~OracleException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* OracleException::getName(){
	IAS_TRACER;
	return "OracleException";
}
/*************************************************************************/
class ConstraintViolationException :
		public virtual OracleException,
		public virtual ::IAS::DS::API::ConstraintViolationException{
public:
	ConstraintViolationException(const String& strInfo):
		OracleException(strInfo){};

	/*************************************************************************/
	const char* getName(){
		IAS_TRACER;
		return "ConstraintViolationException";
	}
};
/*************************************************************************/
/*************************************************************************/
void OracleException::ThrowOnError(const String& strInfo, OCIError *errhp, sword status){
	IAS_TRACER;

	switch(status){

		case OCI_SUCCESS:
			return;

		case OCI_SUCCESS_WITH_INFO:
		{
			text errbuf[4096];
			errbuf[0]=0;
			sb4 errcode = 0;
		    if(errhp)
		    	(void) OCIErrorGet((dvoid *)errhp, (ub4) 1, (text *) NULL, &errcode,
			                        errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);

		    IAS_LOG(LogLevel::INSTANCE.isError(),"Info: "<<errbuf);
		}
			return;

		case OCI_STILL_EXECUTING:
			IAS_THROW(OracleException("OCI_STILL_EXECUTING"));
			return;

		case OCI_NO_DATA:
			IAS_THROW(OracleException("OCI_NO_DATA"));
			return;

		case OCI_NEED_DATA:
			IAS_THROW(OracleException("OCI_NEED_DATA"));
			return;

		case OCI_ERROR:
			{
				text errbuf[4096];
				errbuf[0]=0;
				sb4 errcode = 0;
			    if(errhp)
			    	(void) OCIErrorGet((dvoid *)errhp, (ub4) 1, (text *) NULL, &errcode,
				                        errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);
			    String strMsg((const char*)errbuf);
			    strMsg+=strInfo;

				IAS_LOG(LogLevel::INSTANCE.isError() && errcode != 1,"Execute:["<<strInfo<<"]:"<<strMsg<<", errcode="<<errcode);

				if(errcode == 1)
					IAS_THROW(ConstraintViolationException(strMsg));

				IAS_THROW(OracleException(strMsg));
			}
			break;

		case OCI_INVALID_HANDLE:
			//IAS::LogLevel::INSTANCE.bIsTrace=true;

			IAS_THROW(OracleException("OCI_INVALID_HANDLE"));
		return;
	}

	IAS_THROW(OracleException("Unknow error."));
}
/*************************************************************************/
}
}
}
} /* namespace IAS */
