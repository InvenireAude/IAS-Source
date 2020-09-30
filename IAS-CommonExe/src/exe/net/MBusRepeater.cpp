/*
 * File: MBusRepeater.cpp
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

#include "MBusRepeater.h"

#include <unistd.h>

namespace IAS {
namespace Exe {
namespace Net {
/*************************************************************************/
class DataHolder{
  public:
      inline DataHolder(void* pData, Allocator* pAllocator):
        pData(pData),
        pAllocator(pAllocator){}

      inline ~DataHolder(){
        if(pData)
          pAllocator->free(pData);
      }

      inline operator void* (){
        return pData;
      }

      inline void* pass(){
        void* t = pData;
        pData = 0;
        return t;
      }
  protected:

    void       *pData;
    Allocator  *pAllocator;
  };
/*************************************************************************/
MBusRepeater::MBusRepeater(const IAS::Net::MCast::EndPoint& endPoint,
               IAS::Net::MCast::SequencedBase::IndexType iInputBufferSize,
               IAS::Net::MCast::SequencedBase::IndexType iOutputBufferSize,
               IAS::Net::MCast::SequencedBase::PacketSizeType iMaxPacketSize):
  endPoint(endPoint),
  iInputBufferSize(iInputBufferSize),
  iOutputBufferSize(iOutputBufferSize),
  iMaxPacketSize(iMaxPacketSize),
  pAllocator(MemoryManager::GetAllocator()){

	IAS_TRACER;

  ptrInput = IAS_DFT_FACTORY<IAS::Net::MCast::SequencedInput>::Create(
    endPoint, iInputBufferSize, iMaxPacketSize, MemoryManager::GetAllocator());

  ptrOutput = IAS_DFT_FACTORY<IAS::Net::MCast::SequencedOutput>::Create(
    endPoint, iOutputBufferSize, iMaxPacketSize, pAllocator);

  ptrInput->setup();
  ptrOutput->setup();
  ptrOutput->setMute(true);
  ptrOutput->startRepeater();
}
/*************************************************************************/
MBusRepeater::MBusRepeater(const IAS::Net::MCast::EndPoint& endPoint,
               IAS::Net::MCast::SequencedBase::IndexType iInputBufferSize,
               IAS::Net::MCast::SequencedBase::IndexType iOutputBufferSize,
               IAS::Net::MCast::SequencedBase::PacketSizeType iMaxPacketSize,
               IAS::Storage::Dump::FileSet* pDumpFileSet):
  endPoint(endPoint),
  iInputBufferSize(iInputBufferSize),
  iOutputBufferSize(iOutputBufferSize),
  iMaxPacketSize(iMaxPacketSize),
  pAllocator(pDumpFileSet),
  pDumpFileSet(pDumpFileSet){

  ptrInput = IAS_DFT_FACTORY<IAS::Net::MCast::SequencedInput>::Create(
    endPoint, iInputBufferSize, iMaxPacketSize, MemoryManager::GetAllocator());

  ptrOutput = IAS_DFT_FACTORY<IAS::Net::MCast::SequencedOutput>::Create(
    endPoint, iOutputBufferSize, iMaxPacketSize, pAllocator);

  ptrOutput->setup();
  ptrOutput->setMute(true);

  pDumpFileSet->openBackLog();

  IAS::Net::MCast::SequencedBase::IndexType iNextSequence = 0;

  while(pDumpFileSet->hasMoreBackLogData()){

     Storage::Dump::File::SizeType iDataLen;

     void *pData = pDumpFileSet->nextFromBackLog(iDataLen);

     //TODO do something with this hack & look up.
     iNextSequence = *(reinterpret_cast<const Storage::Dump::File::IndexType*>(
				              reinterpret_cast<const char*>(pData) + iDataLen - sizeof(IAS::Net::MCast::SequencedBase::IndexType))) + 1;

     ptrOutput->send(pData, iDataLen - sizeof(IAS::Net::MCast::SequencedBase::IndexType));

     IAS_LOG(LogLevel::INSTANCE.isInfo(),"Reading backlog, size:"<<iDataLen<<", seq: "<<iNextSequence);
  }

  ptrInput->setup(iNextSequence);
  ptrOutput->startRepeater();

}
/*************************************************************************/
MBusRepeater::~MBusRepeater() throw(){
	IAS_TRACER;

  for(WorkerCollection::iterator it = phcWorkers.begin(); it != phcWorkers.end(); it++){
    (*it)->stop();
  }

  for(WorkerCollection::iterator it = phcWorkers.begin(); it != phcWorkers.end(); it++){
    (*it)->join();
  }

}
/*************************************************************************/
void MBusRepeater::start(unsigned int iNumThreads){



  while(iNumThreads--){
    phcWorkers.addPointer(IAS_DFT_FACTORY<Worker>::Create(this));
  }

//  while(! SYS::Signal::GetInstance()->isStopping() ){
    Thread::Cancellation ca(true);
    sleep(30);
 //}

}
/*************************************************************************/
void MBusRepeater::Worker::run(){

  while(! SYS::Signal::GetInstance()->isStopping() ){

    IAS::Net::MCast::SequencedBase::PacketSizeType iDataLen;
    DataHolder dataInput(pRepeater->ptrInput->receive(iDataLen), MemoryManager::GetAllocator());

    DataHolder dataOutput(pRepeater->pAllocator->allocate(
        iDataLen + sizeof(IAS::Net::MCast::SequencedBase::IndexType)),
        pRepeater->pAllocator);

    memcpy(dataOutput, dataInput, iDataLen);

    IAS_LOG(LogLevel::INSTANCE.isInfo(), "Got packet, len: "<<iDataLen);

    pRepeater->ptrOutput->send(dataOutput.pass(), iDataLen);
  }

}
/*************************************************************************/
}
}
}
