/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/System.h
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
#ifndef _IAS_QS_UDP_System_H_
#define _IAS_QS_UDP_System_H_

#include <commonlib/commonlib.h>

#include <qs/api.h>

#include <qs/Impl/System.h>

namespace IAS {
namespace QS {
namespace UDP {

class ContentManager;

class InputDriver;
class OutputDriver;

/*************************************************************************/
/** The UDP class.
 *
 */
class System :
		public Impl::System {
public:

	virtual ~System() throw();

	virtual API::Connection* createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	ContentManager*  	getContentManager();


	InputDriver*  getInputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                const API::Destination& destination);
	OutputDriver* getOutputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                const API::Destination& destination);


protected:

	System();

	virtual InputDriver*  createInputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                const API::Destination& destination)=0;
	virtual OutputDriver* createOutputDriver(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
                                const API::Destination& destination)=0;

	IAS_DFT_FACTORY< ContentManager >::PtrHolder               ptrContentManager;
	String strName;


	typedef HashMapStringToPointer<InputDriver>  InputDriversMap;
	typedef HashMapStringToPointer<OutputDriver> OutputDriversMap;

	InputDriversMap      hmInputDrivers;
	OutputDriversMap     hmOutputDrivers;

	Mutex mutex;
};
/*************************************************************************/

}
}
}

#endif /* _IAS_QS_UDP_System_H_ */
