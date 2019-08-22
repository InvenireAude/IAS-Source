/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryDecimalExpr.cpp
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
#include "BinaryDecimalExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../exception/InterpreterException.h"

#include <lang/exception/ScriptUsageException.h>


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
class BinaryDecimalExprPlusDecimal : public BinaryDecimalExpr {
public:
	virtual Decimal evaluateDecimal(Context *pCtx) const{
		IAS_TRACER;
		Decimal iLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal iRight = ptrRight->evaluateDecimal(pCtx);
		return iLeft+=iRight;
	};
protected:
	BinaryDecimalExprPlusDecimal(Expr* pLeft, Expr* pRight):
		BinaryDecimalExpr(pLeft,pRight){}

	friend class ::IAS::Factory<BinaryDecimalExprPlusDecimal>;

};
/*************************************************************************/
class BinaryDecimalExprMinusDecimal : public BinaryDecimalExpr {
public:
	virtual Decimal evaluateDecimal(Context *pCtx) const{
		IAS_TRACER;
		Decimal iLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal iRight = ptrRight->evaluateDecimal(pCtx);
		return iLeft-=iRight;
	};
protected:
	BinaryDecimalExprMinusDecimal(Expr* pLeft, Expr* pRight):
		BinaryDecimalExpr(pLeft,pRight){}

	friend class ::IAS::Factory<BinaryDecimalExprMinusDecimal>;

};
/*************************************************************************/
class BinaryDecimalExprMultiplyDecimal : public BinaryDecimalExpr {
public:
	virtual Decimal evaluateDecimal(Context *pCtx) const{
		IAS_TRACER;
		Decimal iLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal iRight = ptrRight->evaluateDecimal(pCtx);
		return iLeft*=iRight;
	};

protected:
	BinaryDecimalExprMultiplyDecimal(Expr* pLeft, Expr* pRight):
		BinaryDecimalExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryDecimalExprMultiplyDecimal>;
};
/*************************************************************************/
class BinaryDecimalExprDivisionDecimal : public BinaryDecimalExpr {
public:
	virtual Decimal evaluateDecimal(Context *pCtx) const{
		IAS_TRACER;
		Decimal iLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal iRight = ptrRight->evaluateDecimal(pCtx);
		if(iRight == Decimal(0))
			IAS_THROW(InterpreterException("Division by zero."));
		return iLeft/=iRight;
	};
protected:
	BinaryDecimalExprDivisionDecimal(Expr* pLeft, Expr* pRight):
		BinaryDecimalExpr(pLeft,pRight){}

	friend class ::IAS::Factory<BinaryDecimalExprDivisionDecimal>;

};
/*************************************************************************/
BinaryDecimalExpr::BinaryDecimalExpr(Expr* pLeft, Expr* pRight):
		 BinaryExprFamily(pLeft,pRight){}
/*************************************************************************/
BinaryDecimalExpr::~BinaryDecimalExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BinaryDecimalExpr* BinaryDecimalExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryDecimalExpr>::PtrHolder ptrBinaryDecimalExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		ptrBinaryDecimalExpr = IAS_DFT_FACTORY<BinaryDecimalExprPlusDecimal>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::SubtractionNode)){
		ptrBinaryDecimalExpr= IAS_DFT_FACTORY<BinaryDecimalExprMinusDecimal>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::MultiplyNode)){
			ptrBinaryDecimalExpr = IAS_DFT_FACTORY<BinaryDecimalExprMultiplyDecimal>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::DivisionNode)){
			ptrBinaryDecimalExpr = IAS_DFT_FACTORY<BinaryDecimalExprDivisionDecimal>::Create(pLeft,pRight);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for an integer argument."));
	}

	return ptrBinaryDecimalExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
