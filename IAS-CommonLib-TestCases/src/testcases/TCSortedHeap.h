/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCSortedHeap.h
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
#ifndef _TCSortedHeap_H_
#define _TCSortedHeap_H_

#include "commonlib/commonlib.h"

#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCSortedHeap: public TestUnit{

public:
	TCSortedHeap(TestSuite* pTestSuite);
	virtual ~TCSortedHeap()  throw ();
	
protected:

	virtual void init(TestSuite* pTestSuite);

	void testOrder();
	void testEmpty();
	void testFull();

	friend class ::IAS::Factory<TCSortedHeap>;
	::IAS::TestRunner<TCSortedHeap> theTestRunner;
};


} /* namespace TCT */
} /* namespace IAS */


#endif /*TCSortedHeap_H_*/
