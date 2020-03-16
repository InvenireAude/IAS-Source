/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationLongExpr.cpp
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
#include "RelationLongExpr.h"
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
class RelationLongExprDiff : public RelationLongExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		return fLeft!=fRight;
	};

protected:
	RelationLongExprDiff(Expr* pLeft, Expr* pRight):
		RelationLongExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationLongExprDiff>;

};
/*************************************************************************/
class RelationLongExprEq : public RelationLongExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		return fLeft==fRight;
	};

protected:
	RelationLongExprEq(Expr* pLeft, Expr* pRight):
		RelationLongExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationLongExprEq>;

};
/*************************************************************************/
class RelationLongExprEqGt : public RelationLongExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		return fLeft>=fRight;
	};

protected:
	RelationLongExprEqGt(Expr* pLeft, Expr* pRight):
		RelationLongExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationLongExprEqGt>;

};
/*************************************************************************/
class RelationLongExprEqLess : public RelationLongExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		return fLeft<=fRight;
	};

protected:
	RelationLongExprEqLess(Expr* pLeft, Expr* pRight):
		RelationLongExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationLongExprEqLess>;

};
/*************************************************************************/
class RelationLongExprGt : public RelationLongExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		return fLeft > fRight;
	};

protected:
	RelationLongExprGt(Expr* pLeft, Expr* pRight):
		RelationLongExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationLongExprGt>;

};
/*************************************************************************/
class RelationLongExprLess : public RelationLongExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Long fLeft = ptrLeft->evaluateLong(pCtx);
		Long fRight = ptrRight->evaluateLong(pCtx);
		return fLeft < fRight;
	};

protected:
	RelationLongExprLess(Expr* pLeft, Expr* pRight):
		RelationLongExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationLongExprLess>;

};
/*************************************************************************/
RelationLongExpr::RelationLongExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationLongExpr::~RelationLongExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationLongExpr* RelationLongExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<RelationLongExpr>::PtrHolder ptrRelationLongExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationLongExpr = IAS_DFT_FACTORY<RelationLongExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationLongExpr = IAS_DFT_FACTORY< RelationLongExprDiff>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqGtNode)){
			ptrRelationLongExpr = IAS_DFT_FACTORY<RelationLongExprEqGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqLessNode)){
			ptrRelationLongExpr = IAS_DFT_FACTORY<RelationLongExprEqLess>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalGtNode)){
			ptrRelationLongExpr = IAS_DFT_FACTORY<RelationLongExprGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalLessNode)){
				ptrRelationLongExpr = IAS_DFT_FACTORY<RelationLongExprLess>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationLongExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
