/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemFmt-MQPCF/src/qs/fmt/pcf/Writer.h 
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
#ifndef _IAS_QS_Fmt_PCF_Writer_H_
#define _IAS_QS_Fmt_PCF_Writer_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <qs/api.h>
#include <cmqc.h>
#include <cmqcfc.h>

namespace IAS {
namespace QS {
namespace Fmt {
class PCFFormatter;
namespace PCF {
class Dictionary;
/*************************************************************************/
/** The Writer class.
 *
 */
class Writer {
public:

	virtual ~Writer() throw();

	void write();

protected:
	Writer(const PCFFormatter*    pFormatter,
		   const DM::DataObject*  dmData,
		   std::ostream&          ostream,
           QS::API::Attributes    *pAttributes=NULL);

	const DM::DataFactory* pDataFactory;
	const PCFFormatter*    pFormatter;
	const Dictionary*      pDictionary;

	const DM::DataObject*  dmData;
	std::ostream&          ostream;
	QS::API::Attributes    *pAttributes;

	void writeValues(const DM::DataObject* dmParent);

	friend class Factory<Writer>;

	IAS_DFT_FACTORY<Buffer>::PtrHolder ptrBuffer;

private:
	void writeCFIN(MQLONG iParameterID, MQLONG iValue);
	void writeCFST(const DM::Property* pProperty);
	void makeCFIL(MQLONG iParameterID, const DM::DataObjectList& lstObjects);
	void makeCFSTL(MQLONG iParameterID, const DM::DataObjectList& lstObjects);
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Fmt_PCF_Writer_H_ */
