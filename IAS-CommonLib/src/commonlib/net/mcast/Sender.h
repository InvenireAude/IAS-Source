/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/Sender.h
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


#ifndef _IAS_Net_MCast_Sender_H_
#define _IAS_Net_MCast_Sender_H_

#include <commonlib/types.h>
#include "Base.h"

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The Sender class.
 *
 */
class Sender : public virtual Base {
public:

	Sender(unsigned int iPort);
	virtual ~Sender() throw();

	void setup(const String& strInterface, const String& strGroup);

	void send(const void *pData, size_t iDataSize);
	void send(const void *pData, size_t iDataSize, size_t& iWritten);
	
protected:

	struct sockaddr_in groupSock;

};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_MCast_Sender_H_ */
