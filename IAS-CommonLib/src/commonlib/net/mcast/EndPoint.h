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

#ifndef _IAS_Net_Bus_EndPoint_H_
#define _IAS_Net_Bus_EndPoint_H_

#include <commonlib/types.h>

namespace IAS {
namespace Net {
namespace MCast {

/*************************************************************************/
/** The EndPoint class.
 *
 */
class EndPoint {
public:

	inline const String&  getInterface()const{
		return strInterface;
	}

	inline const String&  getGroup()const{
		return strGroup;
	}

	inline unsigned int getPort()const{
		return iPort;
	}

	inline EndPoint& operator=(const EndPoint& other){
        this->strInterface=other.strInterface;
        this->strGroup=other.strGroup;
        this->iPort=other.iPort;
		return *this;
	}

	EndPoint(const String& strGroup, const String& strInterface, unsigned int iPort);
	EndPoint(const EndPoint& other);


	friend std::ostream& operator<<(std::ostream&, const EndPoint&);

protected:
	String   strInterface;
	String   strGroup;
	unsigned int iPort;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Bus_EndPoint_H_ */