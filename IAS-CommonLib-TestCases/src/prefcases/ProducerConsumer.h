/*
 * File: ProducerConsumer.h
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


#ifndef _IAS_PerfCases_ProducerConsumer_H_
#define _IAS_PerfCases_ProducerConsumer_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace PerfCases {

/*************************************************************************/
/** The ProducerConsumer class.
 *
 */
class ProducerConsumer {
public:

	virtual ~ProducerConsumer() throw();


  static void Run(int iNumWriters, int iNumReaders, int iBufferLen, bool bShared);

protected:
	ProducerConsumer(int iNumWriters, int iNumReaders, int iBufferLen, bool bShared);

  void start();

  struct SomeData{
    size_t iSeq;
    TimeSample tsStart;
    //TimeSample tsTwo;
    //char  _padding[16];
  };

  typedef ProducerConsumerQueue<SomeData> Queue;
  IAS_DFT_STATIC_FACTORY<Queue>::PtrHolder ptrQueue;

  class Producer : public Thread, public Runnable {
    public:
      Producer(ProducerConsumer *pCase):pCase(pCase),Thread(this){};

      void run();
    protected:
      ProducerConsumer *pCase;
  };

  class Consumer : public Thread, public Runnable {
    public:
      Consumer(ProducerConsumer *pCase):pCase(pCase),Thread(this){};

      void run();
    protected:
      ProducerConsumer *pCase;
  };

  typedef IAS_DFT_FACTORY<Thread>::PtrHoldersCollection ThreadsCollection;
  ThreadsCollection phcThreads;

  int iNumWriters;
  int iNumReaders;
  int iBufferLen;
  bool bShared;

  long iCountDownProduced;
  long iCountDownReceived;

  Mutex mutex;

  TimeSamplesResults tsr;

  bool handlePut();
  bool handleGet();

	friend class Factory<ProducerConsumer>;
};

/*************************************************************************/
}
}

#endif /* _IAS_PerfCases_ProducerConsumer_H_ */
