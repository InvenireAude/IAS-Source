/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/DateTime.h 
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
#ifndef _IAS_DS_Impl_Oracle_Holder_DateTime_H_
#define _IAS_DS_Impl_Oracle_Holder_DateTime_H_

#include <commonlib/commonlib.h>

#include "Base.h"
#include "../tools/Descriptor.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
/** The DateTime class.
 *
 */
class DateTime : public Base {
public:

	virtual ~DateTime() throw();

	virtual void fetch(DM::DataObjectPtr& dm);
	virtual void feed(DM::DataObjectPtr& dm);

protected:
	DateTime(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional);

	static const size_t CBufferLen=sizeof(OCIDateTime*);

	Tools::DescriptorTimeStamp  descTimeStamp;
	friend class ::IAS::Factory<DateTime>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_DS_Impl_Oracle_Holder_DateTime_H_ */
