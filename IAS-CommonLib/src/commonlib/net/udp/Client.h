/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/Client.h
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


#ifndef _IAS_Net_UDP_Client_H_
#define _IAS_Net_UDP_Client_H_

#include <commonlib/types.h>
#include "Socket.h"

namespace IAS {
namespace Net {
namespace UDP {

/*************************************************************************/
/** The Client class.
 *
 */
class Client : public virtual Socket {
public:

	Client(unsigned int iDestinationPort);
	virtual ~Client() throw();

	void setup(const String& strSourceIP, const String& strDestinationIP);

	bool receive(void *pData, size_t iBufferLen, size_t& iDataSize);
	void send(const void *pData, size_t iDataSize);

protected:

	struct sockaddr_in destSockAddr;

};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_UDP_Client_H_ */
