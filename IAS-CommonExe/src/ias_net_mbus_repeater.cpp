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

#include <parameters/MBusRepeaterParameters.h>
#include <exe/net/MBusRepeater.h>

using namespace IAS;
using namespace Exe;
using namespace IAS::Storage;

int main(int argc, char* argv[]) {
	IAS_TRACER;
	IAS::Logger::GetInstance();


	try {

	  IAS_DFT_FACTORY<Parameters::MBusRepeaterParameters>::PtrHolder ptrParameters(
        IAS_DFT_FACTORY<Parameters::MBusRepeaterParameters>::Create(argc, argv)
      );

		if (ptrParameters->checkAndShowHelp(std::cerr) ||
		    ptrParameters->checkAndShowVersion(std::cerr))
			return 1;

    IAS::Net::MCast::EndPoint endPoint(ptrParameters->getGroup(),
                                       ptrParameters->getInterface(),
                                       ptrParameters->getPort(),
                                       ptrParameters->getMaxPacketSize());

    IAS_DFT_FACTORY<Dump::FileSet>::PtrHolder ptrDumpFileSet;
    IAS_DFT_FACTORY<Exe::Net::MBusRepeater>::PtrHolder ptrRepeater;

    if(ptrParameters->hasDumpDirectory()){

      ptrDumpFileSet = IAS_DFT_FACTORY<Dump::FileSet>::Create(
        ptrParameters->getDumpDirectory(),
        ptrParameters->getMaxFileSize()
      );

      if(ptrParameters->hasPrintStats()){
        ptrDumpFileSet->openBackLog();
        ptrDumpFileSet->dumpBackLogInfo(std::cout);
      }else{
        ptrRepeater = IAS_DFT_FACTORY<Exe::Net::MBusRepeater>::Create(
              endPoint,
              ptrParameters->getInputBufferSize(),
              ptrParameters->getOutputBufferSize(),
              ptrDumpFileSet);
      }
    }else{

      ptrRepeater = IAS_DFT_FACTORY<Exe::Net::MBusRepeater>::Create(
              endPoint,
              ptrParameters->getInputBufferSize(),
              ptrParameters->getOutputBufferSize());
    }

    if(!ptrRepeater.isNull())
        ptrRepeater->start(ptrParameters->getNumThreads());

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

}
