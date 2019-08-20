/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorImplType.h
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
#ifndef _IAS_DM_Gen_CppCodeGeneratorImplType_H_
#define _IAS_DM_Gen_CppCodeGeneratorImplType_H_

#include <commonlib/commonlib.h>

#include <map>
#include <vector>

#include "../../../dm/gen/Impl/CppCodeGeneratorFriend.h"
#include "../../../dm/gen/Impl/Patterns.h"
#include <dm/datamodel.h>

namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {

/*************************************************************************/
class CppCodeGeneratorImplType : public CppCodeGeneratorFriend{
public:

	virtual ~CppCodeGeneratorImplType() throw();

	static CppCodeGeneratorImplType* Create(CppCodeGeneratorLogic* pParent);

	void generate();

	void generateWithCommonSourceFiles();
protected:
	CppCodeGeneratorImplType(CppCodeGeneratorLogic* pParent);

	void generateHeader(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo,
						  const Type* pType);

	void generateSource(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo,
						  const Type* pType);


	void generateSourceImpl(const CppCodeGeneratorLogic::NamespaceInfo *pNamespaceInfo,
														   const Type* pType,
														   IAS_DFT_FACTORY<OutputFile>::PtrHolder &ptrFile,
														   std::map<const Type*, bool>& hmIncludedTypes);

	friend class ::IAS::Factory<CppCodeGeneratorImplType>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DMWrap_Cpp_CPPCODEGENERATORLOGIC_H_ */


