/*
 * File: IAS-LangLib/src/lang/model/expr/GetTypeNSNode.cpp
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
#include "GetTypeNSNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {

/*************************************************************************/
GetTypeNSNode::GetTypeNSNode(ExprNode* pExprNode):
	UnaryOperNode(pExprNode){
	IAS_TRACER;
}
/*************************************************************************/
GetTypeNSNode::~GetTypeNSNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
