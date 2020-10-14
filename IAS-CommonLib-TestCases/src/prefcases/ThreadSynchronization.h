/*
 * File: ThreadSynchronization.h
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


#ifndef _IAS_PerfCases_ThreadSynchronization_H_
#define _IAS_PerfCases_ThreadSynchronization_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace PerfCases {

/*************************************************************************/
/** The ThreadSynchronization class.
 *
 */
class ThreadSynchronization {
public:

	virtual ~ThreadSynchronization() throw();


  static void Run(int iNumWorkers);

protected:
	ThreadSynchronization(int iNumWorkers);

  void start();

  class Worker : public Thread, public Runnable {
    public:
      Worker(ThreadSynchronization *pCase):pCase(pCase),Thread(this){};

      void run();
    protected:
      ThreadSynchronization *pCase;
  };



  typedef IAS_DFT_FACTORY<Thread>::PtrHoldersCollection ThreadsCollection;
  ThreadsCollection phcThreads;

  int iNumWorkers;
  volatile long iCountDown;

  Mutex mutex;
  Condition cnd;
  TimeSamplesResults tsr;
  TimeSample ts;

  bool handle();

	friend class Factory<ThreadSynchronization>;
};

/*************************************************************************/
}
}

#endif /* _IAS_PerfCases_ThreadSynchronization_H_ */
