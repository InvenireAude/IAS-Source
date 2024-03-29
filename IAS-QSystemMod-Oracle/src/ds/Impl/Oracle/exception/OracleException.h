/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/exception/OracleException.h 
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

#ifndef _IAS_DS_API_OracleException_H_
#define _IAS_DS_API_OracleException_H_

#include <ds/api/exception/Exception.h>

#include <oci.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace Oracle{
/*************************************************************************/
/** The OracleException exception class.
 */

class OracleException : public ::IAS::DS::API::Exception {

public:
	OracleException();
	OracleException(const String& strInfo);
	OracleException(const String& strInfo, int rc);
	virtual ~OracleException() throw();
	
	virtual const char*  getName();

	static void ThrowOnError(const String& strInfo, OCIError *errhp, sword status);

	//static const char* GetErrorString(int rc);
};

}
}
}
}

#endif /*_IAS_DS_API_OracleException_H_*/

