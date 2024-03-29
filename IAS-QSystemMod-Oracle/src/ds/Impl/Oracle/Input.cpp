/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/Input.cpp
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
#include "Input.h"
#include "exception/OracleException.h"

#include <sqlite3.h>

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
Input::Input(Statement& statement):
		statement(statement),
		iNumInputs(1){
	IAS_TRACER;
}
/*************************************************************************/
Input::~Input() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Input::addInput(const String& strTag, DM::Tools::Setter *pSetter){
	IAS_TRACER;

	tabHolders.push_back(Holder::Base::Create(&statement,pSetter,false));
	tabHolders.back()->bind(iNumInputs++);

}
/*************************************************************************/
void Input::feedInputs(DM::DataObjectPtr& dm){
	IAS_TRACER;

	for(Holder::Base::Table::iterator it=tabHolders.begin();
		it != tabHolders.end(); it++){

		(*it)->feed(dm);
	}

}
/*************************************************************************/
}
}
}
}
