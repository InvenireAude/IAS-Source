/*
 * File: IAS-LangLib/src/lang/printer/expr/xpath/XPathVariableAccessNodeHandler.cpp
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
#include "XPathVariableAccessNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include <lang/printer/CallbackRegister.h>

namespace IAS {
namespace Lang {
namespace Printer {
namespace Expr {
namespace XPath {
/*************************************************************************/
XPathVariableAccessNodeHandler::XPathVariableAccessNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
XPathVariableAccessNodeHandler::~XPathVariableAccessNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void XPathVariableAccessNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::XPath::XPathVariableAccessNode, pNode);
	const Model::Expr::XPath::XPathVariableAccessNode *pXPathVariableAccessNode = IAS_DYNAMICCAST_CONST(Model::Expr::XPath::XPathVariableAccessNode, pNode);


}
/*************************************************************************/
}
}
}
}
}
