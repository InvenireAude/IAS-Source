/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/exception/WMQException.h 
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
/* ChangeLog:
 * 
 */

#ifndef _IAS_QS_WMQ_WMQException_H_
#define _IAS_QS_WMQ_WMQException_H_

#include <commonlib/commonlib.h>
#include "cmqc.h"

namespace IAS{
namespace QS {
namespace WMQ {
/*************************************************************************/
/** The WMQException exception class.
 */

class WMQException : public IAS::Exception
{
public:
	WMQException();
	WMQException(const String& strInfo, MQLONG iReason);
	virtual ~WMQException() throw();
	
	virtual const char*  getName();

	MQLONG getReason()const{return iReason;};

protected:
	MQLONG iReason;

	static bool bStopOnConnectionLost;
};

}}}

#endif /*ITEMNOTFOUNDEXCEPTION_H_*/
