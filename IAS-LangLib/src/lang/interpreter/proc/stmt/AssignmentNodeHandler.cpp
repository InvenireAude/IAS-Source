/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/AssignmentNodeHandler.cpp
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
#include "AssignmentNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/xpath/XPathExprFamily.h>
#include <lang/interpreter/proc/exception/ProcessorException.h>
#include <lang/interpreter/proc/ExecStore.h>
#include <lang/interpreter/exe/allexe.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
AssignmentNodeHandler::AssignmentNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
AssignmentNodeHandler::~AssignmentNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void AssignmentNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::AssignmentNode, pNode);
	const Model::Stmt::AssignmentNode *pAssignmentNode = IAS_DYNAMICCAST_CONST(Model::Stmt::AssignmentNode, pNode);

	const Model::Expr::ExprNode*     pExprNode = pAssignmentNode->getExpressionNode();
	const Model::Stmt::LeftSideNode* pLeftSideNode = pAssignmentNode->getLeftSideNode();

	CallbackSignature::Result aSubCallResult;
	CallbackRegister::SubCall(pLeftSideNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Stmt::LeftSide>::PtrHolder ptrLeftSide(aSubCallResult.pLeftSide);

	CallbackRegister::SubCall(pExprNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExpr(aSubCallResult.pExpr);

 if(!ptrLeftSide->getXPathExprFamily()->canAssign(ptrExpr->getType())){
      // IAS_LOG(true,"Cannot assign a value of type: " + ptrExpr->getType()->getFullName() +
      //    " to " + ptrLeftSide->getXPathExprFamily()->getType()->getFullName()<<" at "<<
      //    pCtx->getExecStore()->getModel()->resolve(pAssignmentNode->getSourceLocation().getSourceID())<<"["<<
      //     pAssignmentNode->getSourceLocation().getLineNumber()<<"]");

      IAS_THROW(ProcessorException("Cannot assign a value of type: " + ptrExpr->getType()->getFullName() +
       " to " + ptrLeftSide->getXPathExprFamily()->getType()->getFullName()));
   }

	IAS_DFT_FACTORY<Exe::Stmt::Assignment>::PtrHolder
		ptrAssignment(IAS_DFT_FACTORY<Exe::Stmt::Assignment>::Create(ptrLeftSide.pass(),ptrExpr.pass()));

	ptrAssignment->setSourceLine(pAssignmentNode->getSourceLocation().getLineNumber());

	aResult.pStatement=ptrAssignment.pass();
}
/*************************************************************************/
}
}
}
}
}
