/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemFmt-MQPCF/src/qs/fmt/pcf/Writer.cpp 
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

#include "Writer.h"

#include "Dictionary.h"
#include "../PCFFormatter.h"


namespace IAS {
namespace QS {
namespace Fmt {
namespace PCF {

/*************************************************************************/
Writer::Writer(const PCFFormatter*      pFormatter,
			   const DM::DataObject*    dmData,
			   std::ostream&       ostream,
			   QS::API::Attributes *pAttributes):
					   pFormatter(pFormatter),
					   pDictionary(pFormatter->getDictionary()),
					   dmData(dmData),
					   ostream(ostream),
					   pAttributes(pAttributes){
	IAS_TRACER;

	pDataFactory = pFormatter->getDataFactory();

	ptrBuffer=IAS_DFT_FACTORY<Buffer>::Create(512);
}
/*************************************************************************/
Writer::~Writer() throw(){
	IAS_TRACER;
}
/*************************************************************************/

struct MQCFH_Header{
	MQLONG iType;
	MQLONG iLength;
	MQLONG iParameter;
};
/*************************************************************************/
static int getSetProporties(const DM::DataObject* dmData){
	IAS_TRACER;
	const DM::ComplexType* pComplexType = dmData->getType()->asComplexType();
	const DM::PropertyList& lstProperites(pComplexType->getProperties());

	int iCount = 0;

	for(int iIdx = 0; iIdx<lstProperites.getSize(); iIdx++)
		if(lstProperites[iIdx]->isMulti()){
			if(dmData->getList(lstProperites[iIdx]).size())
				iCount++;
		}else {
			if(dmData->isSet(lstProperites[iIdx]))
				iCount++;
		}

	return iCount;
}

/*************************************************************************/
void Writer::writeCFIN(MQLONG iParameterID, MQLONG iValue) {
	IAS_TRACER;

	MQCFIN mqCFIN;
	mqCFIN.Type = MQCFT_INTEGER;
	mqCFIN.Parameter = iParameterID;
	mqCFIN.StrucLength = MQCFIN_STRUC_LENGTH;
	mqCFIN.Value = iValue;

	ostream.write((char*) (&mqCFIN), sizeof(mqCFIN));

}
/*************************************************************************/
void Writer::writeCFST(const DM::Property* pProperty) {
	IAS_TRACER;

	MQLONG iParameter = pDictionary->getParameterID(pProperty->getName());
	String strValue(dmData->getString(pProperty));
	MQLONG iStrLen = strValue.length();

	switch (iParameter) {
		case MQCA_Q_NAME:      iStrLen = MQ_Q_NAME_LENGTH; break;
		case MQCA_Q_MGR_NAME:  iStrLen = MQ_Q_MGR_NAME_LENGTH; 	break;
		case MQCACH_CHANNEL_NAME: iStrLen = MQ_CHANNEL_NAME_LENGTH;	break;
	}

	if (iStrLen + sizeof(MQCFST) > ptrBuffer->getSize())
		ptrBuffer->reserve(iStrLen + sizeof(MQCFST));

	MQCFST* pMQCFST = ptrBuffer->getBuffer<MQCFST>();
	pMQCFST->Type = MQCFT_STRING;
	pMQCFST->Parameter = iParameter;
	pMQCFST->CodedCharSetId = MQCCSI_DEFAULT;
	pMQCFST->StringLength = iStrLen;

	if (MQCFST_STRUC_LENGTH_FIXED + pMQCFST->StringLength > sizeof(MQCFST))
		pMQCFST->StrucLength = MQCFST_STRUC_LENGTH_FIXED
				+ pMQCFST->StringLength;
	else
		pMQCFST->StrucLength = sizeof(MQCFST);

	memset(pMQCFST->String, ' ', iStrLen);
	memcpy(pMQCFST->String, strValue.c_str(), strValue.length());
	ostream.write(ptrBuffer->getBuffer<char>(), pMQCFST->StrucLength);
}
/*************************************************************************/
void Writer::makeCFIL(MQLONG iParameterID,
			const DM::DataObjectList& lstObjects) {

	IAS_TRACER;

	MQCFIL* pMQCFIL = ptrBuffer->getBuffer<MQCFIL>();
	pMQCFIL->Type = MQCFT_INTEGER_LIST;
	pMQCFIL->Parameter = iParameterID;
	pMQCFIL->Count = lstObjects.size();
	pMQCFIL->StrucLength = MQCFIL_STRUC_LENGTH_FIXED
			+ sizeof(MQLONG) * pMQCFIL->Count;

	MQLONG* p = pMQCFIL->Values;

	for (int iIdx = 0; iIdx < lstObjects.size(); iIdx++)
		*p++ = lstObjects.at(iIdx)->toInteger();

	ostream.write(ptrBuffer->getBuffer<char>(), pMQCFIL->StrucLength);
}
/*************************************************************************/
void Writer::makeCFSTL(MQLONG iParameterID,
					   const DM::DataObjectList& lstObjects) {

	IAS_TRACER;

	if (iParameterID == MQIACF_Q_ATTRS ||
		iParameterID == MQIACF_CHANNEL_ATTRS ||
		iParameterID == MQIACH_CHANNEL_INSTANCE_ATTRS ||
		iParameterID == MQIACF_Q_MGR_ATTRS ||
		iParameterID == MQIACF_Q_MGR_STATUS_ATTRS) {

		MQCFIL *pMQCFIL = ptrBuffer->getBuffer<MQCFIL>();
		pMQCFIL->Type = MQCFT_INTEGER_LIST;
		pMQCFIL->Parameter = iParameterID;
		pMQCFIL->Count = lstObjects.size();

		pMQCFIL->StrucLength = MQCFIL_STRUC_LENGTH_FIXED
				+ sizeof(MQLONG) * pMQCFIL->Count;

		MQLONG *p = pMQCFIL->Values;

		for (int iIdx = 0; iIdx < lstObjects.size(); iIdx++) {
			*p++ = pDictionary->getParameterID(lstObjects.at(iIdx)->toString());
			IAS_LOG(QS::LogLevel::INSTANCE.isDetailedInfo(),
					pDictionary->getParameterID(
							lstObjects.at(iIdx)->toString()));
		}

		ostream.write(ptrBuffer->getBuffer<char>(), pMQCFIL->StrucLength);
	}else
		IAS_THROW(InternalException("MQ PCF Writer : Not Implemented feature of String Array."));
}

/*************************************************************************/
void Writer::write(){

	IAS_TRACER;

	MQCFH mqCFH;


	const DM::Type* pType = dmData->getType();

	const DM::ComplexType* pComplexType = dmData->getType()->asComplexType();

	mqCFH.Type = pDictionary->getTypeID(pType->getURI());
	mqCFH.Command = pDictionary->getCommandID(pType->getName());

	const DM::PropertyList& lstProperites(pComplexType->getProperties());

	mqCFH.StrucLength  = MQCFH_STRUC_LENGTH;
	mqCFH.Version      = MQCFH_VERSION_1;
	mqCFH.MsgSeqNumber = MQCFC_LAST;
	mqCFH.Control      = MQCFC_LAST;

	mqCFH.ParameterCount = getSetProporties(dmData);

	ostream.write((char*)&mqCFH,sizeof(mqCFH));

	for(int iIdx = 0; iIdx<lstProperites.getSize(); iIdx++)
	if(dmData->isSet(lstProperites[iIdx])) {


		const DM::Property *pProperty = lstProperites[iIdx];
		MQLONG iParameterID = pDictionary->getParameterID(pProperty->getName());

		if(pProperty->isMulti()) {
			const DM::DataObjectList& lstObjects(dmData->getList(pProperty));
			if(lstObjects.size()) {

				switch(pProperty->getType()->getTypeEnum()) {

					case DM::Type::IntegerType :
						makeCFIL(iParameterID, lstObjects);
					break;

					case DM::Type::TextType :
						makeCFSTL(iParameterID, lstObjects);
					break;

				}
			}
		} else {

			switch(pProperty->getType()->getTypeEnum()) {

				case DM::Type::IntegerType :
					writeCFIN(iParameterID, dmData->getInteger(pProperty));
				break;

				case DM::Type::TextType :

					switch(iParameterID){

						case MQIA_Q_TYPE:
							writeCFIN(iParameterID,pDictionary->getQTypeID(dmData->getString(pProperty)));
						break;

						case MQIACH_CHANNEL_TYPE:
							writeCFIN(iParameterID,pDictionary->getChlTypeID(dmData->getString(pProperty)));
						break;

						case MQIACH_CHANNEL_STATUS:
							writeCFIN(iParameterID,pDictionary->getChlStatusID(dmData->getString(pProperty)));
						break;

						case MQIACF_MODE:
							writeCFIN(iParameterID,pDictionary->getChannelStopModeID(dmData->getString(pProperty)));
						break;

						case MQIACH_IN_DOUBT:
							writeCFIN(iParameterID,pDictionary->getChannelInDoubtID(dmData->getString(pProperty)));
						break;

						default:
						writeCFST(pProperty);
					}
					break;

				default:
					IAS_THROW(InternalException("Mapping XSD->PCF type not implemented."));
			}

		}
	}

	ostream.flush();
}
/*************************************************************************/
void Writer::writeValues(const DM::DataObject* dmParent){

	IAS_TRACER;


}
/*************************************************************************/
}
}
}
}
