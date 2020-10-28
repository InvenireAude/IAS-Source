/*
 * File: IAS-QSystemLib/src/qs/fmt/JSONPureFormatter.cpp
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
#include "Formatter.h"

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
String Formatter::substitute(const String& strPattern, const QS::API::Attributes *pAttributes)const{
	IAS_TRACER;

	StringStream ssResult;

	for(String::const_iterator it=strPattern.begin(); it != strPattern.end(); it++){

		if(*it == '$'){

			if(++it != strPattern.end() && *it == '{'){

				String strName;

				while(++it != strPattern.end() && *it != '}')
					strName+=(*it);

				if(*it != '}')
					IAS_THROW(BadUsageException("Missing '}' in environment pattern."))

				ssResult<<pAttributes->getValue(strName);

			}

		}else{
			ssResult<<*it;
		}


	}

	return ssResult.str();
}
/*************************************************************************/
}
}
}
