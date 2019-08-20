/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/Helper.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_SPS_Helper_H_
#define _IAS_QS_Workers_Proc_Logic_SPS_Helper_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Context.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

/*************************************************************************/
/** The Helper class.
 *
 */
class Helper {
public:

	static void UpdateContext(org::invenireaude::qsystem::workers::Context *dmContext,
			           	   	  const String& strPID,
			           	   	  int   iSeq);

	static void RetrieveContext(const org::invenireaude::qsystem::workers::Context *dmContext,
				           	  	String& strPID,
				           	   	int&    iSeq);

protected:

	static const String CAttrNamePID;
	static const String CAttrNameSEQ;

};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_SPS_Helper_H_ */
