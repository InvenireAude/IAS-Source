/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/Statement.h 
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
#ifndef _IAS_DS_Impl_Oracle_Statement_H_
#define _IAS_DS_Impl_Oracle_Statement_H_

#include <commonlib/commonlib.h>
#include <ds/api/Statement.h>

#include "tools/Handle.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
class Session;
/*************************************************************************/
/** The Statement class.
 *
 */
class Statement :
		public virtual DS::API::Statement,
		public Tools::HandleStatement{
public:

	virtual ~Statement() throw();

	virtual void setSQLText(const String& strSQLText);

	virtual void prepare();
	virtual void execute();

	inline const String& getSQLText()const{ return strSQLText; }

	Session* getSession()const { return pSession; };

protected:
	Statement(Session* pSession);

	String strSQLText;
	Session* pSession;

	DS::API::Environment::ObjectMode iObjectMode;
	String     strFormatter;

	friend class Factory<Statement>;
};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_Oracle_Statement_H_ */
