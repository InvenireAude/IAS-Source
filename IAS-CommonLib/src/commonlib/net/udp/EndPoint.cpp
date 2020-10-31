/*
 * File: IAS-CommonLib/src/commonlib/net/mcast/EndPoint.cpp
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

#include "EndPoint.h"
#include <commonlib/logger/logger.h>


namespace IAS {
namespace Net {
namespace UDP {

/*************************************************************************/
EndPoint::EndPoint(const String& strDestinationIP, const String& strSourceIP, unsigned int iDestinationPort,
                   PacketSizeType iMaxPacketSize):
	strSourceIP(strSourceIP),
	strDestinationIP(strDestinationIP),
	iDestinationPort(iDestinationPort),
  iMaxPacketSize(iMaxPacketSize){
	IAS_TRACER;
}
/*************************************************************************/
EndPoint::EndPoint(const EndPoint& other):
	strSourceIP(other.strSourceIP),
	strDestinationIP(other.strDestinationIP),
	iDestinationPort(other.iDestinationPort),
  iMaxPacketSize(other.iMaxPacketSize){
	IAS_TRACER;
}
/*************************************************************************/
std::ostream& operator<<(std::ostream& os, const EndPoint& ep){
	os<<"EP:["<<ep.strSourceIP<<","<<ep.strDestinationIP<<","<<ep.iDestinationPort<<","<<ep.iMaxPacketSize<<"]";
	return os;
}
/*************************************************************************/

}
}
}
