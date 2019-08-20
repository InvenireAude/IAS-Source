/*
 * Copyright (C) 2017, Albert Krzymowski
 * Copyright (C) 2017, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/DataObjectLOB.h 
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
#ifndef _IAS_DS_Impl_Oracle_Holder_DataObjectLOB_H_
#define _IAS_DS_Impl_Oracle_Holder_DataObjectLOB_H_

#include <commonlib/commonlib.h>

#include "Base.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
/** The DataObjectLOB class.
 *
 */
class DataObjectLOB : public Base {
public:

	virtual ~DataObjectLOB() throw();

	virtual void fetch(DM::DataObjectPtr& dm);
	virtual void feed(DM::DataObjectPtr& dm);

protected:
	DataObjectLOB(Statement* pStatement,
	 	 	 	  DM::Tools::Setter* pSetter,
				  bool bOptional,
				  ub2    iOCIType);

	static const size_t CBufferLen=sizeof(OCILobLocator*);

	friend class ::IAS::Factory<DataObjectLOB>;

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_DS_Impl_Oracle_Holder_DataObjectLOB_H_ */
