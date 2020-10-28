/*
 * File: IAS-QSystemLib/src/qs/fmt/MultiPartFormatter.h
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
#ifndef _IAS_QS_Fmt_MultiPartFormatter_H_
#define _IAS_QS_Fmt_MultiPartFormatter_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <dm/json/JSONHelper.h>

#include "Formatter.h"

#include <org/invenireaude/qsystem/workers/Context.h>
#include <qs/workers/proc/wcm/WorkContextManager.h>

namespace IAS {
namespace QS {
namespace Fmt {
class FmtFactory;

/*************************************************************************/
/** The MultiPartFormatter class.
 *
 */
class MultiPartFormatter :public Formatter {
public:

	virtual ~MultiPartFormatter() throw();

	virtual void write(const DM::DataObject* dmData,
							std::ostream&       ostream,
						    QS::API::Attributes *pAttributes=NULL);

	virtual void read( DM::DataObjectPtr& dmData,
						   std::istream&       istream,
						   QS::API::Attributes *pAttributes=NULL);

  static const String& CDateTimeFormatOut;

protected:
	MultiPartFormatter(const DM::DataFactory* pDataFactory);

	const DM::DataFactory* pDataFactory;

	TimeSamplesResults tsrParsing;
	TimeSamplesResults tsrSerialization;

  static const String& CDefaultFormat;
  static const String& CFormatAttr;
  static const String& CDataFormNameAttr;
  static const String& CAttachmentFormNameAttr;
  static const String& CAttachmentFormFileAttr;
  static const String& CBoundaryAttr;
  static const String& CDftBoundary;
  static const String& CHttpLineBreak;

	typedef HashMapStringToPointer<Formatter> FormatterMap;
	FormatterMap							  hmFormatters;

  void writeValue(const String& strName,
                  const String& strFileName,
                  const String& strBoundary,
                        String  strFormat,
                  const DM::DataObject* dmValue,
							    std::ostream&       ostream,
						      QS::API::Attributes *pAttribute);

  void parseHeader(std::istream& is, String& strPartName, String& strPartType, String& strFileName);

	ThreadSpecific<Workers::Proc::WCM::WorkContextManager>::Pointer  pWorkContext;

	Formatter* getFormatter(const String& strFormatter)const;

	friend class Factory<MultiPartFormatter>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_Fmt_MultiPartFormatter_H_ */
