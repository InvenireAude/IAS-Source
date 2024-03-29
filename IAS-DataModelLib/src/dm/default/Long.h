/*
 * File: IAS-DataModelLib/src/dm/default/Long.h
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
#ifndef _IAS_DM_Gen_Long_H_
#define _IAS_DM_Gen_Long_H_

#include <commonlib/commonlib.h>
#include "../../dm/DataObject.h"

namespace IAS{
namespace DM{
namespace Default{

class Long : public virtual ::IAS::DM::DataObject {
  public:
	virtual Long* duplicateLong() const = 0;
};

namespace Ext{

/*************************************************************************/
typedef Impl::ModelAllocator<Long>::RefCountingPtr LongPtr;
/*************************************************************************/
class LongList {
	public:
	virtual ~LongList(){};
	virtual void addDataObject(Long* pValue) = 0;
	virtual Long* getDataObject(int iIdx) = 0;
	virtual void add(::IAS::Long aValue)=0;
	virtual ::IAS::Long at(int iIdx)const=0;
	virtual int size()const=0;
};
/*************************************************************************/
class LongType {
	public:
	virtual ~LongType(){};
	virtual Long* cast(::IAS::DM::DataObject* pDataObject) const = 0;
	virtual const Long* cast(const ::IAS::DM::DataObject* pDataObject) const = 0;

	virtual Long* createLong() const=0;
	virtual ::IAS::DM::Default::Long* createLong(::IAS::Long aValue) const = 0;
};

}

}
}
}

#endif
