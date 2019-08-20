/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/LobOpener.h 
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
#ifndef _IAS_DS_Oracle_LobOpener_H_
#define _IAS_DS_Oracle_LobOpener_H_

#include <oci.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
class Session;
namespace Tools {

class Connection;

/*************************************************************************/
/** The LobOpener class.
 *
 */
class LobOpener {

public:


	LobOpener(Session* pSession, OCILobLocator* pOCILobLocator, ub1 iMode);
	virtual ~LobOpener() throw();

	operator OCILobLocator*(){ return pOCILobLocator; }

	OCILobLocator* pOCILobLocator;
	Session*       pSession;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_DS_Oracle_LobOpener_H_ */
