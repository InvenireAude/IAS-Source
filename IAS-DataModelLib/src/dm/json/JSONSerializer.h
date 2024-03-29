/*
 * File: IAS-DataModelLib/src/dm/json/JSONSerializer.h
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
#ifndef _IAS_DM_JSON_JSONSERIALIZER_H_
#define _IAS_DM_JSON_JSONSERIALIZER_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
class DataObject;
class DataObjectList;
class Type;
namespace JSON {
class LibJSONWriter;
class JSONDocument;
class JSONHelper;
/*************************************************************************/
/** The class. */
 class JSONSerializer {
public:

	virtual ~JSONSerializer() throw();

	void serialize(const DataObject* pDataObject,bool  bXSIType=true);
	void serialize(const DataObjectList& lstDataObject, bool  bXSIType=true);

protected:
	JSONSerializer(const JSONHelper *pJSONHelper, std::ostream& os);


	void serializeElement(const DataObject* pDataObject,
							bool  bXSIType,
							const String& ="");

  void serializeList(const DataObjectList& lstDataObject, const Type* pPropertyType, const String& strPrefix = "");

	void printEscaped(const String& strValue);
	std::ostream& os;

  static const String& CENV_NONFMT_JSON;

  struct Prefixes{
    const char *sPrefix;
    const char *sBeginProperty;
    const char *sEndProperty;
    const char *sEndPropertyArray;
    const char *sDMType;
    const char *sEndl;

    Prefixes();
  };

  static Prefixes prefixes;
  const JSONHelper *pJSONHelper;

	friend class ::IAS::Factory<JSONSerializer>;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_JSON_JSONSERIALIZER_H_ */
