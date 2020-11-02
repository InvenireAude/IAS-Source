/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/Server.h
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


#ifndef _IAS_Net_UDP_Server_H_
#define _IAS_Net_UDP_Server_H_

#include <commonlib/types.h>
#include "Socket.h"

namespace IAS {
namespace Net {
namespace UDP {

/*************************************************************************/
/** The Server class.
 *
 */
class Server : public virtual Socket {
public:

	Server(unsigned int iDestinationPort);
	virtual ~Server() throw();

	bool receive(void *pData, size_t iBufferLen, size_t& iDataSize, String& strSrcIP, int &iSrcPort);

	bool receive(void *pData, size_t iBufferLen, size_t& iDataSize,
                   struct sockaddr_storage* pSrcAddress, socklen_t* pAddressLen);

	void send(const void *pData, size_t iDataSize, String& strDstIP, int &iDstPort);
	void send(const void *pData, size_t iDataSize, struct sockaddr_in& destSockAddr);

protected:


};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_UDP_Server_H_ */
