/*
 * File: IAS-QSystemExe/src/ias_qs_distributor.cpp
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
#include <commonlib/commonlib.h>
#include "parameters/DistributorParameters.h"
#include <qs/api.h>
#include "qs/Impl/shm/Administrator.h"

using namespace IAS;
using namespace QS;
using namespace API;
using namespace Parameters;

int main(int argc, char* argv[]) {
	IAS_TRACER;
	IAS::Logger::GetInstance();


	try {

		IAS_DFT_FACTORY<DistributorParameters>::PtrHolder
			ptrParameters(IAS_DFT_FACTORY<DistributorParameters>::Create(argc, argv));

		if (ptrParameters->checkAndShowHelp(std::cerr))
			return 1;

		SHM::Administrator::StartDistributor(ptrParameters->getSystemName());

	} catch (IAS::SystemException& e) {
		std::cerr << "System Exception:\n";
		e.printToStream(std::cerr);
		std::cerr << "\n";
	} catch (IAS::Exception& e) {
		std::cerr << "Exception:\n";
		e.printToStream(std::cerr);
		std::cerr << "\n";
	} catch (...) {
		std::cerr << "Unhandled exception !\n";
	}

	if(0 && LogLevel::INSTANCE.bIsInfo){
		IAS::MemoryManager::GetInstance()->printToStream(std::cerr);
		IAS::TracerStats::GetInstance()->printToStream(std::cerr);
	}
}
