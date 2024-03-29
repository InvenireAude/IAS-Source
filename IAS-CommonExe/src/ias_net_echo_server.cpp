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

#include <parameters/EchoServerParameters.h>
#include <exe/net/EchoServer.h>

using namespace IAS;
using namespace Exe;

int main(int argc, char* argv[]) {
	IAS_TRACER;
	IAS::Logger::GetInstance();


	try {

	  IAS_DFT_FACTORY<Parameters::EchoServerParameters>::PtrHolder ptrParameters(
        IAS_DFT_FACTORY<Parameters::EchoServerParameters>::Create(argc, argv)
      );

		if (ptrParameters->checkAndShowHelp(std::cerr) ||
		    ptrParameters->checkAndShowVersion(std::cerr))
			return 1;

    IAS_DFT_FACTORY<Exe::Net::EchoServer>::PtrHolder ptrEchoServer(
      IAS_DFT_FACTORY<Exe::Net::EchoServer>::Create(ptrParameters->getPort())
    );

    ptrEchoServer->start();

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
