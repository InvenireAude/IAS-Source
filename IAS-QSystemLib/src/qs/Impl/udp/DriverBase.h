/*
 * MBus: IAS-QSystemLib/src/qs/Impl/sdf/file/DriverBase.h
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
#ifndef _IAS_QS_UDP_DriverBase_H_
#define _IAS_QS_UDP_DriverBase_H_

#include <commonlib/commonlib.h>
#include <qs/api.h>

namespace IAS {
namespace QS {
namespace UDP {

/*************************************************************************/
/** The DriverBase class.
 *
 */
class DriverBase {
public:

	virtual ~DriverBase() throw();


protected:
	DriverBase(const API::Destination& destination);

  API::Destination   destination;
  String             strTopic;

  Allocator*         pAllocator;

  static const int   CMaxTopicLen = 128;

  class PtrDataHolder{
  public:
      PtrDataHolder(void* pData, size_t iDataLeft, DriverBase* pDriverBase):
        pData(reinterpret_cast<char*>(pData)),
        iDataLen(iDataLeft),
        pDriverBase(pDriverBase){
          pCursor = this->pData;
        }

      ~PtrDataHolder(){
        if(pData)
          pDriverBase->pAllocator->free(pData);
      }

      operator char* (){
        return pCursor;
      }

      operator const char* ()const{
        return reinterpret_cast<const char*>(pCursor);
      }

      void setDataLeft(size_t iDataLen){
        this->iDataLen = iDataLen;
        pCursor = pData;
      }

      size_t getDataLeft()const{
        return iDataLen;
      }

      PtrDataHolder& operator+=(int iSkip){

        if(iDataLen < iSkip)
          IAS_THROW(InternalException("UDP::DriverBase(), iDataLen < iSkip"));

        iDataLen -= iSkip;
        pCursor += iSkip;

        return *this;
      };

  protected:

    char*  pData;
    char*  pCursor;
    size_t iDataLen;

    DriverBase* pDriverBase;
  };

	friend class Factory<DriverBase>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_UDP_DriverBase_H_ */
