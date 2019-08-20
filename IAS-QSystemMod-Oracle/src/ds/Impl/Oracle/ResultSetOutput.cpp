/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/ResultSetOutput.cpp 
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
#include "ResultSetOutput.h"

#include "exception/OracleException.h"

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
ResultSetOutput::ResultSetOutput(Statement& statement):
		statement(statement),
		bHasData(false){
	IAS_TRACER;
}
/*************************************************************************/
ResultSetOutput::~ResultSetOutput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ResultSetOutput::addResultSetOutput(DM::Tools::Setter* pSetter, bool bOptional){

	IAS_TRACER;

	tabHolders.push_back(Holder::Base::Create(&statement,pSetter,bOptional));
	tabHolders.back()->define(tabHolders.size());
}
/*************************************************************************/
void ResultSetOutput::bindResultSetOutputs(){
	IAS_TRACER;
}
/*************************************************************************/
bool ResultSetOutput::next(){
	IAS_TRACER;

	//TODO - paging via scrolable cursors.

	sword rc =	OCIStmtFetch2((OCIStmt*)statement,
			 	 	 	 	  statement.getSession()->getErrorHandle(),
							  1,
							  OCI_FETCH_NEXT,
							  0,
							  OCI_DEFAULT);

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"fetching: "<<tabHolders.size()<<" rc="<<rc);

	if(rc == OCI_NO_DATA)
		return bHasData=false;

	if(rc != OCI_SUCCESS)
		OracleException::ThrowOnError(statement.getSQLText()+" fetch",
									statement.getSession()->getErrorHandle(),
				 	 	 rc);

	return bHasData=true;
}
/*************************************************************************/
void ResultSetOutput::fetch(int iIdx, DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(!bHasData)
		IAS_THROW(OracleException("Fetch when no data found."));

	if(iIdx < 0 || iIdx >= tabHolders.size())
		IAS_THROW(OracleException("Fetch index of range."));

	tabHolders[iIdx]->fetch(dm);

}
/*************************************************************************/
void ResultSetOutput::close(){
	IAS_TRACER;

	sword rc =	OCIStmtFetch2((OCIStmt*)statement,
				 	 	 	  statement.getSession()->getErrorHandle(),
							  0,
							  OCI_FETCH_NEXT,
							  0,
							  OCI_DEFAULT);

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"closing ");

	if(rc != OCI_SUCCESS)
		OracleException::ThrowOnError(statement.getSQLText()+" close cursor" ,
									statement.getSession()->getErrorHandle(),
				 	 	 rc);

}
/*************************************************************************/
}
}
}
}
