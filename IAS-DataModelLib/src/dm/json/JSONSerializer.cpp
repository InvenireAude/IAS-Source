/*
 * File: IAS-DataModelLib/src/dm/json/JSONSerializer.cpp
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
#include "../../dm/json/JSONSerializer.h"
#include <commonlib/commonlib.h>

#include "../../dm/DataFactory.h"
#include "../../dm/DataObject.h"
#include "../../dm/DataObjectList.h"
#include "../../dm/json/exception/JSONHelperException.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/Property.h"
#include "../../dm/PropertyList.h"
#include "../../dm/Type.h"

namespace IAS {
namespace DM {
namespace JSON {

const String& JSONSerializer::CENV_NONFMT_JSON("IAS_JSON_NOFMT");
JSONSerializer::Prefixes JSONSerializer::prefixes;

/*************************************************************************/
JSONSerializer::Prefixes::Prefixes() {
  if (EnvTools::GetBooleanEnv(CENV_NONFMT_JSON)){
    this->sPrefix="";
    this->sBeginProperty="\"";
    this->sEndProperty="\":";
    this->sEndPropertyArray="\":[";
    this->sDMType="\"_dmType\":\"";
    this->sEndl="";
  }else{
    this->sPrefix="   ";
    this->sBeginProperty="\"";
    this->sEndProperty="\" : ";
    this->sEndPropertyArray="\" : [ ";
    this->sDMType="\"_dmType\" : \"";
    this->sEndl="\n";
  }
}
/*************************************************************************/
JSONSerializer::JSONSerializer(std::ostream& os):
				os(os){
	IAS_TRACER;
}
/*************************************************************************/
JSONSerializer::~JSONSerializer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void JSONSerializer::printEscaped(const String& strValue){
	IAS_TRACER;

	const char *s=strValue.c_str();

	os<<"\"";
	while(*s){

		switch(*s){
			case '\n': os<<"\\n";   break;
			case '\t': os<<"\\t";   break;
			case '"' : os<<"\\\"";  break;
			case '\\' : os<<"\\\\"; break;
			default:
				os<<*s;
		}
		s++;
	}
	os<<"\"";
}
/*************************************************************************/
void JSONSerializer::serializeElement(const DataObject* pDataObject,
									  bool  bXSIType,
								      const String& strPrefix){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataObject);

	const ::IAS::DM::Type* pType = pDataObject->getType();

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Enum:["<<pType->getTypeEnum()<<"]")

	switch(pType->getTypeEnum()){


		case ::IAS::DM::Type::AnyType:
			os<<"{"<<prefixes.sEndl<<strPrefix<<prefixes.sDMType<<pType->getURI()<<"#"<<pType->getName()<<"\"";
			os<<prefixes.sEndl<<strPrefix<<"}";
		break;

		case ::IAS::DM::Type::TextType:
		case ::IAS::DM::Type::RawType:
		case ::IAS::DM::Type::TimeType:
		case ::IAS::DM::Type::DateType:
		case ::IAS::DM::Type::DateTimeType:

			//TODO excape

			if(bXSIType){
				os<<"{"<<prefixes.sEndl<<strPrefix;
				os<<"\"_value\":";
				printEscaped(pDataObject->toString());
				os<<",";
				os<<prefixes.sEndl<<strPrefix<<prefixes.sDMType<<pType->getURI()<<"#"<<pType->getName()<<"\"";
				os<<prefixes.sEndl<<strPrefix<<"}";
			}else{
				printEscaped(pDataObject->toString());
			}
			break;

    case ::IAS::DM::Type::BooleanType:
		case ::IAS::DM::Type::IntegerType:
    case ::IAS::DM::Type::DecimalType:
		case ::IAS::DM::Type::FloatType:

			if(bXSIType){
				os<<"{"<<prefixes.sEndl<<strPrefix;
				os<<"\"_value\":";
				os<<pDataObject->toString();
				os<<",";
				os<<prefixes.sEndl<<strPrefix<<prefixes.sDMType<<pType->getURI()<<"#"<<pType->getName()<<"\"";
				os<<prefixes.sEndl<<strPrefix<<"}";
			}else{
				os<<pDataObject->toString();
			}
			break;

		case ::IAS::DM::Type::DataObjectType:
		{
			os<<"{"<<prefixes.sEndl<<strPrefix;
			const ::IAS::DM::PropertyList &lstProperties = pType->asComplexType()->getProperties();
			bool bFirst=true;
			for(int i=0; i<lstProperties.getSize(); i++){

				const Property* pProperty=lstProperties.getProperty(i);
				if(! pProperty->isMulti()){

					const DataObject *pChild = NULL;

					if(pDataObject->isSet(pProperty) && (pChild = pDataObject->getDataObject(pProperty)) != NULL) {
						if(bFirst){
							bFirst=false;
						}else{
							os<<","<<prefixes.sEndl<<strPrefix;
						}

						os<<prefixes.sBeginProperty<<pProperty->getName()<<prefixes.sEndProperty;
						const DataObject *pChild = pDataObject->getDataObject(pProperty);
						serializeElement(pChild,
										!pChild->getType()->equals(pProperty->getType()),
										strPrefix+prefixes.sPrefix);
						}/* IF: isSet */

					}else{ /* IF: isMutli */

					const DataObjectList& lstDataObject = pDataObject->getList(pProperty);
					if(lstDataObject.size()) {
						const String& strPropertyName = pProperty->getName();
						if(bFirst) {
							bFirst=false;
						} else {
							os<<","<<prefixes.sEndl<<strPrefix;
						}

						os<<prefixes.sBeginProperty<<pProperty->getName()<<prefixes.sEndPropertyArray;
            serializeList(lstDataObject,pProperty->getType(),strPrefix);
						os<<"]";
					}
				}

				}/* FOR: */

			// xsi:type
			if(bXSIType){

				os<<(bFirst?"":",")<<prefixes.sEndl<<strPrefix<<prefixes.sDMType<<pType->getURI()<<"#"<<pType->getName()<<"\"";
			}


			os<<prefixes.sEndl<<strPrefix<<"}";
			}

			break;

		default:
			IAS_THROW(InternalException("Not implemented DM Type in JSONSerializer."));
		}

}
/*************************************************************************/
void JSONSerializer::serializeList(const DataObjectList& lstDataObject, const DM::Type* pPropertyType, const String& strPrefix){
	IAS_TRACER;

	for(int j=0; j<lstDataObject.size(); j++) {
    if(j!=0)
    os<<" ,";
    const DataObject *pChild = lstDataObject.at(j);
    if(pChild)
      serializeElement(pChild,
        !pChild->getType()->equals(pPropertyType),
        strPrefix+prefixes.sPrefix);
  }

}

/*************************************************************************/
void JSONSerializer::serialize(const DataObject* pDataObject, bool  bXSIType){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pDataObject);

	serializeElement(pDataObject,bXSIType,"");
	os<<prefixes.sEndl;
}
/*************************************************************************/
void JSONSerializer::serialize(const DataObjectList& lstDataObject, bool  bXSIType){
	IAS_TRACER;

  os<<"[";
	serializeList(lstDataObject,lstDataObject.getType());
	os<<"]";
}
/*************************************************************************/
}
}
}
