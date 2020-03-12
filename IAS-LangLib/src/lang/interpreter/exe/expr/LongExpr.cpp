/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/LongExpr.cpp
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
#include "LongExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
LongExpr::LongExpr() throw(){
	IAS_TRACER;
}

/*************************************************************************/
LongExpr::~LongExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String LongExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;
	return TypeTools::LongToString(evaluateLong(pCtx));
}
/*************************************************************************/
int LongExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;
	return evaluateLong(pCtx);
}
/*************************************************************************/
Float LongExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	return (Float)evaluateLong(pCtx);
}
/*************************************************************************/
bool  LongExpr::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	return evaluateLong(pCtx);
}
/*************************************************************************/
::IAS::DateTime LongExpr::evaluateDateTime(Context *pCtx) const{
	IAS_TRACER;
	time_t tmpValue=evaluateInt(pCtx);
	DateTime tsValue;
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
::IAS::Date LongExpr::evaluateDate(Context *pCtx) const{
	IAS_TRACER;
	time_t tmpValue=evaluateInt(pCtx);
	Date tsValue;
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
::IAS::Time LongExpr::evaluateTime(Context *pCtx) const{
	IAS_TRACER;
	time_t tmpValue=evaluateInt(pCtx);
	Time tsValue;
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
Decimal LongExpr::evaluateDecimal(Context *pCtx) const{
	IAS_TRACER;
	return evaluateLong(pCtx);
}
/*************************************************************************/
void LongExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{

	const DM::DataFactory *pDataFactory=pCtx->getDataFactory();

	refResult = getType()->createDataObject(evaluateString(pCtx));

}
/*************************************************************************/
}
}
}
}
}
