/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/FunctionOutput.h
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
#ifndef _IAS_DS_Impl_Oracle_FunctionOutput_H_
#define _IAS_DS_Impl_Oracle_FunctionOutput_H_

#include <commonlib/commonlib.h>
#include "Output.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
class Session;
/*************************************************************************/
/** The FunctionOutput class.
 *
 */
class FunctionOutput :
		public Output{
public:

	virtual ~FunctionOutput() throw();

	virtual void addOutput(const String& strTag, DM::Tools::Setter *pSetter);

protected:
	FunctionOutput(Statement& statement);
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_Oracle_FunctionOutput_H_ */
