/*
 * File: IAS-LangLib/src/lang/model/expr/NegativeNode.h
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
#ifndef _IAS_Lang_Model_Expr_NegativeNode_H_
#define _IAS_Lang_Model_Expr_NegativeNode_H_

#include "UnaryOperNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {

/*************************************************************************/
/** The NegativeNode class.
 *
 */
class NegativeNode : public UnaryOperNode {
public:

	virtual ~NegativeNode() throw();

protected:
	NegativeNode(ExprNode* pExprNode);

	friend class ::IAS::Factory<NegativeNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Model_Expr_NegativeNode_H_ */
