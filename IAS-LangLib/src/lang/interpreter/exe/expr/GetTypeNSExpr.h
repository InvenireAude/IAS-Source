/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/GetTypeNSExpr.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Expr_GetTypeNSExpr_H_
#define _IAS_Lang_Interpreter_Exe_Expr_GetTypeNSExpr_H_

#include "StringExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
/** The GetTypeNSExpr class.
 *
 */
class GetTypeNSExpr : public virtual StringExpr{
public:

	virtual ~GetTypeNSExpr() throw();

	virtual String evaluateString(Context *pCtx) const;

protected:
	GetTypeNSExpr(const DM::DataFactory* pDataFactory, Expr* pExpr);

	IAS_DFT_FACTORY<Expr>::PtrHolder ptrExpr;
	friend class ::IAS::Factory<GetTypeNSExpr>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Expr_GetTypeNSExpr_H_ */
