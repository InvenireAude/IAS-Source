/*
 * File: IAS-DataModelLib/src/dm/Impl/TypeLong.h
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
#ifndef _IAS_DM_Impl_TypeLong_H_
#define _IAS_DM_Impl_TypeLong_H_

#include "../../dm/Impl/TypeBasic.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
class TypeLong : public ::IAS::DM::Impl::TypeBasic {
public:

	virtual ~TypeLong() throw();

	virtual ::IAS::DM::Type::Types getTypeEnum() const;

protected:
	TypeLong(const String& strURI,
			  const String& strName,
			  const ::IAS::DM::Type    *pBaseType);


	virtual DataObject* createDataObjectImpl() const;

	friend class ::IAS::Factory<TypeLong>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_TYPEFLOAT_H_ */
