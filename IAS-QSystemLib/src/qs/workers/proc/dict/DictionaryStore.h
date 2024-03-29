/*
 * File: IAS-QSystemLib/src/qs/workers/proc/dict/DictionaryStore.h
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
#ifndef _IAS_QS_Workers_Proc_Dict_DictionaryStore_H_
#define _IAS_QS_Workers_Proc_Dict_DictionaryStore_H_

#include <commonlib/commonlib.h>

#include "Dictionary.h"

#include <org/invenireaude/qsystem/workers/dict/DataFactory.h>
#include <org/invenireaude/qsystem/workers/dict/Dictionary.h>
#include <org/invenireaude/qsystem/workers/dict/Item.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Dict {

/*************************************************************************/
/** The DictionaryStore class.
 *
 */
class DictionaryStore {
public:

	virtual ~DictionaryStore() throw();


	DM::DataObject* getValue(const String& strDictionary, const String& strKey, unsigned int iTimeoutMS = 0);

	void create(const org::invenireaude::qsystem::workers::dict::Dictionary* dmDictionary);

protected:

	DictionaryStore();

	Mutex       mutex;
	Condition   cndWaitForDictionary;

	Dictionary* lookup(const String& strDictionary, unsigned int iTimeoutMS = 0);

	typedef HashMapStringToPointer<Dictionary> DictionariesMap;

	DictionariesMap hmDictionaries;

	friend class Factory<DictionaryStore>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Dict_DictionaryStore_H_ */
