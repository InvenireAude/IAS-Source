/*
 * File: EchoServer.h
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


#ifndef _IAS_Exe_Net_EchoServer_H_
#define _IAS_Exe_Net_EchoServer_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace Exe {
namespace Net {

/*************************************************************************/
/** The EchoServer class.
 *
 */
class EchoServer {
public:

	virtual ~EchoServer() throw();

  void start();

protected:
	EchoServer(int iPort);
  int iPort;

  class Worker : public Thread, public Runnable {

    public:
      Worker(IAS::Net::FileHandle* pFileHandle):
      Thread(this),
      ptrFileHandle(pFileHandle),
      buffer(4096){
        start();
      };

      virtual void run();

      protected:
        IAS_DFT_FACTORY<IAS::Net::FileHandle>::PtrHolder ptrFileHandle;

        Buffer buffer;
  };

  typedef IAS_DFT_FACTORY<Worker>::PtrHoldersCollection WorkerCollection;
  WorkerCollection                                      phcWorkers;

	friend class Factory<EchoServer>;

  IAS_DFT_FACTORY<IAS::Net::Server>::PtrHolder ptrServer;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Exe_Net_EchoServer_H_ */
