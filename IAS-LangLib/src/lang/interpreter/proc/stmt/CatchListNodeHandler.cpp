/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/CatchListNodeHandler.cpp
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "CatchListNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"


#include <lang/interpreter/exe/stmt/TryCatch.h>
#include <lang/interpreter/exe/stmt/CatchList.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
CatchListNodeHandler::CatchListNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
CatchListNodeHandler::~CatchListNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CatchListNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::CatchListNode, pNode);
	const Model::Stmt::CatchListNode *pCatchListNode = IAS_DYNAMICCAST_CONST(Model::Stmt::CatchListNode, pNode);

	Model::Stmt::CatchListNode::CatchNodesList lstCatchNodes = pCatchListNode->getCatchNodesList();

	IAS_DFT_FACTORY<Exe::Stmt::CatchList>::PtrHolder ptrCatchList(
			IAS_DFT_FACTORY<Exe::Stmt::CatchList>::Create());

	for(Model::Stmt::CatchListNode::CatchNodesList::const_iterator it = lstCatchNodes.begin();
		it != lstCatchNodes.end();
		it++){

		CallbackSignature::Result aSubResult;
		CallbackRegister::SubCall(*it,pCtx,aSubResult);
		ptrCatchList->addCatch(aSubResult.pCatch);
	}

	aResult.pCatchList = ptrCatchList.pass();
}
/*************************************************************************/
}
}
}
}
}
