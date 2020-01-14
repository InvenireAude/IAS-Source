/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationRawExpr.cpp
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

#include "RelationRawExpr.h"
#include <lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../exception/InterpreterRuntimeException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
/*************************************************************************/
class RelationRawExprDiff : public RelationRawExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
    DM::DataObjectPtr dmLeft;
    DM::DataObjectPtr dmRight;
		ptrLeft->evaluate(pCtx,dmLeft);
    ptrRight->evaluate(pCtx,dmRight);

    IAS::DM::RawContent rawLeft;
    IAS::DM::RawContent rawRight;
    dmLeft->toRaw(&rawLeft);
    dmRight->toRaw(&rawRight);

    return rawLeft.getSize() != rawRight.getSize() ||
       memcmp(rawLeft.getBuffer<char>(), rawRight.getBuffer<char>(), rawLeft.getSize()) != 0;

	};

protected:
	RelationRawExprDiff(Expr* pLeft, Expr* pRight):
		RelationRawExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationRawExprDiff>;

};
/*************************************************************************/
class RelationRawExprEq : public RelationRawExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;

	  DM::DataObjectPtr dmLeft;
    DM::DataObjectPtr dmRight;
		ptrLeft->evaluate(pCtx,dmLeft);
    ptrRight->evaluate(pCtx,dmRight);

    IAS::DM::RawContent rawLeft;
    IAS::DM::RawContent rawRight;
    dmLeft->toRaw(&rawLeft);
    dmRight->toRaw(&rawRight);

    return rawLeft.getSize() == rawRight.getSize() &&
       memcmp(rawLeft.getBuffer<char>(), rawRight.getBuffer<char>(), rawLeft.getSize()) == 0;

	};

protected:
	RelationRawExprEq(Expr* pLeft, Expr* pRight):
		RelationRawExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationRawExprEq>;

};
/*************************************************************************/
RelationRawExpr::RelationRawExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationRawExpr::~RelationRawExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationRawExpr* RelationRawExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){

	IAS_TRACER;

	IAS_DFT_FACTORY<RelationRawExpr>::PtrHolder ptrRelationRawExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationRawExpr = IAS_DFT_FACTORY<RelationRawExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationRawExpr = IAS_DFT_FACTORY< RelationRawExprDiff>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationRawExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
