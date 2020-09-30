/*
 * File: MBusRepeater.h
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


#ifndef _IAS_Exe_Net_MBusRepeater_H_
#define _IAS_Exe_Net_MBusRepeater_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace Exe {
namespace Net {

/*************************************************************************/
/** The MBusRepeater class.
 *
 */
class MBusRepeater {
public:

	virtual ~MBusRepeater() throw();

  void start(unsigned int iNumThreads);

protected:
	MBusRepeater(const IAS::Net::MCast::EndPoint& endPoint,
               IAS::Net::MCast::SequencedBase::IndexType iInputBufferSize,
               IAS::Net::MCast::SequencedBase::IndexType iOutputBufferSize,
               IAS::Net::MCast::SequencedBase::PacketSizeType iMaxPacketSize);

	MBusRepeater(const IAS::Net::MCast::EndPoint& endPoint,
               IAS::Net::MCast::SequencedBase::IndexType iInputBufferSize,
               IAS::Net::MCast::SequencedBase::IndexType iOutputBufferSize,
               IAS::Net::MCast::SequencedBase::PacketSizeType iMaxPacketSize,
               IAS::Storage::Dump::FileSet* pDumpFileSet);

  const IAS::Net::MCast::EndPoint& endPoint;

  class Worker : public Thread, public Runnable {

    public:
      Worker(MBusRepeater *pRepeater):
      Thread(this),
      pRepeater(pRepeater){
        start();
      };

      virtual void run();

      protected:

        MBusRepeater *pRepeater;
  };

  typedef IAS_DFT_FACTORY<Worker>::PtrHoldersCollection WorkerCollection;
  WorkerCollection                                      phcWorkers;

	friend class Factory<MBusRepeater>;

  IAS_DFT_FACTORY<IAS::Net::MCast::SequencedInput>::PtrHolder ptrInput;
  IAS_DFT_FACTORY<IAS::Net::MCast::SequencedOutput>::PtrHolder ptrOutput;

  IAS::Net::MCast::SequencedBase::IndexType iInputBufferSize;
  IAS::Net::MCast::SequencedBase::IndexType iOutputBufferSize;
  IAS::Net::MCast::SequencedBase::PacketSizeType iMaxPacketSize;

  Allocator* pAllocator;
  IAS::Storage::Dump::FileSet* pDumpFileSet;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Exe_Net_MBusRepeater_H_ */
