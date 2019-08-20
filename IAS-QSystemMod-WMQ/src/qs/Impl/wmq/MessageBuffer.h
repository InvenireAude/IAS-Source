/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-WMQ/src/qs/Impl/wmq/MessageBuffer.h 
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
#ifndef _IAS_QS_WMQ_MessageBuffer_H_
#define _IAS_QS_WMQ_MessageBuffer_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace WMQ {

class Message;

/*************************************************************************/
/** The MessageBuffer class.
 *
 */
class MessageBuffer : public Buffer {
public:

	MessageBuffer(Message *pWMQMessage);
	//virtual
	~MessageBuffer();

	size_t getDataLen()const{ return iDataLen; };

	bool isRFH1()const{ return bIsRFH1; };

protected:

	bool bIsRFH1;

	size_t iDataLen;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_WMQ_MessageBuffer_H_ */
