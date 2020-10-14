/*
 * File: MemoryCopy.cpp
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

#include "MemoryCopy.h"

#include <sched.h>
#include <unistd.h>
#include <pthread.h>

namespace IAS {
namespace PerfCases {

/*************************************************************************/
void MemoryCopy::Run(int iPacketSize, int iTotalSize){
  IAS_TRACER;

  IAS_DFT_FACTORY<Buffer>::PtrHolder ptrBuffer(
    IAS_DFT_FACTORY<Buffer>::Create(iTotalSize)
  );

  char *pData = ptrBuffer->getBuffer<char>();

  for(int i=0; i<iTotalSize;i++){
    pData[i] = i * 17 ^ 123 ;
  };

 TimeSamplesResults tsr(TimeSamplesResults::COF_MicroSec);


 for(int j=0;j<100;j++){
   TimeSample ts(true);
   for(int i=0; i<100000;i++){
    memcpy( pData + ((i * 1234) % (iTotalSize - iPacketSize)),
             pData + ((i * 234) % (iTotalSize - iPacketSize)), iPacketSize);
  };
  tsr.addSample(ts);
 }

 std::cout<<"MemoryCopy: ["<<iPacketSize<<", "<<iTotalSize<<"]"<<tsr<<std::endl;

}

}
}
