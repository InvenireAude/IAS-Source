/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/log/LogLevel.cpp 
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
#include "LogLevel.h"

#include <commonlib/commonlib.h>

#define IAS_LOG_LEVEL_QS_WMQ_ENV "IAS_DBG_QS_WMQ"

namespace IAS {
namespace QS {
namespace WMQ {

/*************************************************************************/
LogLevelBase LogLevel::INSTANCE=LogLevelBase(IAS_LOG_LEVEL_QS_WMQ_ENV);
/*************************************************************************/

}
}
}
