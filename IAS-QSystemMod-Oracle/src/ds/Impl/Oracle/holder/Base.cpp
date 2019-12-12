/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/Base.cpp
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
#include "Base.h"

#include "../exception/OracleException.h"

#include"DataObjectCLOB.h"
#include"DataObjectBLOB.h"
#include"DataObjectText.h"
#include"DataObjectBinary.h"

#include"Date.h"
#include"DateTime.h"
#include"Float.h"
#include"Boolean.h"
#include"Integer.h"
#include"Text.h"

#include "../Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {
/*************************************************************************/
Base::Base(Statement* pStatement,
		DM::Tools::Setter* pSetter,
		bool bOptional,
		size_t iBufferSize,
		ub2    iOCIType):
		pStatement(pStatement),
		bOptional(bOptional),
		bufData(iBufferSize),
		pSetter(pSetter),
		iPos(-1),
		hpDefine(0),
		hpBind(0),
		iLen(0),
		iOCIType(iOCIType),
		bNull(0),
		bRedefine(false),
		bRebind(false){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Holder: ["<<pSetter->getXPath()<<"] "<<iOCIType<<" "<<iBufferSize<<" "<<bOptional);

}
/*************************************************************************/
Base::~Base() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Base* Base::Create(Statement* pStatement, DM::Tools::Setter* pSetter, bool bOptional){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath()<<":"<<pSetter->getTargetTypeEnum());


	switch(pSetter->getTargetTypeEnum()) {

		case DM::Type::DataObjectType:
		case DM::Type::AnyType:

			switch(pStatement->getSession()->getObjectMode()){

				case DS::API::Environment::OM_TEXT:
					return IAS_DFT_FACTORY<DataObjectText>::Create(pStatement,pSetter,bOptional);
					break;

				case DS::API::Environment::OM_BINARY:
					return IAS_DFT_FACTORY<DataObjectBinary>::Create(pStatement,pSetter,bOptional);
					break;

				case DS::API::Environment::OM_CLOB:
					return IAS_DFT_FACTORY<DataObjectCLOB>::Create(pStatement,pSetter,bOptional);
					break;

				case DS::API::Environment::OM_BLOB:
					return IAS_DFT_FACTORY<DataObjectBLOB>::Create(pStatement,pSetter,bOptional);
					break;

				default:
					IAS_THROW(InternalException(String("Unknown object mode: ") + pStatement->getSQLText()));
			};

			break;

		case DM::Type::DateType:
			return IAS_DFT_FACTORY<Date>::Create(pStatement,pSetter,bOptional);
			break;

		case DM::Type::TimeType:
		case DM::Type::DateTimeType:
			return IAS_DFT_FACTORY<DateTime>::Create(pStatement,pSetter,bOptional);
			break;

		case DM::Type::FloatType:
			return IAS_DFT_FACTORY<Float>::Create(pStatement,pSetter,bOptional);
			break;

		case DM::Type::IntegerType:
			return IAS_DFT_FACTORY<Integer>::Create(pStatement,pSetter,bOptional);
			break;

		case DM::Type::BooleanType:
			return IAS_DFT_FACTORY<Boolean>::Create(pStatement,pSetter,bOptional);
			break;

		case DM::Type::TextType:
    case DM::Type::DecimalType:
			return IAS_DFT_FACTORY<Text>::Create(pStatement,pSetter,bOptional);
			break;

		default:
			return IAS_DFT_FACTORY<Text>::Create(pStatement,pSetter,bOptional);

	}
}
/*************************************************************************/
void Base::define(int iPos){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"define: "<<iPos<<" "<<bufData.getBuffer<void>());

	sword rc = OCIDefineByPos((OCIStmt*)*pStatement,
							   (OCIDefine**)&hpDefine,
							   pStatement->getSession()->getErrorHandle(),
							   iPos,
							   bufData.getBuffer<void>(),
							   (iOCIType != SQLT_CLOB ? (sb4)(bufData.getSize()) : 0),
							   (ub2)iOCIType,
							   (void *) &bNull,
							   (ub2 *) &iLen,
							   0,
							   OCI_DEFAULT);


	OracleException::ThrowOnError(pStatement->getSQLText()+", def="+TypeTools::IntToString(iPos),
				pStatement->getSession()->getErrorHandle(),
				rc);

//	if(this->iPos != -1 && this->iPos != iPos)
//		IAS_THROW(InternalException("iPos != -1 && this->iPos != iPos"));

	this->iPos=iPos;
	this->bRedefine=true;
}
/*************************************************************************/
void Base::bind(int iPos){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"bind: "<<iPos<<" "<<bufData.getBuffer<void>());

	sword rc = OCIBindByPos((OCIStmt*)*pStatement,
								 (OCIBind**)&hpBind,
								 pStatement->getSession()->getErrorHandle(),
								 iPos,
								 bufData.getBuffer<void>(),
								 (sb4)(bufData.getSize()),
								 (ub2)iOCIType,
								 (void *) &bNull,
								 (ub2 *) 0,
								 0,
								 0,
								 (unsigned int *) 0,
								 OCI_DEFAULT);

	OracleException::ThrowOnError(pStatement->getSQLText()+", def="+TypeTools::IntToString(iPos),
				pStatement->getSession()->getErrorHandle(),
				rc);

//	if(this->iPos != -1 && this->iPos != iPos)
//		IAS_THROW(InternalException("iPos != -1 && this->iPos != iPos"));

	this->iPos=iPos;
	this->bRebind=true;
}
/*************************************************************************/
void  Base::assureBufferSize(size_t iRequestedSize){
	IAS_TRACER;

	//TODO decrease size in some cases.

	if(bufData.getSize() >= iRequestedSize)
		return;

	bufData.reserve(iRequestedSize);

	if(bRebind)
		bind(iPos);

	if(bRedefine)
		define(iPos);

}
/*************************************************************************/
}
}
}
}
}

