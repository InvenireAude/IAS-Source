/*
 * File: IAS-DataModelLib/src/dm/json/JSONHelper.cpp
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
#include "../../dm/json/JSONHelper.h"
#include <commonlib/commonlib.h>
#include "JSONSerializer.h"
#include "../../dm/DataObject.h"
#include "../../dm/DataObjectList.h"
#include "../../dm/json/JSONLexer.h"
#include "../../dm/json/JSONParser.h"
#include "../../dm/json/JSONSerializer.h"
#include "../../dm/log/LogLevel.h"


namespace IAS {
namespace DM {
namespace JSON {

const String JSONHelper::CEnvDateTimeFormatOut("IAS_DM_TS_FMT");

struct JSONHelperDefaults {

 JSONHelperDefaults(){
    EnvTools::GetEnv(JSONHelper::CEnvDateTimeFormatOut, strDateTimeFormatOut);
 }

  String strDateTimeFormatOut;
};

static JSONHelperDefaults TheJSONHelperDefaults;
/*************************************************************************/
JSONHelper::JSONHelper(const ::IAS::DM::DataFactory *pDataFactory):
  pDataFactory(pDataFactory),
  strDateTimeFormatOut(TheJSONHelperDefaults.strDateTimeFormatOut){

	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDataFactory);
}
/*************************************************************************/
JSONHelper::~JSONHelper() throw(){
	IAS_TRACER;

}
/*************************************************************************/
DM::DataObjectPtr JSONHelper::load(std::istream& is, const DM::Type* pTypeHint){

	IAS_TRACER;

	IAS_DFT_FACTORY<JSONLexer>::PtrHolder ptrLexer(IAS_DFT_FACTORY<JSONLexer>::Create<std::istream&>(is));

	IAS_DFT_FACTORY<JSONParser>::PtrHolder ptrParser(IAS_DFT_FACTORY<JSONParser>::Create(this,ptrLexer.pass()));

	return ptrParser->parse(pTypeHint);
}

/*************************************************************************/
void JSONHelper::loadList(std::istream& is, ::IAS::DM::DataObjectList& lstDataObject){

	IAS_DFT_FACTORY<JSONLexer>::PtrHolder ptrLexer(IAS_DFT_FACTORY<JSONLexer>::Create<std::istream&>(is));
	IAS_DFT_FACTORY<JSONParser>::PtrHolder ptrParser(IAS_DFT_FACTORY<JSONParser>::Create(this,ptrLexer.pass()));

	return ptrParser->parseList(lstDataObject);

}
/*************************************************************************/
void JSONHelper::save(std::ostream& os,
		   const ::IAS::DM::DataObject *pDataObject,
		   bool  bXSIType){
	IAS_TRACER;

	IAS_DFT_FACTORY<JSONSerializer>::PtrHolder ptrSerializer(IAS_DFT_FACTORY<JSONSerializer>::Create<const JSONHelper*, std::ostream&>(this,os));

	ptrSerializer->serialize(pDataObject,bXSIType);

}

/*************************************************************************/
void JSONHelper::saveList(std::ostream& os,
			                const ::IAS::DM::DataObjectList& lstDataObject){
  IAS_TRACER;

	IAS_DFT_FACTORY<JSONSerializer>::PtrHolder ptrSerializer(IAS_DFT_FACTORY<JSONSerializer>::Create<const JSONHelper*, std::ostream&>(this,os));

	ptrSerializer->serialize(lstDataObject, false);

}
/*************************************************************************/
 void JSONHelper::setDateTimeFormatOut(const String& strDateTimeFormatOut){
   this->strDateTimeFormatOut = strDateTimeFormatOut;
 }
/*************************************************************************/
}
}
}
