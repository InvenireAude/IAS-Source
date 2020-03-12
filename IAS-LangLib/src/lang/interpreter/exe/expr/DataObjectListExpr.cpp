/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/DataObjectListExpr.cpp
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
#include "DataObjectListExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../Context.h"
#include "ExprResultSetter.h"
namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
DataObjectListExpr::~DataObjectListExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String DataObjectListExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
int    DataObjectListExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
Float  DataObjectListExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
bool  DataObjectListExpr::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
::IAS::DateTime  DataObjectListExpr::evaluateDateTime(Context *pCtx) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
::IAS::Date  DataObjectListExpr::evaluateDate(Context *pCtx) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
::IAS::Time  DataObjectListExpr::evaluateTime(Context *pCtx) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
::IAS::Decimal  DataObjectListExpr::evaluateDecimal(Context *pCtx) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
::IAS::Long  DataObjectListExpr::evaluateLong(Context *pCtx) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
void DataObjectListExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{
	IAS_TRACER;
	IAS_THROW(InternalException("Expression allowed here (a list expression expected)."));
}
/*************************************************************************/
}
}
}
}
}
