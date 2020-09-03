/*
 * File: AsynchronousLogger.cpp
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

#include "AsynchronousLogger.h"

#include "LoggerOutput.h"
#include <string.h>

namespace IAS {
namespace Storage {
static MemoryManager _mm;
/*************************************************************************/
AsynchronousLogger::LogBuffer::LogBuffer(size_t iLogBufferSize):
  pData(NULL){
	IAS_TRACER;
  this->iLogBufferSize = iLogBufferSize;
  pData = (unsigned char*) _mm.allocate(iLogBufferSize);
  pCurrent = pData;
}
/*************************************************************************/
AsynchronousLogger::LogBuffer::~LogBuffer(){
	IAS_TRACER;
  if(pData)
    _mm.free(pData);
}
/*************************************************************************/
void AsynchronousLogger::LogBuffer::reset(){
	IAS_TRACER;
  pCurrent = pData;
}
/*************************************************************************/
size_t AsynchronousLogger::LogBuffer::getLeftSpaceSize() const{
	IAS_TRACER;
  return iLogBufferSize - (long) (pCurrent - pData);
}
/*************************************************************************/
size_t AsynchronousLogger::LogBuffer::getUsedSpaceSize() const{
	IAS_TRACER;
  return (long) (pCurrent - pData);
}
/*************************************************************************/
void AsynchronousLogger::LogBuffer::appendData(const void *pData, size_t iDataLen){
  IAS_TRACER;

  if(iDataLen > getLeftSpaceSize()){
    IAS_THROW(InternalException("AsynchronousLogger::LogBuffer::appendData overflow"));
  }

  memcpy(pCurrent, pData, iDataLen);
  pCurrent += iDataLen;
}
/*************************************************************************/
AsynchronousLogger::AsynchronousLogger(LoggerOutput* pLoggerOutput, size_t iLogBufferSize, int iSyncInterval):
  Logger(pLoggerOutput),
  logBufferOne(iLogBufferSize),
  logBufferTwo(iLogBufferSize),
  pWaitingBuffer(&logBufferOne),
  pWritingBuffer(&logBufferTwo){
	IAS_TRACER;
}
/*************************************************************************/
AsynchronousLogger::~AsynchronousLogger() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void AsynchronousLogger::logData(const void *pData, size_t iDataLen){
	IAS_TRACER;

  Mutex::Locker lock(mutex);

  if(pWaitingBuffer->getLeftSpaceSize() < iDataLen){

    while(pWritingBuffer->getUsedSpaceSize() != 0){
      mutex.wait(cndWriteInProgress);

      swapBuffers();

      cndReadyToWrite.broadcast();
    }
  }

  pWaitingBuffer->appendData(pData, iDataLen);

}
/*************************************************************************/
void AsynchronousLogger::swapBuffers(){
	IAS_TRACER;

  LogBuffer* tmpPtr = pWaitingBuffer;
  pWaitingBuffer = pWritingBuffer;
  pWritingBuffer = tmpPtr;

}
/*************************************************************************/
void AsynchronousLogger::syncBuffer(){
	IAS_TRACER;

  ptrLoggerOutput->write(pWritingBuffer->pData, pWritingBuffer->getUsedSpaceSize());
  pWritingBuffer->reset();
}
/*************************************************************************/
}
}
