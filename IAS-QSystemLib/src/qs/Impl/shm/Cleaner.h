/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Cleaner.h
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
#ifndef _IAS_QS_System_Cleaner_H_
#define _IAS_QS_System_Cleaner_H_

#include <commonlib/commonlib.h>
#include <commonlib/memory/mm/SimpleListMemoryManager.h>

#include "shared/Queue.h"

namespace IAS {
namespace QS {
namespace SHM {
class Attachment;
namespace Shared {

class SharedMemorySegment;
class QueueTable;
class Connection;
class ContentStorage;

}
/*************************************************************************/
/** The Cleaner class.
 *
 */
class Cleaner {
public:

	virtual ~Cleaner() throw();

	void start();


protected:

	Cleaner(Attachment *pAttachment);
	Attachment *pAttachment;

	void work();

	friend class Factory<Cleaner>;
};


/*************************************************************************/

}
}
}

#endif /* _IAS_QS_Cleaner_Cleaner_H_ */
