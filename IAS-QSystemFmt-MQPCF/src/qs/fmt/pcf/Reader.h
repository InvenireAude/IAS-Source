/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemFmt-MQPCF/src/qs/fmt/pcf/Reader.h 
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
#ifndef _IAS_QS_Fmt_PCF_Reader_H_
#define _IAS_QS_Fmt_PCF_Reader_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {
class PCFFormatter;
namespace PCF {

/*************************************************************************/
/** The Reader class.
 *
 */
class Reader {
public:

	virtual ~Reader() throw();

	void read();

protected:
	Reader(const PCFFormatter*    pFormatter,
		   DM::DataObjectPtr&     dmData,
		   std::istream&          istream,
           QS::API::Attributes    *pAttributes=NULL);

	const DM::DataFactory* pDataFactory;
	const PCFFormatter*    pFormatter;

	DM::DataObjectPtr&     dmData;
	std::istream&          istream;
	QS::API::Attributes    *pAttributes;

	void readValues(DM::DataObject* dmParent, unsigned int iNumParameters);


	friend class Factory<Reader>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Fmt_PCF_Reader_H_ */
