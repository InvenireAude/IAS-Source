/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/DataObjectBLOB.h 
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
#ifndef _IAS_DS_Impl_Oracle_Holder_DataObjectBLOB_H_
#define _IAS_DS_Impl_Oracle_Holder_DataObjectBLOB_H_

#include <commonlib/commonlib.h>

#include "DataObjectLOB.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
/** The DataObjectBLOB class.
 *
 */
class DataObjectBLOB : public DataObjectLOB {
public:

	virtual ~DataObjectBLOB() throw();

protected:
	DataObjectBLOB(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional);

	friend class ::IAS::Factory<DataObjectBLOB>;

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_DS_Impl_Oracle_Holder_DataObjectBLOB_H_ */
