/*
 * File: IAS-QSystemMod-FCGI/src/qs/Impl/fcgi/Message.cpp
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
#include "Message.h"
#include <qs/log/LogLevel.h>
#include "ContentManager.h"
#include <qs/Impl/base/Attributes.h>

#include <commonlib/commonlib.h>
#include <qs/Impl/shm/shared/MsgEntry.h>

#include <commonlib/net/http/Response.h>

#include <qs/tools/FormatMapper.h>

namespace IAS {
namespace QS {
namespace FCGI {
using namespace IAS::QS::Tools;

/*************************************************************************/
Message::Message(){
	IAS_TRACER;
	ptrContent=IAS_DFT_FACTORY<Content>::Create();
	ptrAttributes=IAS_DFT_FACTORY<QS::Base::Attributes>::Create();
}
/*************************************************************************/
Message::Message(FCGX_Stream* pFCGXStream){
	IAS_TRACER;
	ptrContent=IAS_DFT_FACTORY<Content>::Create();
	ptrAttributes=IAS_DFT_FACTORY<QS::Base::Attributes>::Create();

	const std::size_t iBufSize = 4096;
	std::size_t iDataLen = 0;
	char sBuffer[iBufSize];

	while((iDataLen=FCGX_GetStr(sBuffer,iBufSize-1,pFCGXStream)) > 0){
		sBuffer[iDataLen]=0;
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isData(),"DataChunk:["<<sBuffer<<"]");
		(*ptrContent)<<sBuffer;
	}
	ptrContent->flush();
}
/*************************************************************************/
Message::Message(const String& strText){
	IAS_TRACER;
	(*ptrContent)<<strText;
}
/*************************************************************************/
void Message::write(FCGX_Stream* pFCGXStream){
	IAS_TRACER;

	const std::size_t iBufSize = 4096;
	char sBuffer[iBufSize];

	int iNumBytes=0;

	const String& strSetHttpStatus = "IAS_HTTP_STATUS";

  if(ptrAttributes->isSet(strSetHttpStatus)){

    String strStatus(ptrAttributes->getValue(strSetHttpStatus));

    IAS::Net::HTTP::Response::Status    iStatus = static_cast<IAS::Net::HTTP::Response::Status>(TypeTools::StringToInt(strStatus));

  	FCGX_FPrintF(pFCGXStream, "Status: %d %s \r\n",
                    iStatus,
                    IAS::Net::HTTP::Response::StatusToString(iStatus).c_str());
  }

	const String& strSetCookieAttr = "IAS_HTTP_SET_COOKIE";

	if(ptrAttributes->isSet(strSetCookieAttr)){

		String     strSpecification(ptrAttributes->getValue(strSetCookieAttr));
		StringList lstSettings;

		TypeTools::Tokenize(strSpecification, lstSettings, '\n');

		for(StringList::const_iterator it = lstSettings.begin(); it != lstSettings.end(); it++)
			FCGX_FPrintF(pFCGXStream, "Set-Cookie: %s\r\n", (*it).c_str());

	}

	const String& strRedirectAttr = "IAS_HTTP_REDIRECT";

	if(ptrAttributes->isSet(strRedirectAttr))
		FCGX_FPrintF(pFCGXStream, "Status: 302 Found\r\n"
								   "Location: %s\r\n",ptrAttributes->getValue(strRedirectAttr).c_str());

	const String& strFormat(ptrAttributes->getFormat());

  String strContentType(FormatMapper::MapFormatToContentType(ptrAttributes));

	FCGX_FPrintF(pFCGXStream, "Content-Type: %s\r\n\r\n", strContentType.c_str());

	while((*ptrContent).good()){
		(*ptrContent).read(sBuffer, iBufSize);
	    if((*ptrContent).gcount())
	    	FCGX_PutStr(sBuffer,(*ptrContent).gcount(),pFCGXStream);
	    iNumBytes+=(*ptrContent).gcount();
	}

	FCGX_FFlush(pFCGXStream);

}
/*************************************************************************/
Message::~Message() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Content* Message::getContent(){
	IAS_TRACER;
	return ptrContent;
}
/*************************************************************************/
API::Attributes* Message::getAttributes(){
	IAS_TRACER;
	return ptrAttributes;
}
/*************************************************************************/

}
}
}
