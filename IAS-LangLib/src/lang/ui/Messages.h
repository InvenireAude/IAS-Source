/*
 * File: Messages.h
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


#ifndef _IAS_Lang_UI_Messages_H_
#define _IAS_Lang_UI_Messages_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace UI {

/*************************************************************************/
/** The Messages class.
 *
 */
class Messages : public IAS::MessageCatalog::MessageCatalogUpdater{

public:

	static const MessageCatalog::MsgId	MSGI_LangEnvInfo               = 11001;
  static const MessageCatalog::MsgId	MSGI_LangScriptLog             = 11901;

	static const MessageCatalog::MsgId	MSGE_LangEnvError              = 21001;
	static const MessageCatalog::MsgId	MSGE_LangScriptParseError      = 21002;
	static const MessageCatalog::MsgId	MSGE_LangScriptNotFoundError   = 21003;
	static const MessageCatalog::MsgId	MSGE_LangScriptUsageError      = 21004;
	static const MessageCatalog::MsgId	MSGE_LangScriptRuntimeError    = 21010;
	static const MessageCatalog::MsgId	MSGE_LangInternalError         = 21999;

  static const MessageCatalog::MsgId	MSGW_LangScriptAmbiguousParameters      = 31001;
  static const MessageCatalog::MsgId	MSGW_LangScriptImplicitCast             = 31002;


	Messages();
	virtual ~Messages();

protected:

	static Messages TheInstance;
};


/*************************************************************************/
}
}
}

#endif /* _IAS_Lang_UI_Messages_H_ */
