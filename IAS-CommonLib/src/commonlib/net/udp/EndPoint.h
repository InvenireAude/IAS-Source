/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/EndPoint.h
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

#ifndef _IAS_Net_UDP_EndPoint_H_
#define _IAS_Net_UDP_EndPoint_H_

#include <commonlib/types.h>

namespace IAS {
namespace Net {
namespace UDP {

/*************************************************************************/
/** The EndPoint class.
 *
 */
class EndPoint {
public:

  typedef unsigned int PacketSizeType;


	inline const String&  getSourceIP()const{
		return strSourceIP;
	}

	inline const String&  getDestinationIP()const{
		return strDestinationIP;
	}

	inline unsigned int getDestinationPort()const{
		return iDestinationPort;
	}

	inline PacketSizeType getMaxPacketSize()const{
		return iMaxPacketSize;
	}

	inline EndPoint& operator=(const EndPoint& other){
        this->strSourceIP=other.strSourceIP;
        this->strDestinationIP=other.strDestinationIP;
        this->iDestinationPort=other.iDestinationPort;
        this->iMaxPacketSize=other.iMaxPacketSize;
		return *this;
	}


	EndPoint(const String& strDestinationIP, const String& strSourceIP, unsigned int iDestinationPort, PacketSizeType iMaxPacketSize);
	EndPoint(const EndPoint& other);

	friend std::ostream& operator<<(std::ostream&, const EndPoint&);

protected:
	String   strSourceIP;
	String   strDestinationIP;
	unsigned int iDestinationPort;
  PacketSizeType iMaxPacketSize;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Bus_EndPoint_H_ */
