/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/Socket.h
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


#ifndef _IAS_Net_UDP_Socket_H_
#define _IAS_Net_UDP_Socket_H_

#include <commonlib/types.h>
#include "../Peer.h"

namespace IAS {
namespace Net {
namespace UDP {

/*************************************************************************/
/** The Socket class.
 *
 */
class Socket {
public:

	virtual ~Socket() throw();

	void setTimeout(int iTimeout);
	static const int  C_UnLimited = -1;

protected:
	Socket(unsigned int iDestinationPort);

	int iTimeout;

	enum WaitMode{
		WM_Read,
		WM_Write
	};

	bool waitForData(WaitMode iMode);
	unsigned int iDestinationPort;
	int iSocket;

	void bind(unsigned int iPort = 0);

	bool receive(void *pData, size_t iBufferLen, size_t& iDataSize,
                   struct sockaddr_storage* pSrcAddress, socklen_t* pAddressLen);

  bool receive(void *pData, size_t iBufferLen, size_t& iDataSize, String& strSrcIP, int &iSrcPort);
  bool receive(void *pData, size_t iBufferLen, size_t& iDataSize);

	void send(struct sockaddr_in& destSockAddr, const void *pData, size_t iDataSize, size_t& iWritten);

};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_UDP_Socket_H_ */
