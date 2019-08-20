/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/DataObjectBinary.h 
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
#ifndef _IAS_DS_Impl_Oracle_Holder_DataObjectBinary_H_
#define _IAS_DS_Impl_Oracle_Holder_DataObjectBinary_H_

#include <commonlib/commonlib.h>

#include "DataObjectSimple.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
/** The DataObjectBinary class.
 *
 */
class DataObjectBinary : public DataObjectSimple {
public:

	virtual ~DataObjectBinary() throw();

protected:
	DataObjectBinary(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional);

	friend class ::IAS::Factory<DataObjectBinary>;

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_DS_Impl_Oracle_Holder_DataObjectBinary_H_ */
