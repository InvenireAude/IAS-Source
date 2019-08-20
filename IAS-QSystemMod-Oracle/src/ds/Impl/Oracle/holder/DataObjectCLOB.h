/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/DataObjectCLOB.h 
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
#ifndef _IAS_DS_Impl_Oracle_Holder_DataObjectCLOB_H_
#define _IAS_DS_Impl_Oracle_Holder_DataObjectCLOB_H_

#include <commonlib/commonlib.h>

#include "DataObjectLOB.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
/** The DataObjectCLOB class.
 *
 */
class DataObjectCLOB : public DataObjectLOB {
public:

	virtual ~DataObjectCLOB() throw();

protected:
	DataObjectCLOB(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional);

	friend class ::IAS::Factory<DataObjectCLOB>;

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_DS_Impl_Oracle_Holder_DataObjectCLOB_H_ */
