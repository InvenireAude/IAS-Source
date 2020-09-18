/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/Receiver.h
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


#ifndef _IAS_Net_MCast_Receiver_H_
#define _IAS_Net_MCast_Receiver_H_

#include <commonlib/types.h>
#include "Base.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The Receiver class.
 *
 */
class Receiver : public virtual Base {
public:

	Receiver(unsigned int iPort);
	virtual ~Receiver() throw();

	void bind();

	void subscribe(const String& strInterface, const String& strGroup);

	void receive(void *pData, size_t iBufferLen, size_t& iDataSize);

protected:
	

};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_Receiver_H_ */
