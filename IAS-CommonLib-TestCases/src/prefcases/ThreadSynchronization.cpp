/*
 * File: ThreadSynchronization.cpp
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

#include "ThreadSynchronization.h"

#include <unistd.h>

namespace IAS {
namespace PerfCases {

/*************************************************************************/
ThreadSynchronization::ThreadSynchronization(int iNumWorkers):
  iNumWorkers(iNumWorkers),
  iCountDown(10000),
  mutex(true),
  cnd(true),
  tsr(TimeSamplesResults::COF_MicroSec){
	IAS_TRACER;

 for(int i = 0;i < iNumWorkers; i++){
    phcThreads.addPointer(IAS_DFT_FACTORY<Worker>::Create(this));
  }

}
/*************************************************************************/
ThreadSynchronization::~ThreadSynchronization() throw(){
	IAS_TRACER;

 std::cout<<"ThreadSynchronization: ["<<iNumWorkers<<"]"<<tsr<<std::endl;

 for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->stop();
  }

  for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->join();
  }
}
/*************************************************************************/
void ThreadSynchronization::start(){

  for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->start();
  }

  while( !SYS::Signal::GetInstance()->isStopping() && iCountDown){
    usleep(1);
    Thread::Cancellation ca(true);
    Mutex::Locker locker(mutex);
    iCountDown--;
    //if(iCountDown % 10 == 0)
    //  std::cerr<<".";
    ts.start();
    cnd.signal();
  }
  cnd.broadcast();
  for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->join();
  }
}
/*************************************************************************/
bool ThreadSynchronization::handle(){

  long iValue;

  Mutex::Locker locker(mutex);
  iValue = iCountDown;

  while(iCountDown && iValue == iCountDown){
    Thread::Cancellation ca(true);
    mutex.wait(cnd);
  }

  tsr.addSample(ts);

  return iCountDown > 0;
}
/*************************************************************************/
void ThreadSynchronization::Worker::run(){
	IAS_TRACER;

  SYS::Signal::ThreadRegistration threadRegistration;

  while( !SYS::Signal::GetInstance()->isStopping() && pCase->handle()){
  }

}
/*************************************************************************/
void ThreadSynchronization::Run(int iNumWorkers){
  IAS_TRACER;

  IAS_DFT_FACTORY<ThreadSynchronization>::PtrHolder ptrThreadSynchronization(
    IAS_DFT_FACTORY<ThreadSynchronization>::Create(iNumWorkers)
  );

  ptrThreadSynchronization->start();
}

}
}
