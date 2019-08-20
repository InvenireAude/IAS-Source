/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemFmt-MQPCF/src/qs/fmt/PCFFormatter.h 
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
#ifndef _IAS_QS_Fmt_PCFFormatter_H_
#define _IAS_QS_Fmt_PCFFormatter_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include <qs/fmt/Formatter.h>

#include <org/invenireaude/qsystem/workers/Context.h>


namespace IAS {
namespace QS {
namespace Fmt {
namespace PCF {
class Dictionary;
}
/*************************************************************************/
/** The PCFFormatter class.
 *
 */
class PCFFormatter : public Formatter {
public:

	virtual ~PCFFormatter() throw();

	virtual void write(const DM::DataObject* dmData,
							std::ostream&       ostream,
						    QS::API::Attributes *pAttributes=NULL);

	virtual void read( DM::DataObjectPtr& dmData,
						   std::istream&       istream,
						   QS::API::Attributes *pAttributes=NULL);

	const DM::DataFactory* getDataFactory()const;
	const PCF::Dictionary* getDictionary()const;


protected:
	PCFFormatter(const DM::DataFactory* pDataFactory);


	const DM::DataFactory* pDataFactory;

	IAS_DFT_FACTORY<PCF::Dictionary>::PtrHolder ptrDictionary;

	TimeSamplesResults tsrParsing;
	TimeSamplesResults tsrSerialization;


	friend class Factory<PCFFormatter>;

};

/*************************************************************************/
}
}
}

/*************************************************************************/
extern "C"{
void* _ias_qs_fmt_PCF(const ::IAS::DM::DataFactory* pDataFactory);
void* _ias_qs_fmt_MQADMIN(const ::IAS::DM::DataFactory* pDataFactory);
void* _ias_qs_fmt_MQEVENT(const ::IAS::DM::DataFactory* pDataFactory);

}
/*************************************************************************/
#endif /* _IAS_QS_Fmt_PCFFormatter_H_ */
