/*
 * File: IAS-LangLib/src/lang/model/expr/RelationalEqGtNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_RelationalEqGtNode_H_
#define _IAS_AS_Lang_Model_Expr_RelationalEqGtNode_H_

#include "RelationalBinaryOperNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
class ExprNode;

/*************************************************************************/
/** The class. */
 class RelationalEqGtNode : public RelationalBinaryOperNode {
public:

	virtual ~RelationalEqGtNode() throw();

protected:
	RelationalEqGtNode(ExprNode *pLeftExprNode, ExprNode *pRightExprNode);

	friend class ::IAS::Factory<RelationalEqGtNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_RelationalEqNODE_H_ */
