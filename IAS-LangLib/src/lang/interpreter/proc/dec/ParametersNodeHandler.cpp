/*
 * File: IAS-LangLib/src/lang/interpreter/proc/dec/ParametersNodeHandler.cpp
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
#include "ParametersNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"

#include <lang/interpreter/exe/allexe.h>
#include "../exception/ProcessorLinkedException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Proc {
namespace Dec {

/*************************************************************************/
ParametersNodeHandler::ParametersNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
ParametersNodeHandler::~ParametersNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ParametersNodeHandler::call(const Model::Node* pNode,
									  CallbackCtx *pCtx,
									  CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Dec::ParametersNode, pNode);
	const Model::Dec::ParametersNode *pParametersNode = IAS_DYNAMICCAST_CONST(Model::Dec::ParametersNode, pNode);

	const DM::DataFactory *pDataFactory = pCtx->getDataFactory();

	IAS_DFT_FACTORY< Exe::Dec::Parameters >::PtrHolder ptrParameters(IAS_DFT_FACTORY<Exe::Dec::Parameters>::Create());

	Model::Stmt::StatementsListNode::DeclarationNodesList::const_iterator itDeclarations=
			pParametersNode->getDeclarationsList().begin();

	while(itDeclarations != pParametersNode->getDeclarationsList().end())
  try {
		const Model::Dec::DeclarationNode *pDeclarationNode = *itDeclarations;

		CallbackSignature::Result aSubCallResult;
		IAS_CHECK_IF_VALID(pDeclarationNode);
		CallbackRegister::SubCall(pDeclarationNode, pCtx, aSubCallResult);

		ptrParameters->addVariable(aSubCallResult.pVariableDeclaration);

		itDeclarations++;
	}	catch(ProcessorLinkedException& e){
			throw e;
	}catch(Exception& e){
      IAS_LOG(LogLevel::INSTANCE.isInfo(),(*itDeclarations)->getVariable());
			IAS_THROW(ProcessorLinkedException(e,(*itDeclarations)->getSourceLocation(),*itDeclarations));
	}

	ptrParameters->declareBlockVariables(pCtx->getDataFactory());

	aResult.pParameters = ptrParameters.pass();

}
/*************************************************************************/
}
}
}
}
}
