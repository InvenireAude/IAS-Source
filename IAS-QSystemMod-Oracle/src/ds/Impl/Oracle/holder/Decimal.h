/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/Decimal.h
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
#ifndef _IAS_DS_Impl_Oracle_Holder_Decimal_H_
#define _IAS_DS_Impl_Oracle_Holder_Decimal_H_

#include <commonlib/commonlib.h>

#include "Base.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
/** The Decimal class.
 *
 */
class Decimal : public Base {
public:

	virtual ~Decimal() throw();

	virtual void fetch(DM::DataObjectPtr& dm);
	virtual void feed(DM::DataObjectPtr& dm);

protected:
	Decimal(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional);

	static const size_t CBufferLen=sizeof(OCINumber);

  String strFormat;
	friend class ::IAS::Factory<Decimal>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_DS_Impl_Oracle_Holder_Decimal_H_ */
