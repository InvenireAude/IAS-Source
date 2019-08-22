/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/DecimalExpr.cpp
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
#include "DecimalExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
DecimalExpr::DecimalExpr() throw(){
	IAS_TRACER;
}

/*************************************************************************/
DecimalExpr::~DecimalExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String DecimalExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;
	return evaluateDecimal(pCtx).toString();
}
/*************************************************************************/
int DecimalExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;
	return (long)evaluateDecimal(pCtx);
}
/*************************************************************************/
Float DecimalExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	return (Float)evaluateDecimal(pCtx);
}
/*************************************************************************/
bool  DecimalExpr::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	return (long)evaluateDecimal(pCtx) != 0;
}
/*************************************************************************/
::IAS::DateTime DecimalExpr::evaluateDateTime(Context *pCtx) const{
	IAS_TRACER;
	time_t tmpValue=(long)evaluateDecimal(pCtx);
	DateTime tsValue;
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
::IAS::Date DecimalExpr::evaluateDate(Context *pCtx) const{
	IAS_TRACER;
	time_t tmpValue=(long)evaluateDecimal(pCtx);
	Date tsValue;
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
::IAS::Time DecimalExpr::evaluateTime(Context *pCtx) const{
	IAS_TRACER;
	time_t tmpValue=(long)evaluateDecimal(pCtx);
	Time tsValue;
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
void DecimalExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{

	const DM::DataFactory *pDataFactory=pCtx->getDataFactory();

	refResult = getType()->createDataObject(evaluateString(pCtx));

}
/*************************************************************************/
}
}
}
}
}
