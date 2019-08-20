/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemFmt-MQPCF/src/qs/fmt/pcf/Dictionary.h 
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
#ifndef _IAS_QS_Fmt_PCF_Dictionary_H_
#define _IAS_QS_Fmt_PCF_Dictionary_H_

#include <commonlib/commonlib.h>
#include <cmqc.h>
#include <cmqcfc.h>

namespace IAS {
namespace QS {
namespace Fmt {
namespace PCF {

/*************************************************************************/
/** The Dictionary class.
 *
 */
class Dictionary {
public:

	virtual ~Dictionary() throw();

	const String& getTypeNS(MQLONG iType)const;
	const String& getQTypeName(MQLONG iType)const;
	const String& getChlTypeName(MQLONG iType)const;
	const String& getChlStatusName(MQLONG iType)const;

	const String& getParameterName(MQLONG iParameter)const;
	const String& getCommandName(MQLONG iCommand)const;

	const MQLONG getTypeID(const String& strType)const;
	const MQLONG getQTypeID(const String& strName)const;
	const MQLONG getChlTypeID(const String& strName)const;
	const MQLONG getChlStatusID(const String& strName)const;

	const MQLONG getParameterID(const String& strCommand)const;
	const MQLONG getCommandID(const String& strParameter)const;

	const String& getMQSCName(MQLONG iCommand)const;
	const String& getEventOriginName(MQLONG iOrigin)const;


	const String& getCompCode(MQLONG iCompCode)const;
	const String& getReason(MQLONG iReason)const;

	const String& getChannelStopMode(MQLONG iStatus)const;
	MQLONG        getChannelStopModeID(const String& strStatus)const;

	const String& getChannelInDoubt(MQLONG iStatus)const;
	MQLONG        getChannelInDoubtID(const String& strStatus)const;

protected:
	Dictionary();

	typedef std::map<MQLONG, String> HashMap;
	typedef std::map<String,MQLONG>  HashMapR;

	HashMap  hmCommandID2Name;
	HashMapR hmCommandName2ID;

	HashMap  hmParameterID2Name;
	HashMapR hmParameterName2ID;

	HashMap  hmType2NS;
	HashMapR hmNS2Type;

	HashMap  hmQType2Name;
	HashMapR hmName2QType;

	HashMap  hmChlType2Name;
	HashMapR hmName2ChlType;

	HashMap  hmChlStatus2Name;
	HashMapR hmName2ChlStatus;

	HashMap hmMQSCNames;
	HashMap hmEventOriginName;

	HashMap hmReasonName;
	HashMap hmCompCodeName;

	void initializeCommandID2Name();
	void initializeParameterID2Name();
	void initializeType2NS();
	void initializeQType2Name();
	void initializeChlType2Name();
	void initializeChlStatus2Name();
	void initializeMQSCNames();
	void initializeEventOriginName();
	void initializeReasonName();
	void initializeCompCodeName();

	friend class Factory<Dictionary>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Fmt_PCF_Dictionary_H_ */
