/*

 * File: IAS-QSystemLib/src/qs/workers/proc/GlobalContext.cpp
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
#include "GlobalContext.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "dm/Impl/DataFactory.h"
#include <ds/Impl/Environment.h>
#include <qs/fmt/FmtFactory.h>

#include "io/IOFactory.h"
#include "ds/DSFactory.h"
#include "txm/TXMFactory.h"
#include "logic/LogicFactory.h"

#include "cache/CacheStore.h"
#include "cache/CacheFactory.h"

#include "ec/EventCounterFactory.h"
#include "ec/EventCounterStore.h"

#include "stats/LogicStatsStore.h"
#include "stats/PublisherFactory.h"
#include "stats/PublisherStore.h"

#include "dict/DictionaryStore.h"
#include "task/WaitingRoom.h"

#include "mode/ControllerFactory.h"
#include "mode/Controller.h"

#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>
#include <org/invenireaude/qsystem/workers/ds/DataFactory.h>
#include <org/invenireaude/qsystem/workers/cache/DataFactory.h>
#include <org/invenireaude/qsystem/workers/ec/DataFactory.h>
#include <org/invenireaude/qsystem/workers/txm/DataFactory.h>
#include <org/invenireaude/qsystem/workers/logic/DataFactory.h>

#include <org/invenireaude/qsystem/workers/spec/DataFactory.h>
#include <org/invenireaude/qsystem/workers/spec/Specification.h>
#include <org/invenireaude/qsystem/workers/io/InputSpecification.h>
#include <org/invenireaude/qsystem/workers/io/OutputSpecification.h>
#include <org/invenireaude/qsystem/workers/io/Input.h>
#include <org/invenireaude/qsystem/workers/io/Output.h>
#include <org/invenireaude/qsystem/workers/logic/LogicSpecification.h>
#include <org/invenireaude/qsystem/workers/logic/Logic.h>

#include <org/invenireaude/qsystem/workers/stats/DataFactory.h>

#include <qs/ui/Messages.h>

#include <climits>

#include "ProgramProvider.h"
#include "wcm/Registry.h"

#include "wcm/WorkContextManager.h"

//TODO eclipse complains about __INT_MAX__
#ifndef __INT_MAX__
#define __INT_MAX__ 99999999
#endif

using namespace org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {

int  GlobalContext::CMemoryTrimPeriod(-1);
const String& GlobalContext::CEnvMemoryTrimPeriod("IAS_PROC_MEM_TRIM");

/*************************************************************************/
GlobalContext::GlobalContext(const Parameters* pParameters):
	ptrDataFactory(org::invenireaude::qsystem::workers::DataFactory::GetInstance()->getContaingDataFactory()),
	ptrLogicFactory(IAS_DFT_FACTORY<Logic::LogicFactory>::Create()),
	bAbort(pParameters->getDontRun()),
	dmSpecification(NULL),
  tLastMemoryTrim(time(NULL)),
  iMemoryTrimPeriod(-1){

	IAS_TRACER;

	loadXSD();

	dmSpecification = readParameters(pParameters);

// We may need this when initialization touches DBs (eg. sql verification)
	ptrWorkContext=IAS_DFT_FACTORY<WCM::WorkContextManager>::Create(this);
  pWorkContextShared=ptrWorkContext;

	ptrFmtFactory   = IAS_DFT_FACTORY<Fmt::FmtFactory>::Create(ptrDataFactory);

	ptrDictionaryStore = IAS_DFT_FACTORY<Dict::DictionaryStore>::Create();

	ptrCacheStore = IAS_DFT_FACTORY<Cache::CacheStore>::Create();

	ptrEventCounterStore = IAS_DFT_FACTORY<EC::EventCounterStore>::Create();

	ptrWaitingRoom = IAS_DFT_FACTORY<Task::WaitingRoom>::Create(this);


	InstanceFeature< ::IAS::DS::Impl::Environment>::GetInstance()->
		setFmtFactory(IAS_DFT_FACTORY<Fmt::FmtFactory>::Create(ptrDataFactory));

	if(!dmSpecification || !dmSpecification->isSetInputSpec())
		IAS_THROW(InternalException("!dmSpecification || !dmSpecification->isSetInput() in GlobalContext()"));

	if(dmSpecification->isSetInputSpec())
		iMsgTotal=dmSpecification->getInputSpec()->getNumMsgs();

	iMsgLeft=iMsgTotal;

	if(dmSpecification->isSetCacheSpec())
		Cache::CacheFactory::CreateCaches(dmSpecification->getCacheSpec(),ptrCacheStore,this);

	if(dmSpecification->isSetEcSpec())
		EC::EventCounterFactory::CreateEventCounters(dmSpecification->getEcSpec(),ptrEventCounterStore,this);

	if(dmSpecification->isSetStats()){

		ptrStatsPublisherStore = IAS_DFT_FACTORY<Stats::PublisherStore>::Create(dmSpecification->getStats(),this);
		ptrStatsPublisherStore->start();
	}

  String strMemTrimPeriod;
  if(EnvTools::GetEnv(CEnvMemoryTrimPeriod, strMemTrimPeriod)){
    iMemoryTrimPeriod = TypeTools::StringToInt(strMemTrimPeriod);
    IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"I will trim memory, "<<CEnvMemoryTrimPeriod<<"="<<iMemoryTrimPeriod);
  }

}
/*************************************************************************/
GlobalContext::~GlobalContext() throw(){
	IAS_TRACER;
  pWorkContextShared = 0;
}
/*************************************************************************/
void GlobalContext::InitializeDataFactories(){

	Lang::Model::Model::RegisterBuildInTypes();

	org::invenireaude::qsystem::workers::DataFactory::GetInstance();
	org::invenireaude::qsystem::workers::io::DataFactory::GetInstance();
	org::invenireaude::qsystem::workers::ds::DataFactory::GetInstance();
	org::invenireaude::qsystem::workers::txm::DataFactory::GetInstance();
	org::invenireaude::qsystem::workers::cache::DataFactory::GetInstance();
	org::invenireaude::qsystem::workers::ec::DataFactory::GetInstance();
	org::invenireaude::qsystem::workers::stats::DataFactory::GetInstance();
	org::invenireaude::qsystem::workers::logic::DataFactory::GetInstance();

}
/*************************************************************************/
void GlobalContext::loadXSD(){


	IAS_DFT_FACTORY<DM::XML::XSDHelper>::PtrHolder ptrXSDHelper(
					IAS_DFT_FACTORY<DM::XML::XSDHelper>::Create(ptrDataFactory));

	StringList lstXSDFiles;
	IAS::EnvTools::GetEnvTokenized("IAS_LANG_XSD",lstXSDFiles);

	for(StringList::const_iterator it = lstXSDFiles.begin();
		it != lstXSDFiles.end();
		it++){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Loading: "<<(*it));
			String strFile(*it);
			if(strFile.length() > 4 && strFile.substr(strFile.length()-4).compare(".xsd") == 0){
			ptrXSDHelper->defineTypesFromFile(*it);
		}else{
			//Keep forever ?
			SYS::DynamicLibrary* pLibrary=IAS_DFT_FACTORY<SYS::DynamicLibrary>::Create(*it);
			void (*fun)();
			fun=(void(*)())pLibrary->getSymbol("ias_dm_init");
			(*fun)();
		}
	}

	//IAS::DM::Impl::MemoryManager::GetInstance()->PrintToStream(std::cout);
	//IAS::MemoryManager::GetInstance()->printToStream(std::cout);
}
/*************************************************************************/
const ::IAS::DM::DataFactory *GlobalContext::getDataFactory()const{
	IAS_TRACER;
	return ptrDataFactory;
}
/*************************************************************************/
bool GlobalContext::allDone(){
	IAS_TRACER;
	Mutex::Locker locker(mutex);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Left: "<<iMsgLeft<<", bAbort="<<bAbort);

	if(iMsgLeft == 0 || bAbort)
    return true;

  time_t tCurrentTime = time(NULL);

  if(iMemoryTrimPeriod > 0 && (tCurrentTime / iMemoryTrimPeriod) > (tLastMemoryTrim / iMemoryTrimPeriod) ){
    MemoryManager::GetInstance()->trim();
    tLastMemoryTrim = tCurrentTime;
  }
	iMsgLeft--;
	return false;
}
/*************************************************************************/
void GlobalContext::abort(bool bImmediate){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
    bAbort=true;
    if(bImmediate)
    	SYS::Signal::SignalHandler(15);
}
/*************************************************************************/
bool GlobalContext::isAborted(){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
    return bAbort;
}
/*************************************************************************/
void GlobalContext::getProgress(unsigned int& iMsgLeft, unsigned int& iMsgTotal){
	IAS_TRACER;

	iMsgLeft=this->iMsgLeft;
	iMsgTotal=this->iMsgTotal;

}
/*************************************************************************/
const Fmt::FmtFactory* GlobalContext::getFmtFactory()const{
	IAS_TRACER;
	return ptrFmtFactory;
}
/*************************************************************************/
Logic::LogicFactory* GlobalContext::getLogicFactory() const{
	IAS_TRACER;
	return ptrLogicFactory;
}
/*************************************************************************/
Dict::DictionaryStore* GlobalContext::getDictionaryStore() const{
	IAS_TRACER;
	return ptrDictionaryStore;
}
/*************************************************************************/
Task::WaitingRoom*       GlobalContext::getWaitingRoom() const{
	IAS_TRACER;
	return ptrWaitingRoom;
}
/*************************************************************************/
Cache::CacheStore* GlobalContext::getCacheStore() const{
	IAS_TRACER;
	return ptrCacheStore;
}
/*************************************************************************/
EC::EventCounterStore* GlobalContext::getEventCounterStore() const{
	IAS_TRACER;
	return ptrEventCounterStore;
}
/*************************************************************************/
Stats::LogicStatsStore* GlobalContext::getLogicStatsStore() const{
	IAS_TRACER;

	if(ptrStatsPublisherStore.isNull())
		IAS_THROW(ItemNotFoundException("LogicStatsStore"));

	return ptrStatsPublisherStore->getLogicStatsStore();
}
/*************************************************************************/
const ::org::invenireaude::qsystem::workers::spec::Specification* GlobalContext::getSpecification()const{
	IAS_TRACER;
	return dmSpecification;
}
/*************************************************************************/
ProgramProvider* GlobalContext::getProgramProvider(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(ptrProgramProvider.isNull()){
		ptrProgramProvider = IAS_DFT_FACTORY< ProgramProvider >::Create<DM::DataFactory*>(ptrDataFactory);
	}

	return ptrProgramProvider;
}
/*************************************************************************/
spec::Ext::SpecificationPtr GlobalContext::readParameters(const Parameters* pParameters)const{
	IAS_TRACER;

	SYS::Signal::GetInstance();
	SYS::GlobalDynamicLibraryStore::GetInstance();

	spec::Ext::SpecificationPtr dmSpecification;

	if(pParameters->hasFullConfig()){

		dmSpecification =	spec::DataFactory::GetInstance()->getSpecificationType()->cast(
					DM::Tools::Formatter::LoadFile(pParameters->getFullConfig(),
													spec::DataFactory::GetInstance()->getContaingDataFactory(),
													spec::DataFactory::GetInstance()->getSpecificationType()));

	}else{
		dmSpecification = spec::DataFactory::GetInstance()->createSpecification();

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo() && pParameters->hasInputSpecs(),  "Setup Input: "<<pParameters->getInputSpecs());
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo() && pParameters->hasOutputSpecs(), "Setup Output: "<<pParameters->getOutputSpecs());
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo() && pParameters->hasLogicSpecs(),  "Setup Logic: "<<pParameters->getLogicSpecs());

	}

	if(pParameters->hasInputSpecs() || !pParameters->hasFullConfig()){

		io::Ext::InputSpecificationPtr dmParametersInputSpecification(
      IO::IOFactory::InputSpecsToDM(pParameters->hasInputSpecs() ? pParameters->getInputSpecs() : "file:stdin?format=String"));

		io::InputSpecification *pInputSpecification = dmSpecification->isSetInputSpec() ?
			dmSpecification->getInputSpec() : dmSpecification->createInputSpec();

		const io::Ext::InputList& lstInputs(dmParametersInputSpecification->getInputsList());

		for(int iIdx=0; iIdx < lstInputs.size(); iIdx++)
			pInputSpecification->setInputs(lstInputs.at(iIdx)->duplicateInput());
	}


  if(pParameters->hasOutputSpecs() || !pParameters->hasFullConfig()){

	  io::Ext::OutputSpecificationPtr dmParametersOutputSpecification(
      IO::IOFactory::OutputSpecsToDM(pParameters->hasOutputSpecs() ? pParameters->getOutputSpecs() :  "file:stdout"));

	  io::OutputSpecification *pOutputSpecification = dmSpecification->isSetOutputSpec() ?
		  dmSpecification->getOutputSpec() : dmSpecification->createOutputSpec();

	  const io::Ext::OutputList& lstOutputs(dmParametersOutputSpecification->getOutputsList());

	  for(int iIdx=0; iIdx < lstOutputs.size(); iIdx++)
		  pOutputSpecification->setOutputs(lstOutputs.at(iIdx)->duplicateOutput());
  }

	if(!dmSpecification->isSetInputSpec())
		dmSpecification->createInputSpec();

	if(!dmSpecification->getInputSpec()->isSetNumMsgs())
		dmSpecification->getInputSpec()->setNumMsgs(pParameters->getNumMessages());


	if(!dmSpecification->getInputSpec()->isSetOffset())
		dmSpecification->getInputSpec()->setOffset(pParameters->getOffset());


	if(pParameters->hasDataSourceSpecs())
		dmSpecification->setDatasourceSpec(DS::DSFactory::DataSourceSpecsToDM(pParameters->getDataSourceSpecs()));

	if(pParameters->hasTXMSpecs())
		dmSpecification->setTxmSpec(TXM::TXMFactory::TransactionManagerSpecsToDM(pParameters->getTXMSpecs()));

	if(pParameters->hasCacheSpecs())
		dmSpecification->setCacheSpec(Cache::CacheFactory::CacheSpecsToDM(pParameters->getCacheSpecs()));

	if(pParameters->hasEventCounterSpecs())
		dmSpecification->setEcSpec(EC::EventCounterFactory::ECSpecsToDM(pParameters->getCacheSpecs()));

	if(pParameters->hasLogicSpecs())
		dmSpecification->setLogicSpec(Logic::LogicFactory::SpecsToDM(pParameters->getLogicSpecs(),pParameters->getLogicParameters()));

	logic::Ext::LogicList& lstLogics(dmSpecification->getLogicSpec()->getLogicsList());

	for(int iIdx=0;iIdx < lstLogics.size();iIdx++){

		if(! dmSpecification->getLogicSpec()->getLogicsList().at(iIdx)->isSetInstances())
			dmSpecification->getLogicSpec()->getLogicsList().at(iIdx)->setInstances(pParameters->getNumThreads());

		if(! dmSpecification->getLogicSpec()->getLogicsList().at(iIdx)->isSetCommitCount())
			dmSpecification->getLogicSpec()->getLogicsList().at(iIdx)->setCommitCount(pParameters->getCommitCount());
	}


	if(!dmSpecification->isSetMode() || pParameters->hasModeSpecs())
		dmSpecification->setMode(pParameters->getModeSpecs());

	if(pParameters->hasStatsPublishersSpecs()){
		dmSpecification->setStats(Stats::PublisherFactory::SpecsToDM(pParameters->getStatsPublishersSpecs()));
	}

	return dmSpecification;
}
/*************************************************************************/
void GlobalContext::Start(const Parameters* pParameters){

	IAS_TRACER;

	InitializeDataFactories();
	WCM::Registry::GetInstance();
	SYS::Signal::GetInstance();

	IAS_DFT_FACTORY<GlobalContext>::PtrHolder ptrGlobalContext;
	Mode::ControllerFactory::PtrHolder ptrController;

	try {

		ptrGlobalContext = IAS_DFT_FACTORY<GlobalContext>::Create(pParameters);
		ptrController    = Mode::ControllerFactory::Create(ptrGlobalContext);

	}catch(Exception& e){
		UserMessage(UI::Messages::MSGE_ConfigError)<<e.getName()<<e.getInfo();
		return;
	}


	ptrController->start();
}
/*************************************************************************/
}
}
}
}
