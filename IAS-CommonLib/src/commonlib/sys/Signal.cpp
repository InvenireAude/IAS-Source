/*
 * File: IAS-CommonLib/src/commonlib/sys/Signal.cpp
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
#include "Signal.h"

#include <commonlib/commonlib.h>

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<commonlib/threads/Thread.h>

#ifdef __GLIBC__
#include <malloc.h>
#endif
namespace IAS {
namespace SYS {

static Mutex _SignalMutex;

/*************************************************************************/
bool Signal::bStopping(false);
struct sigaction old_action[32];
/*************************************************************************/
void Signal::SignalHandler(int iSignal){

	Mutex::Locker locker(_SignalMutex);

	if(bStopping)
		return;

	bStopping=true;

	Signal::GetInstance()->stopThreads();

}
/*************************************************************************/
void Signal::SignalHandlerStopOnly(int iSignal){

	Mutex::Locker locker(_SignalMutex);

	if(bStopping)
		return;

	bStopping=true;
}
/*************************************************************************/
void Signal::User1SignalHandler(int iSignal){

	Mutex::Locker locker(_SignalMutex);

	if(bStopping)
		return;

		Signal::GetInstance()->handleUserSignal();
}
/*************************************************************************/
void Signal::User2SignalHandler(int iSignal){

	Mutex::Locker locker(_SignalMutex);

	if(bStopping)
		return;

#ifdef __GLIBC__
  malloc_info(0, stderr);
#endif

}
/*************************************************************************/
Signal::Signal(){
	IAS_TRACER;

	bStopping=false;

	struct sigaction new_action;

	new_action.sa_handler = SIG_IGN;
	new_action.sa_flags   = 0;
	if(sigaction(SIGPIPE, &new_action,0) == -1)
			IAS_THROW(SystemException("Signal SIGPIPE"));

	if(getenv("IAS_SIG_CANCEL_THREADS") && getenv("IAS_SIG_CANCEL_THREADS")[0] == 'N')
		new_action.sa_handler = Signal::SignalHandlerStopOnly;
	else
		new_action.sa_handler = Signal::SignalHandler;

	sigemptyset (&new_action.sa_mask);
	new_action.sa_flags = SA_RESTART;

	if(sigaction(SIGHUP, &new_action,old_action+SIGHUP) == -1)
		IAS_THROW(SystemException("Signal SIGHUP"));

	if(sigaction(SIGINT, &new_action,old_action+SIGINT) == -1)
		IAS_THROW(SystemException("Signal SIGINT"));

	if(sigaction(SIGTERM, &new_action,old_action+SIGTERM) == -1)
		IAS_THROW(SystemException("Signal SIGTERM"));

  new_action.sa_handler = Signal::User1SignalHandler;

	if(sigaction(SIGUSR1, &new_action,old_action+SIGUSR1) == -1)
		IAS_THROW(SystemException("Signal SIGUSR1"));

  new_action.sa_handler = Signal::User2SignalHandler;

	if(sigaction(SIGUSR2, &new_action,old_action+SIGUSR2) == -1)
		IAS_THROW(SystemException("Signal SIGUSR2"));

}
/*************************************************************************/
Signal::~Signal() throw(){
	IAS_TRACER;
	Mutex::Locker locker(_SignalMutex);

	bStopping=true;
}
/*************************************************************************/
bool Signal::isStopping()const {
	IAS_TRACER;
	return bStopping;
}
/*************************************************************************/
void Signal::stopThreads(){
	IAS_TRACER;

	for(ThreadSet::const_iterator it=setThreadsToStop.begin();
		it != setThreadsToStop.end(); it++){
		IAS_LOG(LogLevel::INSTANCE.isSystem(), "stopping a thread");;
		(*it)->stop();
	}
}
/*************************************************************************/
void Signal::addThread(Thread* pThread){
	IAS_TRACER;
	Mutex::Locker locker(_SignalMutex);
	setThreadsToStop.insert(pThread);
}
/*************************************************************************/
void Signal::removeThread(Thread* pThread){
	IAS_TRACER;
	Mutex::Locker locker(_SignalMutex);
	setThreadsToStop.erase(pThread);
}
/*************************************************************************/
Signal::ThreadRegistration::ThreadRegistration(){
	Signal::GetInstance()->addThread(
			Thread::Specific::GetPointer());
}
/*************************************************************************/
Signal::ThreadRegistration::~ThreadRegistration(){
	Signal::GetInstance()->removeThread(
			Thread::Specific::GetPointer());
}
/*************************************************************************/
/*************************************************************************/
void Signal::addUserSignalCallback(UserSignalCallback* pUserSignalCallback){
	IAS_TRACER;
	Mutex::Locker locker(_SignalMutex);
	setUserSignalCallback.insert(pUserSignalCallback);
}
/*************************************************************************/
void Signal::removeUserSignalCallback(UserSignalCallback* pUserSignalCallback){
	IAS_TRACER;
	Mutex::Locker locker(_SignalMutex);
	setUserSignalCallback.erase(pUserSignalCallback);
}
/*************************************************************************/
Signal::UserSignalCallback::UserSignalCallback(){
	Signal::GetInstance()->addUserSignalCallback(this);
}
/*************************************************************************/
Signal::UserSignalCallback::~UserSignalCallback(){
	Signal::GetInstance()->addUserSignalCallback(this);
}
/*************************************************************************/
void Signal::handleUserSignal(){
	for(UserSignalCallbackSet::iterator it=setUserSignalCallback.begin();
		it != setUserSignalCallback.end(); it++){
		IAS_LOG(LogLevel::INSTANCE.isSystem(), "handle the user signal:");;
		(*it)->handleUserSignal();
	}
}
/*************************************************************************/
void Signal::StopApplication(bool bCancelThreads){
	
	if(bCancelThreads){
		SignalHandler(0);
	}else{
		SignalHandlerStopOnly(0);
	}
}
/*************************************************************************/
//TODO AIX xlc/linker workaround
Signal* Signal::GetInstance(){
	return InstanceFeature<Signal>::GetInstance();

}
}
}
