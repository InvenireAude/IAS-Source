/*
 * File: ProducerConsumer.cpp
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

#include "ProducerConsumer.h"


namespace IAS {
namespace PerfCases {

/*************************************************************************/
ProducerConsumer::ProducerConsumer(int iNumWriters, int iNumReaders, int iBufferLen, bool bShared):
  iNumWriters(iNumWriters),
  iNumReaders(iNumReaders),
  iBufferLen(iBufferLen),
  bShared(bShared),
  tsr(TimeSamplesResults::COF_MicroSec),
  iCountDownProduced(1000000),
  iCountDownReceived(1000000){
	IAS_TRACER;

  ptrQueue = IAS_DFT_FACTORY<Queue>::Create(iBufferLen);

  for(int i = 0;i < iNumWriters; i++){
    phcThreads.addPointer(IAS_DFT_FACTORY<Producer>::Create(this));
  }

  for(int i = 0;i < iNumReaders; i++){
    phcThreads.addPointer(IAS_DFT_FACTORY<Consumer>::Create(this));
  }


}
/*************************************************************************/
ProducerConsumer::~ProducerConsumer() throw(){
	IAS_TRACER;

 std::cout<<"ProducerConsumer: ["<<iNumWriters<<", "<<iNumReaders<<", "<<iBufferLen<<"]"<<tsr<<std::endl;

 for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->stop();
  }

  for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->join();
  }
}
/*************************************************************************/
void ProducerConsumer::start(){

  for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->start();
  }

  for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->join();
  }
}
/*************************************************************************/
bool ProducerConsumer::handlePut(){


  {
    Mutex::Locker locker(mutex);
    if(iCountDownProduced == 0)
      return false;
    iCountDownProduced--;
  }

  SomeData data;
  data.tsStart.start();
  ptrQueue->put(data);

  return true;
}
/*************************************************************************/
bool ProducerConsumer::handleGet(){

  {
    Mutex::Locker locker(mutex);
    if(iCountDownReceived == 0)
      return false;
    iCountDownReceived--;
  }

  SomeData data(ptrQueue->get());
  Mutex::Locker locker(mutex);
  tsr.addSample(data.tsStart);
  return iCountDownReceived > 0;
}
/*************************************************************************/
void ProducerConsumer::Producer::run(){
	IAS_TRACER;

  SYS::Signal::ThreadRegistration threadRegistration;

  while( !SYS::Signal::GetInstance()->isStopping() && pCase->handlePut()){
  }

}
/*************************************************************************/
void ProducerConsumer::Consumer::run(){
	IAS_TRACER;

  SYS::Signal::ThreadRegistration threadRegistration;

    while( !SYS::Signal::GetInstance()->isStopping() && pCase->handleGet()){
    }
}
/*************************************************************************/
void ProducerConsumer::Run(int iNumWriters, int iNumReaders, int iBufferLen, bool bShared){
  IAS_TRACER;

  IAS_DFT_FACTORY<ProducerConsumer>::PtrHolder ptrProducerConsumer(
    IAS_DFT_FACTORY<ProducerConsumer>::Create(iNumWriters, iNumReaders, iBufferLen, bShared)
  );

  ptrProducerConsumer->start();
}

}
}
