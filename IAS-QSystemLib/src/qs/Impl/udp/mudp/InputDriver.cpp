/*
 * MUDP: IAS-QSystemLib/src/qs/Impl/sdf/file/InputDriver.cpp
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
#include "InputDriver.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Message.h"

namespace IAS {
namespace QS {
namespace UDP {
namespace MUDP {

/*************************************************************************/
InputDriver::InputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                         const API::Destination& destination):
  UDP::InputDriver(destination),
  receiver(dmConnection->getPort()){
	IAS_TRACER;
}
/*************************************************************************/
InputDriver::~InputDriver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Message* InputDriver::receive(int iTimeWait, API::Attributes* pSelector){
	IAS_TRACER;


  while(! SYS::Signal::GetInstance()->isStopping() ){

    PtrDataHolder data(pAllocator->allocate(64000), 64000, this);
    size_t iDataLen;
    String strSrcAddress;
    int    iSrcPort;
    receiver.receive(data, data.getDataLeft(), iDataLen, strSrcAddress, iSrcPort);
    data.setDataLeft(iDataLen);

    if(checkTopic(data)){
      IAS_DFT_FACTORY<QS::Base::Attributes>::PtrHolder ptrAttributes(buildAttributes(data));
      if(!pSelector || checkAttributes(ptrAttributes, pSelector)){
        StringStream ssTmp;
        ssTmp<<"udp://"<<strSrcAddress<<":"<<iSrcPort<<"/";//TODO extract topics ?
        ptrAttributes->setReplyTo(ssTmp.str());
        return IAS_DFT_FACTORY<Message>::Create(data, data.getDataLeft(), ptrAttributes.pass());
      }
    }
  }

  IAS_THROW(EndOfDataException("No more UDP messages expected."));
}
/*************************************************************************/
unsigned int InputDriver::skip(unsigned int iOffset){
  IAS_TRACER;
  // todo
  return 0;
}
/*************************************************************************/
}
}
}
}
