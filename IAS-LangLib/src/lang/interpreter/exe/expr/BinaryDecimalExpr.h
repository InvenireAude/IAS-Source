/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryDecimalExpr.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_BINARYDecimalExpr_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_BINARYDecimalExpr_H_

#include "BinaryExprFamily.h"
#include "DecimalExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
/** The class. */
 class BinaryDecimalExpr :
	public DecimalExpr,
	public BinaryExprFamily{
public:

	virtual ~BinaryDecimalExpr() throw();

	static BinaryDecimalExpr* Create(Expr* pLeft,
									 Expr* pRight,
									 TypeInfoProxy aTypeInfoProxy);

protected:
	BinaryDecimalExpr(Expr* pLeft, Expr* pRight);
	friend class ::IAS::Factory<BinaryDecimalExpr>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_BINARYSTRINGExpr_H_ */
