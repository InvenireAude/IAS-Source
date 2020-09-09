/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCBufferQueue.cpp
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

#include "TCBufferQueue.h"
#include <queue>

namespace IAS {
namespace TCT {

int tabBufferQueueValues[] = { 13, 6, 28, 315, 417, 53, 167, 74, 23, 3, 323, 48, -1 };

/*************************************************************************/

TCBufferQueue::TCBufferQueue(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}
/*************************************************************************/
TCBufferQueue::~TCBufferQueue() throw () {
	IAS_TRACER;
}

/*************************************************************************/
void TCBufferQueue::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("testOrder",&::IAS::TCT::TCBufferQueue::testOrder);
	theTestRunner.addCase("testEmpty",&::IAS::TCT::TCBufferQueue::testEmpty);
	theTestRunner.addCase("testFull",&::IAS::TCT::TCBufferQueue::testFull);
	TestUnit::init("TCBufferQueue",&theTestRunner, pTestSuite);
}
/*************************************************************************/
void TCBufferQueue::testOrder() {
	IAS_TRACER;

	IAS::BufferQueue<int> buffer(7);
	typedef std::queue<int> Queue;
	Queue            queueValues;

	for(int i=0; tabBufferQueueValues[i] > 0; i++){
		buffer.put(tabBufferQueueValues[i]);
		queueValues.push(tabBufferQueueValues[i]);
	}

	if(buffer.size() != queueValues.size())
		IAS_THROW(BadUsageException("Size error. ")<<buffer.size()<<" ? "<<queueValues.size());
		
	while(!queueValues.empty()){

		int iValue = buffer.get();
		if(queueValues.front() != iValue)
			IAS_THROW(BadUsageException("Wrong order or a bad value: ")<<queueValues.front()<<" ? "<<iValue);
		queueValues.pop();
	}	

	if(buffer.size() != 0)
		IAS_THROW(BadUsageException("Expected an empty buffer."));

}
/*************************************************************************/
void TCBufferQueue::testEmpty() {
	IAS_TRACER;

	IAS::BufferQueue<int> buffer(8);

	buffer.put(1);
	buffer.get();
	try{
		buffer.get();
		IAS_THROW(BadUsageException("Expected an empty buffer exception."));
	}catch(Exception &e){}
}
/*************************************************************************/
void TCBufferQueue::testFull(){
	IAS_TRACER;

	IAS::BufferQueue<int> buffer(2);

	buffer.put(1);
	buffer.put(2);
	buffer.put(3);
	buffer.put(4);
	try{
		buffer.put(5);
		IAS_THROW(BadUsageException("Expected a full buffer exception."));
	}catch(Exception &e){}
}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
