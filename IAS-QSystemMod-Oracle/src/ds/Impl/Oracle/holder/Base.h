/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/Base.h 
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
#ifndef _IAS_DS_Impl_Oracle_Holder_Base_H_
#define _IAS_DS_Impl_Oracle_Holder_Base_H_

#include <commonlib/commonlib.h>

#include "../Statement.h"
#include <dm/datamodel.h>
#include <dm/tools/Setter.h>

#include "../log/LogLevel.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

class Session;
/*************************************************************************/
/** The Base class.
 *
 */
class Base  {
public:

	virtual ~Base() throw();

	static Base* Create(Statement* pStatement, DM::Tools::Setter* pSetter, bool bOptional);

	typedef IAS_DFT_FACTORY<Base> Factory;

	class Table : public
		std::vector<Base*>,
		PtrCleaner< Table, Base::Factory::Deleter >{
		public:
		  Table(): PtrCleaner< Table, Base::Factory::Deleter>(*this){};
	};

	void define(int iPos);
	void bind(int iPos);

	virtual void fetch(DM::DataObjectPtr& dm)=0;
	virtual void feed(DM::DataObjectPtr& dm)=0;

protected:

	Base(Statement* pStatement,
		 DM::Tools::Setter* pSetter,
		 bool bOptional,
		 size_t iBufferSize,
		 ub2    iOCIType);

	Buffer          bufData;
	sb2             bNull;

	OCIDefine       *hpDefine;
	OCIBind         *hpBind;

	ub2             iLen;
	ub2             iOCIType;
	bool            bOptional;
	int             iPos;

	DM::Tools::Setter* pSetter;
	Statement* pStatement;

	bool			bRebind;
	bool			bRedefine;

protected:
	void        assureBufferSize(size_t iRequestedSize);
};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_DS_Impl_Oracle_Base_H_ */
