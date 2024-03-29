/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/ProcessCache.cpp
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
#include "ProcessCache.h"
#include "ProcessDataStore.h"

#include<qs/log/sps/LogLevel.h>

#include <org/invenireaude/qsystem/workers/sps/ProcessInstance.h>
#include <org/invenireaude/qsystem/workers/sps/ProcessArray.h>
#include <org/invenireaude/qsystem/workers/sps/DataFactory.h>

using namespace org::invenireaude::qsystem::workers::sps;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

const String ProcessCache::CEnvCacheSize("IAS_SPS_CACHE_SZ");

/*************************************************************************/
int ProcessCache::getDefaultCacheSize(){

    String strValue("100");
    EnvTools::GetEnv(CEnvCacheSize, strValue);
    return TypeTools::StringToInt(strValue);
}
/*************************************************************************/
ProcessCache::ProcessCache():
	CacheBase(getDefaultCacheSize()),
	iCounter(0){
	IAS_TRACER;

  strKeyPrefix = MiscTools::GetUUID();
  IAS_LOG(LogLevel::INSTANCE.isSystem(), "Prefix: "<<strKeyPrefix);
  strKeyPrefix+="-";
	ptrDataStore = IAS_DFT_FACTORY<ProcessDataStore>::Create("spsdb");
}
/*************************************************************************/
ProcessCache::~ProcessCache() throw(){
	IAS_TRACER;
}
/*************************************************************************/
ProcessCacheEntryPtr ProcessCache::createEntry(const String& strProcessName){
	IAS_TRACER;
	Mutex::Locker locker(mutex);

	String strID(strKeyPrefix+TypeTools::IntToString(iCounter++));

	return IAS_DFT_FACTORY<ProcessCacheEntry>::Create(strID,strProcessName,ptrDataStore.getPointer());
}
/*************************************************************************/
ProcessCacheEntryPtr ProcessCache::getEntry(const String& strID){
	IAS_TRACER;
	Mutex::Locker locker(mutex);

	ProcessCacheEntryPtr ptrProcessCacheEntry;


	Ext::ProcessInstancePtr dmProcessInstance(ptrDataStore->loadAndLockProcessInstance(strID));

	if(lookup(strID,ptrProcessCacheEntry)){

		if(dmProcessInstance->getOldVersion() != ptrProcessCacheEntry->getProcessInstance()->getOldVersion()){
			ptrProcessCacheEntry->updateProcessInstance(dmProcessInstance);
			ptrProcessCacheEntry->loadDocuments(ptrDataStore);
		}

	}else{

		ptrProcessCacheEntry=IAS_DFT_FACTORY<ProcessCacheEntry>::Create(dmProcessInstance);
		ptrProcessCacheEntry->loadDocuments(ptrDataStore);
	}


	return ptrProcessCacheEntry;
}
/*************************************************************************/
void ProcessCache::synchronize(ProcessCacheEntry* pProcessCacheEntry){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pProcessCacheEntry);

	pProcessCacheEntry->save(ptrDataStore);
}
/*************************************************************************/
void ProcessCache::returnToCache(ProcessCacheEntryPtr& ptrProcessCacheEntry){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(ptrProcessCacheEntry);
	insert(ptrProcessCacheEntry);
}
/*************************************************************************/
void ProcessCache::getEntriesToSchedule(EntriesList& lstEntries, int iMaxEntries ){
	IAS_TRACER;
	lstEntries.clear();

	Ext::ProcessArrayPtr dmArray(DataFactory::GetInstance()->createProcessArray());

	dmArray->setPageSize(iMaxEntries);
	ptrDataStore->getProcessesToSchedule(dmArray,iMaxEntries);

	Ext::ProcessInstanceList& lstInstances(dmArray->getInstancesList());

	Mutex::Locker locker(mutex);

	for(int iIdx=0; iIdx<lstInstances.size();iIdx++)
		lstEntries.push_back(IAS_DFT_FACTORY<ProcessCacheEntry>::Create(lstInstances.at(iIdx)));


}
/*************************************************************************/
void ProcessCache::getEntriesToClean(EntriesList& lstEntries, int iMaxEntries ){
	IAS_TRACER;

	lstEntries.clear();

	Ext::ProcessArrayPtr dmArray(DataFactory::GetInstance()->createProcessArray());

	dmArray->setPageSize(iMaxEntries);
	ptrDataStore->getProcessesToClean(dmArray, iMaxEntries);

	Ext::ProcessInstanceList& lstInstances(dmArray->getInstancesList());

	Mutex::Locker locker(mutex);

	for(int iIdx=0; iIdx<lstInstances.size();iIdx++)
		lstEntries.push_back(IAS_DFT_FACTORY<ProcessCacheEntry>::Create(lstInstances.at(iIdx)));

}
/*************************************************************************/
void ProcessCache::CreateInstanceSafely(){
	IAS_TRACER;
	static Mutex mutex;
	Mutex::Locker locker(mutex);
	SPS::ProcessCache::GetInstance();
}

/*************************************************************************/
}
}
}
}
}
}

