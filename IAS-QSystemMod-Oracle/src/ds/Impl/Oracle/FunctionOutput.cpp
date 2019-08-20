/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/FunctionOutput.cpp
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
#include "FunctionOutput.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {

/*************************************************************************/
FunctionOutput::FunctionOutput(Statement& statement):Output(statement){
	IAS_TRACER;
}
/*************************************************************************/
FunctionOutput::~FunctionOutput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void FunctionOutput::addOutput(const String& strTag, DM::Tools::Setter *pSetter){
	IAS_TRACER;

    tabOutputHolders.push_back(Holder::Base::Create(&statement,pSetter,false));
	  tabOutputHolders.back()->define(tabOutputHolders.size() + tabInputOutputHolders.size());

}
/*************************************************************************/
}
}
}
}
