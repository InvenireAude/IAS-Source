/*
 * File: IAS-CommonLib/src/commonlib/types/DoubleLinkedList.h
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
#ifndef _IAS_Types_DoubleLinkedList_H_
#define _IAS_Types_DoubleLinkedList_H_

#include <commonlib/types.h>

namespace IAS {

/*************************************************************************/
/** The DoubleLinkedList class.
 *
 */
template<class C>
class DoubleLinkedList {

public:

  DoubleLinkedList():
    pPrev(this),
    pNext(this){}

 ~DoubleLinkedList(){
    if(pNext != this)
      this->pNext->pPrev = this->pPrev;

    if(pPrev != this)
      this->pPrev->pNext = this->pNext;
 }

  void append(C *pNext){
    pNext->pNext = this->pNext;
    this->pNext->pPrev = pPrev;
    this->pNext = pNext;
    pNext->pPrev = this;
  }

  void prepend(C *pPrev){
    pPrev->pPrev = this->pPrev;
    this->pPrev->pNext = pPrev;
    this->pPrev = pPrev;
    pPrev->pNext = this;
  }

  void detach(){

    if(pNext != this)
      this->pNext->pPrev = this->pPrev;

    if(pPrev != this)
      this->pPrev->pNext = this->pNext;

    this->pPrev = this->pNext = this;
  }

  inline C* getPrev(){
    return pPrev;
  }

  inline C* getNext(){
    return *pNext;
  }

 private:

  DoubleLinkedList<C> *pPrev;
  DoubleLinkedList<C> *pNext;
};

/*************************************************************************/

}

#endif /* _IAS_Types_DoubleLinkedList_H_ */
