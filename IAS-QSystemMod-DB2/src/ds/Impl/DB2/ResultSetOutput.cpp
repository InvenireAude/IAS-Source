/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/ResultSetOutput.cpp 
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

#include "exception/DB2Exception.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

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

	SQLRETURN rc = SQLFetch((SQLHANDLE)statement);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"fetching: "<<tabHolders.size()<<" rc="<<rc);

	if(rc == SQL_NO_DATA_FOUND)
		return bHasData=false;

	DB2Exception::ThrowOnError(statement.getSQLText()+" fetch",
									rc,SQL_HANDLE_STMT, (SQLHANDLE)statement);

	return bHasData=true;
}
/*************************************************************************/
void ResultSetOutput::fetch(int iIdx, DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(!bHasData)
		IAS_THROW(DB2Exception("Fetch when no data found."));

	if(iIdx < 0 || iIdx >= tabHolders.size())
		IAS_THROW(DB2Exception("Fetch index of range."));

	tabHolders[iIdx]->fetch(dm);

}
/*************************************************************************/
void ResultSetOutput::close(){
	IAS_TRACER;

	SQLRETURN rc = SQLCloseCursor((SQLHANDLE)statement);

	DB2Exception::ThrowOnError(statement.getSQLText()+" close cursor ",
							rc,SQL_HANDLE_STMT, (SQLHANDLE)statement);

}
/*************************************************************************/
}
}
}
}
