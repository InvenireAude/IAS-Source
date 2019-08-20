/*
 * File: IAS-LangLib/src/lang/model/stmt/ConditionalAssignmentNode.h
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
#ifndef _IAS_AS_Lang_Model_Stmt_ConditionalAssignmentNode_H_
#define _IAS_AS_Lang_Model_Stmt_ConditionalAssignmentNode_H_

#include <commonlib/commonlib.h>
#include "StatementNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr{
class ExprNode;

namespace XPath{
class XPathAccessNode;
}

}
namespace Stmt {

class LeftSideNode;

/*************************************************************************/
/** The class. */
 class ConditionalAssignmentNode : public StatementNode {
public:

	virtual ~ConditionalAssignmentNode() throw();

	inline LeftSideNode*   getLeftSideNode() const { return ptrLeftSideNode; };
	inline Expr::XPath::XPathAccessNode* getXPathAccessNode() const { return ptrXPathAccessNode; };

protected:
	ConditionalAssignmentNode(LeftSideNode   *pLeftSideNode,
			                  Expr::XPath::XPathAccessNode *pXPathAccessNode);

	IAS_DFT_FACTORY<LeftSideNode>::PtrHolder    ptrLeftSideNode;
	IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::PtrHolder  ptrXPathAccessNode;

	friend class ::IAS::Factory<ConditionalAssignmentNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Stmt_ASSIGNMENTNODE_H_ */
