/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryListExpr.cpp
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
#include "BinaryListExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include <lang/exception/ScriptUsageException.h>
#include "ExprResultSetter.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

class ExprResultSetterRight : public IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter{
	public:

		ExprResultSetterRight(const IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter& other);

	//	virtual void assign(DM::DataObject* dmValue);
		virtual void assignList(DM::DataObjectList& refList);
	};

ExprResultSetterRight::ExprResultSetterRight(
		const IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter& other) :
		IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter(other) {

    if(!other.isTargetArray())
      IAS_THROW(BadUsageException("List expected as a result target."));

    bClearList = false;
}

void ExprResultSetterRight::assignList(DM::DataObjectList& refList){

  if(iIdx > 0)
		IAS_THROW(BadUsageException(String("Cannot assign array to the other array element.") += pProperty->getName()));

	DM::DataObjectList& refTargetList=ptrDM->getList(pProperty);

  if(&refList == &refTargetList)
		IAS_THROW(BadUsageException("You cannot concatenate the list with itself, use COPYOF(...), eg. l = l + COPYOF(l)."));

	for(int iIdx=0;iIdx<refList.size();iIdx++) {
		DM::DataObject *dmValue(refList.at(iIdx));
		refTargetList.add(dmValue ? refList.at(iIdx)->duplicate() : NULL);
	}
}


/*************************************************************************/
class BinaryListExprPlusList : public BinaryListExpr {
public:

	virtual void evaluate(Context *pCtx,
						  ExprResultSetter& refResult) const{

      ExprResultSetterRight rs(refResult);

    	ptrLeft->evaluate(pCtx,refResult);
      ptrRight->evaluate(pCtx,rs);
	};

protected:
	BinaryListExprPlusList(Expr* pLeft, Expr* pRight):
		BinaryListExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryListExprPlusList>;

};

/*************************************************************************/
BinaryListExpr::BinaryListExpr(Expr* pLeft, Expr* pRight):
		 BinaryExprFamily(pLeft,pRight){}
/*************************************************************************/
BinaryListExpr::~BinaryListExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool BinaryListExpr::isArray()const{
  return true;
}
/*************************************************************************/
BinaryListExpr* BinaryListExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryListExpr>::PtrHolder ptrBinaryListExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		ptrBinaryListExpr = IAS_DFT_FACTORY<BinaryListExprPlusList>::Create(pLeft,pRight);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for a string argument."));
	}

	return ptrBinaryListExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
