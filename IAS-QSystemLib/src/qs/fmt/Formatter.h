/*
 * File: IAS-QSystemLib/src/qs/fmt/Formatter.h
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
#ifndef _IAS_QS_Fmt_Formatter_H_
#define _IAS_QS_Fmt_Formatter_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <dm/json/JSONHelper.h>

#include <org/invenireaude/qsystem/workers/Context.h>

namespace IAS {
namespace QS {
namespace API{
class Message;
class Content;
class Attributes;
}

namespace Fmt {

/*************************************************************************/
/** The XMLFormatter class.
 *
 */
class Formatter {
public:

	virtual ~Formatter(){};

	virtual void write(const DM::DataObject* dmData,
						std::ostream&       ostream,
					    QS::API::Attributes *pAttributes=NULL)=0;

	virtual void read( DM::DataObjectPtr& dmData,
					   std::istream&       istream,
					   QS::API::Attributes *pAttributes=NULL)=0;

protected:

 String substitute(const String& strPattern, const QS::API::Attributes *pAttributes)const;
};

/*************************************************************************/
}
}
}
#endif /* _IAS_QS_Fmt_Formatter_H_ */
