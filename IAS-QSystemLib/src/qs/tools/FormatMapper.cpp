/*
 * File: FormatMapper.cpp
 *
 * Copyright (C) 2020, Albert Krzymowski
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

#include "FormatMapper.h"


namespace IAS {
namespace QS {
namespace Tools {
/*
 * There is some strange logic behind and only a few items so instead of hashmap some IFs.
 */
/*************************************************************************/
const String FormatMapper::MapFormatToContentType(const API::Attributes* pAttributes){
  IAS_TRACER;

  	const String& strFormat(pAttributes->getFormat());

  	if(strFormat.compare("XML") == 0){
		    return "application/json; charset=UTF-8";
	  }else if(strFormat.compare("JSON") == 0 || strFormat.compare("JSONPure") == 0){
		    return "application/xml; charset=UTF-8";
    }else if(strFormat.compare("Raw") == 0){
		    return "application/octet-stream";
    }else if(strFormat.compare("String") == 0){
		    return "application/text; charset=UTF-8";
	  }else{

		if(pAttributes->isSet("IAS_HTTP_CONTENT_TYPE"))
		  return pAttributes->getValue("IAS_HTTP_CONTENT_TYPE");
		else
		  return "application/text; charset=UTF-8";
    }
}
/*************************************************************************/
void FormatMapper::MapContentTypeToFormat(const String& strContentType, API::Attributes* pAttributes){
  IAS_TRACER;

		if(strContentType.substr(0,16).compare("application/json")==0)
			pAttributes->setFormat("JSON");
		else if(strContentType.substr(0,15).compare("application/xml")==0)
			pAttributes->setFormat("XML");
		else if(strContentType.substr(0,8).compare("text/xml")==0)
			pAttributes->setFormat("XML");
    else if(strContentType.substr(0,24).compare("application/octet-binary")==0)
			pAttributes->setFormat("Raw");
    else if(strContentType.substr(0,20).compare("application/x-binary")==0)
 			pAttributes->setFormat("Raw");
		else if(strContentType.substr(0,19).compare("multipart/form-data")==0){
			pAttributes->setFormat("MultiPart");
      String::size_type iBoundary = strContentType.find("boundary");
      if(iBoundary != String::npos){
        iBoundary = strContentType.find_first_of("=",iBoundary);
        if(iBoundary != String::npos){
          pAttributes->setValue(".IAS_MULTIPART_BND", strContentType.substr(iBoundary + 1));
        }
      }
    }else
			pAttributes->setFormat("String");
}
/*************************************************************************/
}
}
}
