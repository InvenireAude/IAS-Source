/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryLongExpr.cpp
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
#include "BinaryLongExpr.h"
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
class BinaryLongExprAdditionLong : public BinaryLongExpr {
public:
	virtual Long evaluateLong(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		return fLeft+fRight;
	};
protected:
	BinaryLongExprAdditionLong(Expr* pLeft, Expr* pRight):
		BinaryLongExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryLongExprAdditionLong>;
};
/*************************************************************************/
class BinaryLongExprSubtractionLong : public BinaryLongExpr {
public:
	virtual Long evaluateLong(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		return fLeft-fRight;
	};
protected:
	BinaryLongExprSubtractionLong(Expr* pLeft, Expr* pRight):
		BinaryLongExpr(pLeft,pRight){}

	friend class  ::IAS::Factory<BinaryLongExprSubtractionLong>;
};
/*************************************************************************/
class BinaryLongExprMultiplyLong : public BinaryLongExpr {
public:
	virtual Long evaluateLong(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		return fLeft*fRight;
	};
protected:
	BinaryLongExprMultiplyLong(Expr* pLeft, Expr* pRight):
		BinaryLongExpr(pLeft,pRight){}

	friend class ::IAS::Factory<BinaryLongExprMultiplyLong>;

};
/*************************************************************************/
class BinaryLongExprDivisionLong : public BinaryLongExpr {
public:
	virtual Long evaluateLong(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		if(fRight == 0)
			IAS_THROW(InterpreterException("Division by zero."));
		return fLeft/fRight;
	};
protected:
	BinaryLongExprDivisionLong(Expr* pLeft, Expr* pRight):
		BinaryLongExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryLongExprDivisionLong>;

};
/*************************************************************************/
class BinaryLongExprModuloLong : public BinaryLongExpr {
public:
	virtual Long evaluateLong(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		if(fRight == 0)
				IAS_THROW(InterpreterException("Division by zero."));
		return (int)fLeft%(int)fRight;
	};
protected:
	BinaryLongExprModuloLong(Expr* pLeft, Expr* pRight):
		BinaryLongExpr(pLeft,pRight){}

	friend class::IAS::Factory<BinaryLongExprModuloLong>;
};
/*************************************************************************/
BinaryLongExpr::BinaryLongExpr(Expr* pLeft, Expr* pRight):
		 BinaryExprFamily(pLeft,pRight){}
/*************************************************************************/
BinaryLongExpr::~BinaryLongExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BinaryLongExpr* BinaryLongExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryLongExpr>::PtrHolder ptrBinaryLongExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		ptrBinaryLongExpr = IAS_DFT_FACTORY<BinaryLongExprAdditionLong>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::SubtractionNode)){
		ptrBinaryLongExpr = IAS_DFT_FACTORY<BinaryLongExprSubtractionLong>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::MultiplyNode)){
			ptrBinaryLongExpr = IAS_DFT_FACTORY<BinaryLongExprMultiplyLong>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::DivisionNode)){
			ptrBinaryLongExpr = IAS_DFT_FACTORY<BinaryLongExprDivisionLong>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::ModuloNode)){
			ptrBinaryLongExpr = IAS_DFT_FACTORY<BinaryLongExprModuloLong>::Create(pLeft,pRight);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for a float argument."));
	}

	return ptrBinaryLongExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
