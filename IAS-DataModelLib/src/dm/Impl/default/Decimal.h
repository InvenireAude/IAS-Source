/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Decimal.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Decimal_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Decimal_46H

#include "../../../dm/default/Decimal.h"

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectDecimal.h"
#include "../../../dm/Impl/TypeDecimal.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class DecimalType; }
/*************************************************************************/
class Decimal:
	public ::IAS::DM::Impl::DataObjectDecimal,
	public virtual ::IAS::DM::Default::Decimal{

public:

	virtual ~Decimal() throw();

	virtual ::IAS::DM::Default::Decimal* duplicateDecimal() const;
protected:
	Decimal(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<Decimal>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<Decimal>::RefCountingPtr DecimalPtr;
/*************************************************************************/
class DecimalList : public ::IAS::DM::Default::Ext::DecimalList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    DecimalList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::Decimal* pValue);
	virtual ::IAS::DM::Default::Decimal* getDataObject(int iIdx);

	virtual void add(const ::IAS::Decimal& aValue);
	virtual ::IAS::Decimal at(int iIdx)const;
	virtual int size()const;

	friend class ::IAS::Factory<DecimalList>;
};
/*************************************************************************/

 class DecimalType :
	public ::IAS::DM::Impl::TypeDecimal,
	public virtual ::IAS::DM::Default::Ext::DecimalType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<DecimalType>, DecimalType >{

public:

	virtual ~DecimalType() throw();

	virtual ::IAS::DM::Default::Decimal* createDecimal() const;
	virtual ::IAS::DM::Default::Decimal* createDecimal(const ::IAS::Decimal& aValue) const;

	virtual ::IAS::DM::Default::Decimal* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::Decimal* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static Decimal* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const Decimal* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	DecimalType();
	DecimalType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	Decimal* createDecimalImpl() const;

	friend class ::IAS::Factory<DecimalType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
