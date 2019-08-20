/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemFmt-MQPCF/src/qs/fmt/pcf/Reader.cpp 
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
#include<qs/log/LogLevel.h>

#include "Reader.h"

#include "Dictionary.h"
#include "../PCFFormatter.h"

#include <cmqc.h>
#include <cmqcfc.h>

namespace IAS {
namespace QS {
namespace Fmt {
namespace PCF {

/*************************************************************************/
Reader::Reader(const PCFFormatter*    pFormatter,
			   DM::DataObjectPtr& dmData,
			   std::istream&       istream,
			   QS::API::Attributes *pAttributes):
					   pFormatter(pFormatter),
					   dmData(dmData),
					   istream(istream),
					   pAttributes(pAttributes){
	IAS_TRACER;

	pDataFactory = pFormatter->getDataFactory();
}

/*************************************************************************/
Reader::~Reader() throw(){
	IAS_TRACER;
}
/*************************************************************************/

struct MQCFH_Header{
	MQLONG iType;
	MQLONG iLength;
	MQLONG iParameter;
};
/*************************************************************************/
void Reader::read(){

	IAS_TRACER;

	MQCFH mqCFH;

	istream.read((char*)&mqCFH,MQCFH_STRUC_LENGTH);

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), "CFH.Type:       "<<mqCFH.Type);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), "CFH.Command:    "<<mqCFH.Command);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), "CFH.Count:      "<<mqCFH.ParameterCount);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), "CFH.MsgSeqNo:   "<<mqCFH.MsgSeqNumber);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), "CFH.Control:    "<<mqCFH.Control);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), "CFH.RC:         "<<mqCFH.Reason);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), "CFH.CC:         "<<mqCFH.CompCode);

	const Dictionary *pDictionary = pFormatter->getDictionary();

	String strNS(pDictionary->getTypeNS(mqCFH.Type));
	String strCommand(pDictionary->getCommandName(mqCFH.Command));

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), strCommand);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), strNS);

	dmData = pDataFactory->getType(strNS, strCommand)->createDataObject();

	dmData->setBoolean("ControlLast", mqCFH.Control == MQCFC_LAST);
	dmData->setInteger("MsgSeqNumber",mqCFH.MsgSeqNumber);
	dmData->setString("CompCode", pDictionary->getCompCode(mqCFH.CompCode));
	dmData->setString("Reason",   pDictionary->getReason(mqCFH.Reason));

	readValues(dmData, mqCFH.ParameterCount);

}
/*************************************************************************/
static String _GetMQMDValue(const char* s, int iMaxLen) {

	while(iMaxLen && s[iMaxLen-1] == ' ')
		iMaxLen--;

	return String(s,iMaxLen);
}
/*************************************************************************/
void Reader::readValues(DM::DataObject* dmParent, unsigned int iNumParameters){

	IAS_TRACER;

	IAS_DFT_FACTORY<Buffer>::PtrHolder ptrBuffer(IAS_DFT_FACTORY<Buffer>::Create(1024));

	const Dictionary *pDictionary = pFormatter->getDictionary();

	const DM::ComplexType* pType = dmParent->getType()->asComplexType();

	while(istream.good() && iNumParameters--){

		istream.read(ptrBuffer->getBuffer<char>(),sizeof(MQCFH_Header));

		MQCFH_Header *pHeader=ptrBuffer->getBuffer<MQCFH_Header>();

		String strParameter(pFormatter->getDictionary()->getParameterName(
				pHeader->iParameter));

		IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), strParameter);
		IAS_LOG(QS::LogLevel::INSTANCE.isInfo(), pHeader->iLength);

		if(pHeader->iLength > ptrBuffer->getSize() ){
			ptrBuffer->resize(pHeader->iLength);
			pHeader=ptrBuffer->getBuffer<MQCFH_Header>();
		}

		istream.read(ptrBuffer->getBuffer<char>() + sizeof(MQCFH_Header),
				pHeader->iLength - sizeof(MQCFH_Header) );

		if(pHeader->iParameter == MQIAMO_OBJECT_COUNT)
			continue;

		try {
			switch(pHeader->iType) {

				case MQCFT_INTEGER: {
					MQCFIN *pMQCFIN = ptrBuffer->getBuffer<MQCFIN>();

					switch(pMQCFIN->Parameter){

					case MQIACF_COMMAND:
						dmParent->setString(strParameter, pDictionary->getMQSCName(pMQCFIN->Value));
					break;

					case MQIA_Q_TYPE:
						dmParent->setString(strParameter, pDictionary->getQTypeName(pMQCFIN->Value));
					break;

					case MQIACH_CHANNEL_TYPE:
						dmParent->setString(strParameter, pDictionary->getChlTypeName(pMQCFIN->Value));
					break;

					case MQIACH_CHANNEL_STATUS:
						dmParent->setString(strParameter, pDictionary->getChlStatusName(pMQCFIN->Value));
					break;

					case MQIACF_MODE:
						dmParent->setString(strParameter, pDictionary->getChannelStopMode(pMQCFIN->Value));
					break;

					case MQIACH_IN_DOUBT:
						dmParent->setString(strParameter, pDictionary->getChannelInDoubt(pMQCFIN->Value));
					break;

					case MQIACF_EVENT_ORIGIN:
						dmParent->setString(strParameter, pDictionary->getEventOriginName(pMQCFIN->Value));
					break;

					default:
						dmParent->setInteger(strParameter,pMQCFIN->Value);
					}

				}
				break;

				case MQCFT_INTEGER_LIST: {
					MQCFIL *pMQCFIL = ptrBuffer->getBuffer<MQCFIL>();

					for(int iIdx = 0; iIdx < pMQCFIL->Count;iIdx++){
						MQLONG iValue = pMQCFIL->Values[iIdx];

						switch(pMQCFIL->Parameter){
							case MQIACF_Q_ATTRS :
							case MQIACF_CHANNEL_ATTRS :
							case MQIACH_CHANNEL_INSTANCE_ATTRS:
							case MQIACF_Q_MGR_ATTRS :
							case MQIACF_Q_MGR_STATUS_ATTRS :
								dmParent->createDataObject(strParameter)->setString(
										pDictionary->getParameterName(iValue));
								break;

							default:
								dmParent->createDataObject(strParameter)->setInteger(iValue);
						}
					}
				}
				break;

				case MQCFT_INTEGER64: {
					MQCFIN64 *pMQCFIN64 = ptrBuffer->getBuffer<MQCFIN64>();
					dmParent->setInteger(strParameter,pMQCFIN64->Value);
				}
				break;

				case MQCFT_INTEGER64_LIST: {
					MQCFIL64 *pMQCFIL64 = ptrBuffer->getBuffer<MQCFIL64>();
					for(int iIdx = 0; iIdx < pMQCFIL64->Count;iIdx++)
					dmParent->setInteger(strParameter,pMQCFIL64->Values[iIdx]);
				}
				break;

				case MQCFT_STRING: {
					MQCFST *pMQCFST = ptrBuffer->getBuffer<MQCFST>();

					String strValue=_GetMQMDValue(pMQCFST->String,pMQCFST->StringLength);

					if(pHeader->iParameter == MQCA_CREATION_TIME ||
					   pHeader->iParameter == MQCAMO_CLOSE_TIME ||
					   pHeader->iParameter == MQCAMO_CONN_TIME  ||
					   pHeader->iParameter == MQCAMO_DISC_TIME  ||
					   pHeader->iParameter == MQCAMO_END_TIME   ||
					   pHeader->iParameter == MQCAMO_OPEN_TIME  ||
					   pHeader->iParameter == MQCAMO_START_TIME ){
						strValue[2]=':';
						strValue[5]=':';
					}

					dmParent->setString(strParameter,strValue);

				}
				break;

				case MQCFT_BYTE_STRING: {
					MQCFBS *pMQCFBS = ptrBuffer->getBuffer<MQCFBS>();
					String strValue;
					MiscTools::BinarytoHex(pMQCFBS->String,pMQCFBS->StringLength,strValue);
					dmParent->setString(strParameter,strValue);
				}
				break;

				case MQCFT_GROUP: {
					MQCFGR *pMQCFGR = ptrBuffer->getBuffer<MQCFGR>();
					readValues(dmParent->createDataObject(strParameter),pMQCFGR->ParameterCount);
				}

				break;

				default:
				IAS_LOG(QS::LogLevel::INSTANCE.isError(),"!! Unknown type:"<<ptrBuffer->getBuffer<MQCFH_Header>()->iType);

			}
		} catch(ItemNotFoundException& e) {
			IAS_LOG(QS::LogLevel::INSTANCE.isError(), "Ignoring PCF value for: "<<strParameter);
		}

	}
}
/*************************************************************************/
}
}
}
}
