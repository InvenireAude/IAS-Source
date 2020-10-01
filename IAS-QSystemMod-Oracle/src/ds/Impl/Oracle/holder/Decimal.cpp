/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-Oracle/src/ds/Impl/Oracle/holder/Decimal.cpp
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License.
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 *
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 *
 */
#include "Decimal.h"
#include <ds/Impl/Oracle/Session.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace Oracle {
namespace Holder {

/*************************************************************************/
Decimal::Decimal(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQLT_VNU),
   strFormat("99999999999999999"){

  IAS_TRACER;

  int iPrecision = pSetter->getTargetType()->getRestrictionFractionDigits();

  if(iPrecision){

    strFormat+=".";

    while(iPrecision-- > 0){
      strFormat+="9";
    }

  }
   ::IAS::Long iValue = 0L;
    sword rc = OCINumberFromInt(
                pStatement->getSession()->getErrorHandle(),
                &iValue,
                sizeof(::IAS::Long),
                OCI_NUMBER_SIGNED,
			          bufData.getBuffer<OCINumber>());
}
/*************************************************************************/
Decimal::~Decimal() throw(){
	IAS_TRACER;
}
/*************************************************************************/
class RawDecimalHolder : public ::IAS::Decimal{

public:
  RawDecimalHolder(const Decimal&d):
    Decimal(d){};

  long long getLongLongRaw(){
    return getRawValue();
  }
};
/*************************************************************************/
void Decimal::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath()<<" "<<strFormat);

	if(bNull == -1) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{

    char buf[100];
    ub4  bufs=99;

    sword rc = OCINumberToText(
                pStatement->getSession()->getErrorHandle(),
                bufData.getBuffer<OCINumber>(),
                (oratext*)strFormat.c_str(),
                strFormat.length()
                ,0,0,
			          &bufs,(oratext*)buf);

	  OracleException::ThrowOnError("OCINumberToText", pStatement->getSession()->getErrorHandle(), rc);
    String s(buf);
    ::IAS::Decimal d(s);
		pSetter->setDecimal(dm, d);
	}

}
/*************************************************************************/
void Decimal::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),pSetter->getXPath());


	if(pSetter->isNotNull(dm)){

  	IAS_LOG(LogLevel::INSTANCE.isData(),"value:["<<pSetter->getValue(dm)->toDecimal()<<"]");

    RawDecimalHolder d(pSetter->getValue(dm)->toDecimal());
    long long lValue (d.getLongLongRaw());

    OCINumber n;

    sword rc = OCINumberFromInt(
                pStatement->getSession()->getErrorHandle(),
                &lValue,
                sizeof(lValue),
                OCI_NUMBER_SIGNED,
			          &n);

	  OracleException::ThrowOnError("OCINumberFromInt(decimal)", pStatement->getSession()->getErrorHandle(), rc);

    OCINumberShift( pStatement->getSession()->getErrorHandle(),
                    &n,
                    -d.getPrecision(),
                    bufData.getBuffer<OCINumber>()
                   );
		bNull=0;

	}else{
		IAS_LOG(LogLevel::INSTANCE.isData(),"is NULL");
		bNull=-1;
	}

}
/*************************************************************************/
}
}
}
}
}
