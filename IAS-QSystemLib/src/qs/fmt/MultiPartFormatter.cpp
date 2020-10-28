/*
 * File: IAS-QSystemLib/src/qs/fmt/MultiPartFormatter.cpp
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
#include "MultiPartFormatter.h"
#include<qs/log/LogLevel.h>
#include "dm/json/JSONHelper.h"

#include <commonlib/commonlib.h>

#include <qs/api.h>

#include "JSONFormatter.h"
#include "JSONPureFormatter.h"
#include "XMLFormatter.h"
#include "RawFormatter.h"
#include "StringFormatter.h"

#include <qs/workers/proc/wcm/storage/Context.h>


namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
const String& MultiPartFormatter::CDefaultFormat("JSON");
const String& MultiPartFormatter::CFormatAttr(".IAS_MPF_DFT_FORMAT");
const String& MultiPartFormatter::CDataFormNameAttr(".IAS_MPF_DATA_NAME");
const String& MultiPartFormatter::CAttachmentFormNameAttr(".IAS_MPF_ATTACHMENT_NAME");
const String& MultiPartFormatter::CAttachmentFormFileAttr(".IAS_MPF_ATTACHMENT_FILE");
const String& MultiPartFormatter::CBoundaryAttr(".IAS_MULTIPART_BND");
const String& MultiPartFormatter::CDftBoundary("-----IAS--Multi-Form-Break-----");
const String& MultiPartFormatter::CHttpLineBreak("\r\n");
/*************************************************************************/
MultiPartFormatter::MultiPartFormatter(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);
	hmFormatters["XML"]=IAS_DFT_FACTORY<XMLFormatter>::Create(pDataFactory);
	hmFormatters["JSON"]=IAS_DFT_FACTORY<JSONFormatter>::Create(pDataFactory);
	hmFormatters["JSONPure"]=IAS_DFT_FACTORY<JSONPureFormatter>::Create(pDataFactory);
	hmFormatters["String"]=IAS_DFT_FACTORY<StringFormatter>::Create(pDataFactory);
	hmFormatters["Raw"]=IAS_DFT_FACTORY<RawFormatter>::Create(pDataFactory);

}
/*************************************************************************/
MultiPartFormatter::~MultiPartFormatter() throw(){
	IAS_TRACER;

	//IAS_LOG(LogLevel::INSTANCE.isInfo(),"Parsing:       "<<tsrParsing);
	//IAS_LOG(LogLevel::INSTANCE.isInfo(),"Serializing:   "<<tsrSerialization);

}
/*************************************************************************/
static inline void _extractName(const String& strBuffer, const String& strName, String& strValue){
    String::size_type iIdx1 = 0;
    //TODO use pointer

    while(isspace(strBuffer[iIdx1]))
      iIdx1++;

    String::size_type iIdx2 = iIdx1;

    while(iIdx2 < strBuffer.length() && !isspace(strBuffer[iIdx2]) && strBuffer[iIdx2] != '=')
      iIdx2++;

    if(strBuffer.compare(iIdx1, iIdx2 - iIdx1, strName) != 0 )
      IAS_THROW(BadUsageException("Cannot parse html header: exptected: ")<<strName<<", got: "
                    <<strBuffer.substr(iIdx1, iIdx2 - iIdx1)<<".");

    iIdx1 = iIdx2;

    while(iIdx1 < strBuffer.length() && strBuffer[iIdx1] != '=')
      iIdx1++;

    if(iIdx1 == strBuffer.length())
      return;

    while(iIdx1 < strBuffer.length() && strBuffer[iIdx1] != '"')
      iIdx1++;

    if(iIdx1 == strBuffer.length())
      return;

    iIdx2 = ++iIdx1;

    while(iIdx2 < strBuffer.length() && strBuffer[iIdx2] != '"')
      iIdx2++;

    if(iIdx2 == strBuffer.length())
      return;

    strValue = strBuffer.substr(iIdx1, iIdx2 - iIdx1);
}
/*************************************************************************/
static inline String _trim(const String& strValue){

  const char* s = strValue.c_str();

   IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"value:["<<strValue<<"]");

  while(*s && isspace(*s)){
    s++;
  }

  const char* p = strValue.c_str() + strValue.length() - 1;

  while(s < p && isspace(*p)){
    p--;
  }

  IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"result:["<<String(s, p - s + 1)<<"]");
  return String(s, p - s + 1);
}
/*************************************************************************/
void MultiPartFormatter::parseHeader(std::istream& is, String& strPartName, String& strPartType, String& strFileName){

  IAS_TRACER;

  String strBuffer;
  bool bFirst = true;

  while(is.good()){

		getline(is, strBuffer, '\r');

    IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Line: ["<<strBuffer<<"]");


		if(is.get() != '\n')
			IAS_THROW(BadUsageException("HTTP Response Parser Error: LF expected after CR in part header."))

    if(strBuffer.empty()){

      if(!bFirst)
        return;

      continue;
    }
    bFirst = false;
    StringList lstNameValue;
    TypeTools::Tokenize(strBuffer, lstNameValue, ':');

    if(lstNameValue.size() != 2)
    	IAS_THROW(BadUsageException("HTTP Response Parser Error: name : value pair missing: [")<<strBuffer<<"]");

    StringList::const_iterator it = lstNameValue.begin();

    const String& strName = (*it++);
    const String strValue = _trim((*it));

    IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"(name,value) = ("<<strName<<","<<strValue<<")");

    if(strName.compare("Content-Disposition")==0 || strName.compare("content-Disposition")==0){
      StringList lstValue;

      TypeTools::Tokenize(strValue, lstValue, ';');

      StringList::const_iterator it = lstValue.begin();
      it++;

      if(it == lstValue.end())
        IAS_THROW(BadUsageException("No 'name' attribute in [")<<strBuffer<<"]");

      _extractName(*it, "name", strPartName);
      it++;

      if(it != lstValue.end()){
        _extractName(*it, "filename", strFileName);
      }

    } if(strName.compare("Content-Type")==0 || strName.compare("content-Type")==0){

      if(strValue.substr(0,16).compare("application/json") == 0 ||
         strValue.substr(0,9).compare("text/json") == 0){
          strPartType = "JSON";
        }

      if(strValue.substr(0,15).compare("application/xml") == 0 ||
         strValue.substr(0,8).compare("text/xml") == 0){
          strPartType = "XML";
        }

      if(strValue.substr(0,16).compare("application/text") == 0 ||
         strValue.substr(0,4).compare("text") == 0){
          strPartType = "String";
        }

      if(strValue.substr(0,24).compare("application/octet-stream") == 0 ||
         strValue.substr(0,20).compare("application/x-binary") == 0){
          strPartType = "Raw";
        }

    } if(strName.compare("Content-Transfer-Encoding")==0 ||
         strName.compare("content-Transfer-Encoding")==0){

        if(strValue.compare("base64") == 0){
          strPartType = "Raw";
        }
    }
  }

}
/*************************************************************************/
void MultiPartFormatter::read( DM::DataObjectPtr& dmData,
  	   	   				             std::istream&       istream,
  	   	   				             QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
	ts.start();

  String strBoundary("--" +
                    (pAttributes && pAttributes->isSet(CBoundaryAttr) ?
                          pAttributes->getValue(CBoundaryAttr) : CDftBoundary));

  const String& strDataName(pAttributes && pAttributes->isSet(CDataFormNameAttr) ?
      pAttributes->getValue(CDataFormNameAttr) : "data");

  const String& strFormat(pAttributes && pAttributes->isSet(CFormatAttr) ?
      pAttributes->getValue(CFormatAttr) : CDefaultFormat);


  int iIdx = 1;

  StringStream ssPart;
  MiscTools::CopyStreamsUntilBoundary(istream,ssPart,strBoundary);

  while(istream.good()){

    StringStream ssPart;
    MiscTools::CopyStreamsUntilBoundary(istream,ssPart,strBoundary);

   IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Part: "<<ssPart.str());

    if(!istream.good())
      break;

    String strPartName;
    String strPartType;
    String strFileName;

    parseHeader(ssPart, strPartName, strPartType, strFileName);
    IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Part Header: "<<strPartName<<", file:["<<strFileName<<"], "<<strPartType);

    DM::DataObjectPtr dmValue;
    getFormatter(strPartType)->read(dmValue, ssPart, pAttributes);

    if(strPartName.compare(strDataName) == 0){
         dmData = dmValue;
       }else{
         pWorkContext->storage.setLocalValue(strPartName,dmValue);
         if(pAttributes){
            String strAttrName = CAttachmentFormNameAttr + "_" + TypeTools::IntToString(iIdx);
            pAttributes->setValue(strAttrName, strPartName);
            if(!strFileName.empty()){
              String strAttrFile = CAttachmentFormFileAttr + "_" + TypeTools::IntToString(iIdx);
              pAttributes->setValue(strAttrFile, strFileName);
            }
         }
         iIdx++;
       }

      IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"--- PART DONE ["<<iIdx<<"] :: ["<<strPartName<<"] ---");
  }

  if(dmData.isNull()){
    IAS_THROW(BadUsageException("Cannot find the main part object in mulit part, expected name=")<<strDataName);
  }

	tsrParsing.addSample(ts);
}
/*************************************************************************/
void MultiPartFormatter::write(const DM::DataObject* dmData,
		 	 	 	 	  std::ostream&       ostream,
		 	 	 	 	  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();

  const String& strBoundary(pAttributes && pAttributes->isSet(CBoundaryAttr) ?
      pAttributes->getValue(CBoundaryAttr) : CDftBoundary);

  const String& strDataName(pAttributes && pAttributes->isSet(CDataFormNameAttr) ?
      pAttributes->getValue(CDataFormNameAttr) : "data");

 const String& strFormat(pAttributes && pAttributes->isSet(CFormatAttr) ?
      pAttributes->getValue(CFormatAttr) : CDefaultFormat);

  ostream<<"--"<<strBoundary<<CHttpLineBreak;

  writeValue(strDataName, "", strBoundary, strFormat, dmData, ostream, pAttributes);

  int iIdx = 1;
  String strAttrName = CAttachmentFormNameAttr + "_" + TypeTools::IntToString(iIdx);
  String strAttrFile = CAttachmentFormFileAttr + "_" + TypeTools::IntToString(iIdx);

  while(pAttributes && pAttributes->isSet(strAttrName)){

    String strPartName = pAttributes->getValue(strAttrName);
    String strFileName;

    if(pAttributes->isSet(strAttrFile))
      strFileName = pAttributes->getValue(strAttrFile);

    DM::DataObjectPtr dmValue = pWorkContext->storage.getLocalValue(strPartName);

    writeValue(strPartName, strFileName, strBoundary, strFormat, dmValue, ostream, pAttributes);

    iIdx++;
    strAttrName = CAttachmentFormNameAttr + "_" + TypeTools::IntToString(iIdx);
    strAttrFile = CAttachmentFormFileAttr + "_" + TypeTools::IntToString(iIdx);
  }

	ostream.flush();

	tsrSerialization.addSample(ts);
}
/*************************************************************************/
void MultiPartFormatter::writeValue(const String& strName,
                                    const String& strFileName,
                                    const String& strBoundary,
                                          String  strFormat,
                                    const DM::DataObject* dmValue,
							                      std::ostream&       ostream,
						                        QS::API::Attributes *pAttributes){

 ostream<<"Content-Disposition: form-data; name=\""<<strName<<"\"";

 if(!strFileName.empty())
  ostream<<"; filename=\""<<strFileName<<"\"";

 ostream<<CHttpLineBreak;

 String strContentType;

  switch(dmValue->getType()->getTypeEnum()){

   case DM::Type::RawType:
    strContentType = "application/octet-stream";
    strFormat      = "Raw";
   break;

   case DM::Type::TextType:
    strContentType = "application/text";
    strFormat      = "String";
   break;

  default:

    if(strFormat.compare("XML") == 0){
      strContentType = "application/xml; charset=UTF-8";
    }else if(strFormat.compare("JSON") == 0 || strFormat.compare("JSONPure") == 0){
      strContentType = "application/json; charset=UTF-8";
    }else{
      IAS_THROW(BadUsageException("Cannot specify this formater in MutliPart: ")<<strFormat);
    }
  }
  ostream<<"Content-Type: "<<strContentType<<CHttpLineBreak;
  ostream<<CHttpLineBreak;
  getFormatter(strFormat)->write(dmValue, ostream, pAttributes);
  ostream<<"--"<<strBoundary<<CHttpLineBreak;
}
/*************************************************************************/
Formatter* MultiPartFormatter::getFormatter(const String& strSpecs)const{
	IAS_TRACER;

	if(hmFormatters.count(strSpecs) == 0)
		IAS_THROW(ItemNotFoundException(strSpecs+" - this formatter is not supported in mulit part messages."));

	return const_cast<FormatterMap&>(hmFormatters).at(strSpecs);
}
/*************************************************************************/
}
}
}
