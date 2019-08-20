/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/FunCallValue.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Expr_FunCallValue_H_
#define _IAS_Lang_Interpreter_Exe_Expr_FunCallValue_H_

#include "DataObjectExpr.h"
#include "FunCall.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Program;
namespace Expr {
class ExprList;
/*************************************************************************/
/** The FunCallValue class.
 *
 */
class FunCallValue :
	public virtual FunCall,
	public virtual DataObjectExpr {
public:

	virtual ~FunCallValue() throw();

	virtual void evaluate(IAS::Lang::Interpreter::Exe::Context* pCtx, IAS::DM::DataObjectPtr& refOutput)const;

protected:
	FunCallValue(Program* pProgram, ExprList* pExprList);
	friend class ::IAS::Factory<FunCallValue>;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Expr_FunCallValue_H_ */
