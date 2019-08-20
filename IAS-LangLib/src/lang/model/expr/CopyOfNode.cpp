/*
 * File: IAS-LangLib/src/lang/model/expr/CopyOfNode.cpp
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
#include "CopyOfNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "xpath/XPathAccessNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {

/*************************************************************************/
CopyOfNode::CopyOfNode(Expr::XPath::XPathAccessNode  *pXPathAccessNode){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pXPathAccessNode);

	this->ptrXPathAccessNode=pXPathAccessNode;
}
/*************************************************************************/
CopyOfNode::~CopyOfNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
