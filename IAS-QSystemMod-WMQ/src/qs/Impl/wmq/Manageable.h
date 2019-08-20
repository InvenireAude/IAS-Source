/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/Manageable.h 
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
#ifndef _IAS_QS_WMQ_Manageable_H_
#define _IAS_QS_WMQ_Manageable_H_

#include <commonlib/commonlib.h>

#include <qs/api.h>
#include <cmqc.h>

namespace IAS {
namespace QS {
namespace WMQ {

class Session;

/*************************************************************************/
/** The Manageable class.
 *
 */
class Manageable {
public:

	virtual ~Manageable() throw();


	static const String CJMSDstAttr;
	static const String CJMSRtoAttr;

protected:
	Manageable(Session* pSession);

	inline Session* getSession() {return pSession;}
	inline const Session* getSession()const{return pSession;}

	void updateID(unsigned char* sId, const String& strValue)const;
	void updateMDPMO(MQMD& md, MQPMO& pmo, const ::IAS::QS::API::Attributes* pAttributes)const;


private:
	Session* pSession;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Manageable_H_ */
