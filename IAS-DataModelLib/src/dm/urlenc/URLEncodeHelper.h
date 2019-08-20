/*
 * File: IAS-DataModelLib/src/dm/urlenc/URLEncodeHelper.h
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _IAS_DM_URLENC_URLENCODEHELPER_H_
#define _IAS_DM_URLENC_URLENCODEHELPER_H_

#include <commonlib/commonlib.h>

#include "../../dm/DataObject.h"

namespace IAS {
namespace DM {
class DataFactory;
class DataObject;
namespace URLEnc {

/*************************************************************************/
/** The class. */
 class URLEncodeHelper {
public:

	virtual ~URLEncodeHelper() throw();

	inline const ::IAS::DM::DataFactory *getDataFactory() { return pDataFactory;};

	void save(std::ostream& os,
			  const ::IAS::DM::DataObject *pDataObject,
			  bool  bXSIType = true);

	DM::DataObjectPtr load(std::istream& is, const DM::Type* pTypeHint=NULL);

protected:
	URLEncodeHelper(const ::IAS::DM::DataFactory *pDataFactory);

	const ::IAS::DM::DataFactory *pDataFactory;

  static const String C_MockURLPrefix;

	friend class ::IAS::Factory<URLEncodeHelper>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_URLENC_URLENCODEHELPER_H_ */
