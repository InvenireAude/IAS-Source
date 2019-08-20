/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemFmt-MQPCF/src/qs/fmt/PCFFormatter.cpp 
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
#include "PCFFormatter.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/api.h>
#include <qs/fmt/pcf/Reader.h>
#include <qs/fmt/pcf/Writer.h>
#include <qs/fmt/pcf/Dictionary.h>

namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
PCFFormatter::PCFFormatter(const DM::DataFactory* pDataFactory):
		pDataFactory(pDataFactory),
		ptrDictionary(IAS_DFT_FACTORY<PCF::Dictionary>::Create()){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);

}
/*************************************************************************/
PCFFormatter::~PCFFormatter() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void PCFFormatter::read(DM::DataObjectPtr& dmData,
		   	   	   	   	std::istream&       istream,
		   	   	   	   	QS::API::Attributes *pAttributes){

	IAS_TRACER;


	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
	ts.start();

	IAS_DFT_FACTORY<PCF::Reader>::PtrHolder
		ptrReader(IAS_DFT_FACTORY<PCF::Reader>::Create<const PCFFormatter*,
													   DM::DataObjectPtr&,
													   std::istream&,
													   QS::API::Attributes*>(this,dmData, istream, pAttributes));


	ptrReader->read();

	//TODO temporary
	pAttributes->setFormat("JSON");

	//dmData=ptrDoc->getRootObject();

}
/*************************************************************************/
void PCFFormatter::write(const DM::DataObject* dmData,
						 std::ostream&         ostream,
						 QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();

	IAS_DFT_FACTORY<PCF::Writer>::PtrHolder
		ptrWriter(IAS_DFT_FACTORY<PCF::Writer>::Create<const PCFFormatter*,
													   const DM::DataObject*,
													   std::ostream&,
													   QS::API::Attributes*>(this,dmData, ostream, pAttributes));


	ptrWriter->write();

	tsrSerialization.addSample(ts);
}
/*************************************************************************/
const DM::DataFactory* PCFFormatter::getDataFactory()const{
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataFactory);
	return pDataFactory;
}
/*************************************************************************/
const PCF::Dictionary* PCFFormatter::getDictionary()const{
	IAS_TRACER;
	IAS_CHECK_IF_NULL(ptrDictionary);
	return ptrDictionary;
}
/*************************************************************************/

}
}
}

/*************************************************************************/
extern "C"{

void* _ias_qs_fmt_PCF(const ::IAS::DM::DataFactory* pDataFactory){
	IAS_TRACER;
	return IAS_DFT_FACTORY< ::IAS::QS::Fmt::PCFFormatter >::Create(pDataFactory);
}

void* _ias_qs_fmt_MQADMIN(const ::IAS::DM::DataFactory* pDataFactory){
	IAS_TRACER;
	return IAS_DFT_FACTORY< ::IAS::QS::Fmt::PCFFormatter >::Create(pDataFactory);
}

void* _ias_qs_fmt_MQEVENT(const ::IAS::DM::DataFactory* pDataFactory){
	IAS_TRACER;
	return IAS_DFT_FACTORY< ::IAS::QS::Fmt::PCFFormatter >::Create(pDataFactory);
}


}
/*************************************************************************/
