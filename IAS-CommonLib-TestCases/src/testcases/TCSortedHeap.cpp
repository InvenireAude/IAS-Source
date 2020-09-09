/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCSortedHeap.cpp
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

#include "TCSortedHeap.h"
#include <set>

namespace IAS {
namespace TCT {

int tabValues[] = { 13, 6, 28, 315, 417, 53, 167, 74, 23, 3, 323, 48, -1 };

/*************************************************************************/

TCSortedHeap::TCSortedHeap(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}
/*************************************************************************/
TCSortedHeap::~TCSortedHeap() throw () {
	IAS_TRACER;
}

/*************************************************************************/
void TCSortedHeap::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("testOrder",&::IAS::TCT::TCSortedHeap::testOrder);
	theTestRunner.addCase("testEmpty",&::IAS::TCT::TCSortedHeap::testEmpty);
	theTestRunner.addCase("testFull",&::IAS::TCT::TCSortedHeap::testFull);
	TestUnit::init("TCSortedHeap",&theTestRunner, pTestSuite);
}
/*************************************************************************/
void TCSortedHeap::testOrder() {
	IAS_TRACER;

	IAS::SortedHeap<int> heap(100);
	typedef std::set<int> OrderedSet;
	OrderedSet            setOrderedValues;

	for(int i=0; tabValues[i] > 0; i++){
		heap.insert(tabValues[i]);
		setOrderedValues.insert(tabValues[i]);
	}

	for(OrderedSet::const_iterator it = setOrderedValues.begin();
		it != setOrderedValues.end(); it++){

		int iValue = heap.getMin();
		if(*it != iValue)
			IAS_THROW(BadUsageException("Wrong order or a bad value: ")<<(*it)<<" ? "<<iValue);

		heap.popMin();
	}	

	if(heap.size() != 0)
		IAS_THROW(BadUsageException("Expected an empty heap."));

}
/*************************************************************************/
void TCSortedHeap::testEmpty() {
	IAS_TRACER;

	IAS::SortedHeap<int> heap(100);

	heap.insert(1);
	heap.popMin();
	try{
		heap.popMin();
		IAS_THROW(BadUsageException("Expected an empty heap exception."));
	}catch(Exception &e){}
}
/*************************************************************************/
void TCSortedHeap::testFull(){
	IAS_TRACER;

	IAS::SortedHeap<int> heap(3);

	heap.insert(1);
	heap.insert(2);
	heap.insert(3);
	return;
	try{
		heap.insert(4);
		IAS_THROW(BadUsageException("Expected a full heap exception."));
	}catch(Exception &e){}
}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
