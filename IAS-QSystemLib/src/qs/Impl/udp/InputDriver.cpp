/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Driver.cpp
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
#include "InputDriver.h"
#include<qs/log/LogLevel.h>
#include "Message.h"
#include "../base/Attributes.h"

namespace IAS {
namespace QS {
namespace UDP {

/*************************************************************************/
InputDriver::InputDriver(const API::Destination& destination):
  DriverBase(destination){};
/*************************************************************************/
bool InputDriver::checkTopic(PtrDataHolder& data) const{
  IAS_TRACER;

   if(strTopic.empty())
    return true;

   const int iMaxLen = data.getDataLeft() < 4096 ? data.getDataLeft() : 4096;
   int iTopicStringLen = strnlen(data, iMaxLen);

  if(iTopicStringLen == iMaxLen)
    return false;

   String strMsgTopic(data, iTopicStringLen);
   data += iTopicStringLen + 1;

   IAS_LOG(LogLevel::INSTANCE.isInfo(), "Match:["<<strMsgTopic<<"] ? ["<<strTopic<<"]");

   return strTopic.compare("*") == 0 ||
          strTopic.compare(strMsgTopic) == 0 ||
          strMsgTopic.compare("*") == 0;

}
/*************************************************************************/
QS::Base::Attributes *InputDriver::buildAttributes(PtrDataHolder& data) const{
  IAS_TRACER;

  IAS_DFT_FACTORY<QS::Base::Attributes>::PtrHolder ptrAttributes(
    IAS_DFT_FACTORY<QS::Base::Attributes>::Create());

  if(!strTopic.empty()){

    const int iMaxLen = data.getDataLeft() < 4096 ? data.getDataLeft() : 4096;
    int iAttrStringLen = strnlen(data, iMaxLen);

    if(iAttrStringLen != iMaxLen){
      StringStream ssTmp(String(data, iAttrStringLen));
      ptrAttributes->read(ssTmp);
      data += iAttrStringLen + 1;
    }

  }

  return ptrAttributes.pass();
}
/*************************************************************************/
bool InputDriver::checkAttributes(const API::Attributes *pAttributes,
                                  API::Attributes *pSelector){
  IAS_TRACER;


  for(API::Attributes::ValuesMap::const_iterator it = pSelector->begin();
      it != pSelector->end(); it++){
        const String& strName(it->first);
        const String& strValue(it->second);

        if(!pAttributes->isSet(strName) ||
            pAttributes->getValue(strName).compare(strValue) != 0)
            return false;
    }

  return true;
}
/*************************************************************************/
}
}
}

