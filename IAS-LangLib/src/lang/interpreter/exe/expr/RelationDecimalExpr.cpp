/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationDecimalExpr.cpp
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
#include "RelationDecimalExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../exception/InterpreterRuntimeException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
/*************************************************************************/
class RelationDecimalExprDiff : public RelationDecimalExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Decimal fLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal fRight = ptrRight->evaluateDecimal(pCtx);
		return fLeft!=fRight;
	};

protected:
	RelationDecimalExprDiff(Expr* pLeft, Expr* pRight):
		RelationDecimalExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDecimalExprDiff>;

};
/*************************************************************************/
class RelationDecimalExprEq : public RelationDecimalExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Decimal fLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal fRight = ptrRight->evaluateDecimal(pCtx);
		return fLeft==fRight;
	};

protected:
	RelationDecimalExprEq(Expr* pLeft, Expr* pRight):
		RelationDecimalExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDecimalExprEq>;

};
/*************************************************************************/
class RelationDecimalExprEqGt : public RelationDecimalExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Decimal fLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal fRight = ptrRight->evaluateDecimal(pCtx);
		return fLeft>=fRight;
	};

protected:
	RelationDecimalExprEqGt(Expr* pLeft, Expr* pRight):
		RelationDecimalExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDecimalExprEqGt>;

};
/*************************************************************************/
class RelationDecimalExprEqLess : public RelationDecimalExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Decimal fLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal fRight = ptrRight->evaluateDecimal(pCtx);
		return fLeft<=fRight;
	};

protected:
	RelationDecimalExprEqLess(Expr* pLeft, Expr* pRight):
		RelationDecimalExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDecimalExprEqLess>;

};
/*************************************************************************/
class RelationDecimalExprGt : public RelationDecimalExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Decimal fLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal fRight = ptrRight->evaluateDecimal(pCtx);
		return fLeft > fRight;
	};

protected:
	RelationDecimalExprGt(Expr* pLeft, Expr* pRight):
		RelationDecimalExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDecimalExprGt>;

};
/*************************************************************************/
class RelationDecimalExprLess : public RelationDecimalExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Decimal fLeft = ptrLeft->evaluateDecimal(pCtx);
		Decimal fRight = ptrRight->evaluateDecimal(pCtx);
		return fLeft < fRight;
	};

protected:
	RelationDecimalExprLess(Expr* pLeft, Expr* pRight):
		RelationDecimalExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDecimalExprLess>;

};
/*************************************************************************/
RelationDecimalExpr::RelationDecimalExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationDecimalExpr::~RelationDecimalExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationDecimalExpr* RelationDecimalExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<RelationDecimalExpr>::PtrHolder ptrRelationDecimalExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationDecimalExpr = IAS_DFT_FACTORY<RelationDecimalExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationDecimalExpr = IAS_DFT_FACTORY< RelationDecimalExprDiff>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqGtNode)){
			ptrRelationDecimalExpr = IAS_DFT_FACTORY<RelationDecimalExprEqGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqLessNode)){
			ptrRelationDecimalExpr = IAS_DFT_FACTORY<RelationDecimalExprEqLess>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalGtNode)){
			ptrRelationDecimalExpr = IAS_DFT_FACTORY<RelationDecimalExprGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalLessNode)){
				ptrRelationDecimalExpr = IAS_DFT_FACTORY<RelationDecimalExprLess>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationDecimalExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
