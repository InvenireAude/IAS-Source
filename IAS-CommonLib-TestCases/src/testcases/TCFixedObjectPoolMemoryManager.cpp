/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCFixedObjectPoolMemoryManager.cpp
 *
 * Copyright (C) 2020, Albert Krzymowski
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
#include "commonlib/memory/mm/SimpleListMemoryManager.h"

#include "TCFixedObjectPoolMemoryManager.h"

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>

namespace IAS{
namespace TCT{

/*************************************************************************/
Allocator *TCFixedObjectPoolMemoryManager::TheAllocator;
/*************************************************************************/
TCFixedObjectPoolMemoryManager::TCFixedObjectPoolMemoryManager(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

}
/*************************************************************************/
TCFixedObjectPoolMemoryManager::~TCFixedObjectPoolMemoryManager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCFixedObjectPoolMemoryManager::init(TestSuite* pTestSuite){
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCFixedObjectPoolMemoryManager::caseALL);
	TestUnit::init("TCFixedObjectPoolMemoryManager",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCFixedObjectPoolMemoryManager::caseALL(){
	IAS_TRACER;

	IAS_DFT_FACTORY<FixedObjectPoolMemoryManager>::PtrHolder ptrMemoryManager;
	char *b = new char[FixedObjectPoolMemoryManager::ComputeMemoryRequirement(sizeof(Object),100)];
	Object *tabObjects = (Object *)b;
	ptrMemoryManager=IAS_DFT_FACTORY<FixedObjectPoolMemoryManager>::Create(b, sizeof(Object), 100);
	TheAllocator=ptrMemoryManager;

	{
		ObjectFactory::PtrHoldersCollection phc;
		for(int i=0; i<25; i++){
			if(i % 5 == 0){
				ObjectFactory::PtrHolder
					ptrObject(ObjectFactory::Create(i));
			}else{
				phc.addPointer(ObjectFactory::Create(i));
			}
		}

		ptrMemoryManager->dump(std::cerr);
		ptrMemoryManager->printToStream(std::cerr);

		std::cerr<<"Expecting an error [1]"<<std::endl;
		ObjectFactory::Free(tabObjects - 1);
		std::cerr<<"Expecting an error [2]"<<std::endl;
		ObjectFactory::Free(tabObjects + 30);
		std::cerr<<"Done with errors."<<std::endl;
	}

	ptrMemoryManager->printToStream(std::cerr);

}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
