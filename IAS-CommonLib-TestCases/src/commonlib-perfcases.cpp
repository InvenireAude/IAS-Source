/*
 * File: IAS-CommonLib-TestCases/src/commonlib-testcases.cpp
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
#include "commonlib/commonlib.h"

#include <prefcases/ProducerConsumer.h>
#include <prefcases/ThreadSynchronization.h>
#include <prefcases/ThreadSpinlocks.h>
#include <prefcases/MemoryCopy.h>

using namespace IAS;
using namespace IAS::PerfCases;


int main(int argc, char* argv[]) {
	IAS_TRACER;
	IAS::Logger::GetInstance();

	std::cout << "Starting\n";

	try {

    /*
     * ProducerConsumer
     */

    // for(int iWriters = 1; iWriters <= 16; iWriters+=4)
    //   for(int iReaders = 1; iReaders <= 16; iReaders+=4)
    //     for(int iBuffLen = 1; iBuffLen <= 16; iBuffLen+=4)
    //       ProducerConsumer::Run(iWriters,iReaders,iBuffLen,false);


    /*
     * ThreadSynchronization
     */

  //  for(int iWorkers = 2; iWorkers <= 20; iWorkers+=2)
  //         ThreadSynchronization::Run(iWorkers);


  //  for(int iWorkers = 2; iWorkers <= 20; iWorkers+=2)
  //         ThreadSpinlocks::Run(iWorkers);

  for(int iPacketSize = 64; iPacketSize <= 1024; iPacketSize*=2)
    for(int iTotalSize = 1; iTotalSize <= 4; iTotalSize+=2)
          MemoryCopy::Run(iPacketSize, iTotalSize*10*1024*1024);


	} catch (IAS::SystemException& e) {
		std::cerr << "System Exception:\n";
		e.printToStream(std::cerr);
		std::cerr << "\n";
	} catch (IAS::Exception& e) {
		std::cerr << "Exception:\n";
		e.printToStream(std::cerr);
		std::cerr << "\n";
	} catch (...) {
		std::cerr << "Unknown exception !\n";
	}

	std::cout << "ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout << "Tracer:\n";
	//IAS::TracerStats::GetInstance()->printToStream(std::cout);
	std::cout << "Ending\n";
}
