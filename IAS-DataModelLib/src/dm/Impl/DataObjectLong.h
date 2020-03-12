/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectLong.h
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
#ifndef _IAS_DM_Impl_DataObjectLong_H_
#define _IAS_DM_Impl_DataObjectLong_H_

#include "../../dm/Impl/DataObjectBasic.h"

namespace IAS {
namespace DM {
namespace Impl {

class Type;

/*************************************************************************/
class DataObjectLong : public ::IAS::DM::Impl::DataObjectBasic {
public:

	virtual ~DataObjectLong() throw();


	virtual void setString(const String& strValue);
	virtual void setInteger(int iValue);
	virtual void setBoolean(bool bValue);
	virtual void setLong(Long fValue);
  virtual void setDecimal(const Decimal& dValue);

	virtual void setDataObject(const IAS::DM::DataObject* pDataObject);


	virtual String toString()const;
	virtual bool    toBoolean()const;
	virtual int     toInteger()const;
	virtual Long    toLong()const;
  virtual Decimal toDecimal()const;

	virtual bool    equals(const IAS::DM::DataObject* dmValue)const;

protected:
	DataObjectLong(const Type *pType);


	Long fValue;

	friend class ::IAS::Factory<DataObjectLong>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_DATAOBJECTFLOAT_H_ */
