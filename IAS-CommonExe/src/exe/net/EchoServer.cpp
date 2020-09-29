/*
 * File: EchoServer.cpp
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

#include "EchoServer.h"


namespace IAS {
namespace Exe {
namespace Net {

/*************************************************************************/
EchoServer::EchoServer(int iPort):
  iPort(iPort),
  ptrServer(NULL){
	IAS_TRACER;

  IAS::Net::Peer peer(iPort);

 ptrServer = IAS_DFT_FACTORY<IAS::Net::Server>::Create(peer);

}
/*************************************************************************/
EchoServer::~EchoServer() throw(){
	IAS_TRACER;

  for(WorkerCollection::iterator it = phcWorkers.begin(); it != phcWorkers.end(); it++){
    (*it)->stop();
  }

  for(WorkerCollection::iterator it = phcWorkers.begin(); it != phcWorkers.end(); it++){
    (*it)->join();
  }

}
/*************************************************************************/
void EchoServer::start(){

  while (! SYS::Signal::GetInstance()->isStopping()){
      phcWorkers.addPointer(
        IAS_DFT_FACTORY<Worker>::Create(ptrServer->accept())
      );
  }

}
/*************************************************************************/
void EchoServer::Worker::run(){

  size_t iDataLen = 1;

  while (! SYS::Signal::GetInstance()->isStopping() || iDataLen == 0){

      if(ptrFileHandle->read(buffer, buffer.getSize(), iDataLen) == IAS::Net::IBlockIO::RC_OK){

        size_t iOffset = 0;
        size_t iWritten = 0;

        while(iDataLen > 0){
          ptrFileHandle->write(buffer.getBuffer<char>() + iOffset, iDataLen, iWritten);
          iDataLen -= iWritten;
          iOffset  += iWritten;
        }
      }

  }

}
/*************************************************************************/
}
}
}
