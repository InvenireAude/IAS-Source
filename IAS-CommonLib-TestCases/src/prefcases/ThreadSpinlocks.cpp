/*
 * File: ThreadSpinlocks.cpp
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

#include "ThreadSpinlocks.h"

#include <sched.h>
#include <unistd.h>
#include <pthread.h>

namespace IAS {
namespace PerfCases {

static void _setaffinity(bool bMain){
  cpu_set_t cpuset;
  pthread_t thread;

  thread = pthread_self();

  /* Set affinity mask to include CPUs 0 to 7 */

  CPU_ZERO(&cpuset);
  if(bMain){
     CPU_SET(0, &cpuset);
  }else{
    for (int j = 1; j < 8; j++)
      CPU_SET(j, &cpuset);
  }

  if (pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset) != 0)
    IAS_THROW(SystemException("pthread_setaffinity_np"));

}
/*************************************************************************/
ThreadSpinlocks::ThreadSpinlocks(int iNumWorkers):
  iNumWorkers(iNumWorkers),
  iCountDown(10000),
  mutex(true),
  tsr(TimeSamplesResults::COF_MicroSec){
	IAS_TRACER;

 for(int i = 0;i < iNumWorkers; i++){
    phcThreads.addPointer(IAS_DFT_FACTORY<Worker>::Create(this));
  }

}
/*************************************************************************/
ThreadSpinlocks::~ThreadSpinlocks() throw(){
	IAS_TRACER;

 std::cout<<"ThreadSpinlocks: ["<<iNumWorkers<<"]"<<tsr<<std::endl;

 for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->stop();
  }

  for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->join();
  }
}
/*************************************************************************/
static inline void _wait(Mutex& mutex){
  while(!mutex.trylock());
}
/*************************************************************************/
void ThreadSpinlocks::start(){

  for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->start();
  }

  _setaffinity(true);

  while( !SYS::Signal::GetInstance()->isStopping() && iCountDown){
    usleep(100);
    Thread::Cancellation ca(true);
    _wait(mutex);
    iCountDown--;
    bFirst = true;
    // if(iCountDown % 10 == 0)
    //   std::cerr<<".";
    ts.start();
    mutex.unlock();
  }

  for(ThreadsCollection::iterator it = phcThreads.begin(); it != phcThreads.end(); it++){
    (*it)->join();
  }
}
/*************************************************************************/
bool ThreadSpinlocks::handle(){

  long iValue;

  _wait(mutex);
  iValue = iCountDown;
  mutex.unlock();

  bool bWait = true;

  while(bWait){
    Thread::Cancellation ca(true);
    //_wait(mutex);
    if(mutex.trylock()){
      bWait = iCountDown && iValue == iCountDown && !bFirst;
      if(bWait){
        mutex.unlock();
        sched_yield();
        //usleep(1);
      }
    }else{
      sched_yield();
    }
  }
  bFirst = false;
  tsr.addSample(ts);
  iValue = iCountDown;
  mutex.unlock();

  return iValue > 0;
}
/*************************************************************************/
void ThreadSpinlocks::Worker::run(){
	IAS_TRACER;

  SYS::Signal::ThreadRegistration threadRegistration;
  _setaffinity(false);

  while( !SYS::Signal::GetInstance()->isStopping() && pCase->handle()){
  }

}
/*************************************************************************/
void ThreadSpinlocks::Run(int iNumWorkers){
  IAS_TRACER;

  IAS_DFT_FACTORY<ThreadSpinlocks>::PtrHolder ptrThreadSpinlocks(
    IAS_DFT_FACTORY<ThreadSpinlocks>::Create(iNumWorkers)
  );

  ptrThreadSpinlocks->start();
}

}
}
