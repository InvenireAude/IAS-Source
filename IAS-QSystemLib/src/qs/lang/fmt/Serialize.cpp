/*
 * File: IAS-QSystemLib/src/qs/lang/fmt/Serialize.cpp
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
#include "Serialize.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <dm/datamodel.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>
#include <qs/Impl/base/Attributes.h>



using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace Fmt {

/*************************************************************************/
Serialize::Serialize(const DM::Type* pType, const StringList& lstParamaters, const IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

	ptrFmtFactory = IAS_DFT_FACTORY<QS::Fmt::FmtFactory>::Create(pModuleProxy->getDataFactory());

}
/*************************************************************************/
Serialize::~Serialize() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Serialize::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strFormat   = pParameters->getString("format");
	DM::DataObject* dmData   = pParameters->getDataObject("data");

  IAS_DFT_FACTORY<QS::Base::Attributes>::PtrHolder ptrAttributes(IAS_DFT_FACTORY<QS::Base::Attributes>::Create());

  if(pParameters->getType()->asComplexType()->getProperties().hasProperty("attributes")){
    DM::DataObjectList& lstAttributes = pParameters->getList("attributes");

    for(int iIdx = 0; iIdx < lstAttributes.size(); iIdx++){
      const workers::Attribute* pAttribute = workers::DataFactory::GetInstance()->getAttributeType()->cast(lstAttributes.at(iIdx));
      ptrAttributes->setValue(pAttribute->getName(), pAttribute->getValue() );
    }
  }

	try{

		StringStream ssResult;
		ptrFmtFactory->getFormatter(strFormat)->write(dmData,ssResult,ptrAttributes);

		pParameters->setString(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),
							   ssResult.str());

	}catch(Exception& e){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();

		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}
}
/*************************************************************************/
Extern::Statement* Serialize::Create(const DM::Type* pType, const StringList& lstParamaters, const IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Serialize>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

