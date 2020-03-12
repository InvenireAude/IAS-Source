/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Long.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Long_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Long_46H

#include <dm/default/Long.h>

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectLong.h"
#include "../../../dm/Impl/TypeLong.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class LongType; }
/*************************************************************************/
class Long:
	public ::IAS::DM::Impl::DataObjectLong,
	public virtual ::IAS::DM::Default::Long{

public:

	virtual ~Long() throw();

	virtual ::IAS::DM::Default::Long* duplicateLong() const;
protected:
	Long(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<Long>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<Long>::RefCountingPtr LongPtr;
/*************************************************************************/
class LongList : public ::IAS::DM::Default::Ext::LongList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    LongList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::Long* pValue);
	virtual ::IAS::DM::Default::Long* getDataObject(int iIdx);

	virtual void add(const ::IAS::Long aValue);
	virtual ::IAS::Long at(int iIdx)const;
	virtual int size()const;

	friend class ::IAS::Factory<LongList>;
};
/*************************************************************************/

 class LongType :
	public ::IAS::DM::Impl::TypeLong,
	public virtual ::IAS::DM::Default::Ext::LongType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<LongType>, LongType >{

public:

	virtual ~LongType() throw();

	virtual ::IAS::DM::Default::Long* createLong() const;
	virtual ::IAS::DM::Default::Long* createLong(const ::IAS::Long aValue) const;

	virtual ::IAS::DM::Default::Long* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::Long* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static Long* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const Long* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	LongType();
	LongType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	Long* createLongImpl() const;

	friend class ::IAS::Factory<LongType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
