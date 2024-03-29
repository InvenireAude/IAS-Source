/*
 * File: IAS-ServiceManagerLib/src/sm/worker/RunCommandHelper.cpp
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
#include "RunCommandHelper.h"

#include <commonlib/commonlib.h>

#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"
#include "exe/Handler.h"
#include "Process.h"
#include "StartStopHelper.h"
#include "WorkerForStop.h"
#include "signal.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
RunCommandHelper::RunCommandHelper(const ::IAS::SM::Cfg::Config *pConfig, bool bSuppressDebug):
		bSuppressDebug(bSuppressDebug){
	IAS_TRACER;

	this->pConfig = pConfig;
	ptrExeHandler  = IAS_DFT_FACTORY<Exe::Handler>::Create();

}
/*************************************************************************/
RunCommandHelper::~RunCommandHelper() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void RunCommandHelper::run(const String& strServiceName) {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Starting ...");

	const ::org::invenireaude::sm::cfg::Service *pService = pConfig->getService(strServiceName);
	const Command* pCommand = pService->getStartCmd();

	const ResourceGroup* dmResourceGrp = pConfig->getMergedServiceResourceGrps(pService);


	IAS_DFT_FACTORY<WorkerForStop>::PtrHolder ptrWorkerForStop(
			WorkerForStop::Create(pConfig));

	ptrWorkerForStop->work(pService);

	IAS_DFT_FACTORY<SYS::Proc::Executor>::PtrHolder ptrExecutor(ptrExeHandler->createExecutor(dmResourceGrp->getExe(), pCommand));

	IAS_DFT_FACTORY<Process>::PtrHolder ptrProcess(IAS_DFT_FACTORY<Process>::Create(ptrExecutor));

	StringPairList lstVariables;
	pConfig->buildEnvList(pService, lstVariables);

	if(bSuppressDebug)
		for(StringPairList::iterator it=lstVariables.begin(); it != lstVariables.end(); it++)
			if(it->first.find("IAS_DBG") != String::npos)
				it = lstVariables.erase(it);

	lstVariables.push_back(std::pair<String,String>(StartStopHelper::CEnvIndex, TypeTools::IntToString(0)));
	ptrProcess->updateEnvironment(lstVariables);

	ptrProcess->start();
	signal(SIGCHLD, SIG_DFL);
	ptrProcess->wait();

}
/*************************************************************************/

}
}
}
