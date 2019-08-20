/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Tools.h 
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License. 
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 * 
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 * 
 */
#ifndef _IAS_QS_WMQ_Tools_H_
#define _IAS_QS_WMQ_Tools_H_

#include <commonlib/commonlib.h>

#include "log/LogLevel.h"

namespace IAS {
namespace QS {
namespace WMQ {

class ContentManager;

/*************************************************************************/
/** The WMQ class.
 *
 */
class Tools  {
public:

	static String GetMQMDValue(const char* s, int iMaxLen);

};
/*************************************************************************/

}
}
}

#endif /* _IAS_QS_WMQ_Tools_H_ */
