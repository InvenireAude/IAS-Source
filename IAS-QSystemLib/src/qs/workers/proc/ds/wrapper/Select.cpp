/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Select.cpp
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
#include "Select.h"
#include<qs/log/LogLevel.h>
#include "Lexer.h"

#include <dm/datamodel.h>

#include "exception/ParseException.h"


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {

/*************************************************************************/
Select::Select(::IAS::DS::API::Session* pSession,
			   const ::IAS::DM::Type* pType):
			   tabInputSetters(pType),
			   tabResultSetSetters(pType),
			   bForUpdate(false){

	IAS_TRACER;

	ptrSelect=pSession->createSelect();

	strSQLText = "SELECT ";
}
/*************************************************************************/
Select::~Select() throw(){
	IAS_TRACER;
}
/*************************************************************************/
 String Select::parseColumnNameOrExpr(Lexer* pLexer){
   IAS_TRACER;

  String strResult;

	 pLexer->assetToken(Lexer::T_SYMBOL);
    String strValue = pLexer->getValue();
		bool bQuote = pLexer->isQuoted();

		if(bQuote)
			strResult+='"';

		strResult+=strValue;
    pLexer->nextToken();

		if(bQuote){
			strResult+='"';
    }else{

      if(pLexer->getToken() == Lexer::T_OPENPAR){
        pLexer->assetNext(Lexer::T_SYMBOL);
        strResult+= "(" + pLexer->getValue() + ")";
        pLexer->assetNext(Lexer::T_CLOSEPAR);
        pLexer->nextToken();
      }
    }

  return strResult;
 }
/*************************************************************************/
void Select::parseResult(Lexer* pLexer,
						 ResultSetSettersTable& tabResultSetSetters,
						 Lexer::Token iStopToken,
						 bool bFirst){
	IAS_TRACER;

	Lexer::Token iToken;

	int iCount=0;

	while((iToken=pLexer->nextToken()) != Lexer::T_END){

		if(iToken == iStopToken)
			break;

		if(iCount) {
			pLexer->assetToken(Lexer::T_COMMA);
			iToken=pLexer->nextToken();
		}

		bool bOptional=false;

		if(iToken == Lexer::T_QUESTION_MARK){
			bOptional=true;
			iToken=pLexer->nextToken();
		}

		if(!bFirst || iCount)
			strSQLText+=", ";

		iCount++;

    strSQLText+=parseColumnNameOrExpr(pLexer);

		pLexer->assetToken(Lexer::T_ARROW);
		pLexer->assetNext(Lexer::T_SYMBOL);

		tabResultSetSetters.addXPath(pLexer->getXPathValue(), bOptional);
	}

}
/*************************************************************************/
void Select::parseResultAndFromAndWhere(Lexer* pLexer,
					 	 	 	 	    DM::DataObject* dm,
										ResultSetSettersTable& tabResultSetSetters,
										bool bFirst){
	IAS_TRACER;

	Lexer::Token iToken;

	parseResult(pLexer, tabResultSetSetters, Lexer::T_FROM, bFirst);

	pLexer->assetToken(Lexer::T_FROM);

	pLexer->assetNext(Lexer::T_SYMBOL);

	strSQLText+=" FROM ";
	strSQLText+=pLexer->getValue();
	strSQLText+="";

	if(pLexer->nextToken() == Lexer::T_WHERE)
		handleWhere(pLexer,tabInputSetters,dm);

  if(pLexer->getToken() == Lexer::T_GROUP){
    pLexer->assetNext(Lexer::T_BY);
    parseGroupBy(pLexer);
  }

	if(pLexer->getToken() == Lexer::T_ORDER){
      pLexer->assetNext(Lexer::T_BY);
      switch(iToken = pLexer->nextToken()){
        case Lexer::T_SYMBOL:
            parseOrderBy(pLexer);
          break;
        case Lexer::T_MAP :
            parseOrderByMap(pLexer, dm);
          break;
        default:
          IAS_THROW(ParseException(String("Expected 'ORDER BY' or 'ORDER BY MAP' sepecification, got:") +
            pLexer->getPrintable(iToken),pLexer->getLine()));
      }
  }

	if(pLexer->getToken() == Lexer::T_FOR){
		pLexer->assetNext(Lexer::T_UPDATE);
		bForUpdate=true;

		strSQLText+=" FOR UPDATE ";
    pLexer->nextToken();
	}

	pLexer->assetToken(Lexer::T_END);
}
/*************************************************************************/
void Select::parseGroupBy(Lexer *pLexer){
  IAS_TRACER;

  pLexer->nextToken();
	strSQLText+=" GROUP BY ";
  bool bFirst = true;
	do{

      if(!bFirst){
        pLexer->nextToken();
        strSQLText+=", ";
      }

     strSQLText+=parseColumnNameOrExpr(pLexer);
     bFirst = false;

    }while(pLexer->getToken() == Lexer::T_COMMA);

  if(bFirst){
    IAS_THROW(BadUsageException("A column name expected after GROUP BY."));
  }

}
/*************************************************************************/
void Select::parseOrderBy(Lexer *pLexer){
  IAS_TRACER;

  bool bFirst = true;
  strSQLText+=" ORDER BY ";
  strSQLText+=parseOrderByText(pLexer);
}
/*************************************************************************/
void Select::parseOrderByMap(Lexer *pLexer, DM::DataObject* dm){
  IAS_TRACER;

  String strMapValue = "_";
  bool bHasMatch = false;

  if(!dm){
    IAS_THROW(BadUsageException("Cannot use SQL: ORDER BY MAP with the NULL dataobject value."));
  }

  pLexer->assetNext(Lexer::T_SYMBOL);
  String strXPath = pLexer->getXPathValue();

  if(dm->isSet(strXPath)){
    strMapValue = dm->getString(strXPath);
  }

  pLexer->assetNext(Lexer::T_OPENPAR);

  do{

    pLexer->assetNext(Lexer::T_SYMBOL);
    String strValue = pLexer->getXPathValue();

    pLexer->assetNext(Lexer::T_ARROW);
    pLexer->assetNext(Lexer::T_OPENPAR);

    String strOrderByText;

    if(pLexer->nextToken() != Lexer::T_CLOSEPAR){
       strOrderByText = parseOrderByText(pLexer);
    }
    pLexer->assetToken(Lexer::T_CLOSEPAR);

    if(strMapValue.compare(strValue) == 0){

      if(!strOrderByText.empty())
        strSQLText += " ORDER BY " +strOrderByText;
      bReusable = false;
      bHasMatch = true;
    }

  }while(pLexer->nextToken() == Lexer::T_COMMA);

  pLexer->assetToken(Lexer::T_CLOSEPAR);

  if(!bHasMatch){
    IAS_THROW(BadUsageException("Cannot use SQL: ORDER BY MAP with the empty value of: " + strXPath + " and no default value ('_') set."));
  }
  pLexer->nextToken();

}
/*************************************************************************/
String Select::parseOrderByText(Lexer *pLexer){
  IAS_TRACER;

  String strResult;
  bool bFirst = true;
	do{

      if(!bFirst){
        pLexer->nextToken();
        strResult+=", ";
      }

      strResult += parseColumnNameOrExpr(pLexer);

      switch(pLexer->getToken()){
        case Lexer::T_ASC:
          strResult+=" ASC";
          pLexer->nextToken();
        break;
        case Lexer::T_DESC:
          strResult+=" DESC";
          pLexer->nextToken();
        break;
        default:
          strResult+=" ASC";
      }

      bFirst = false;

    }while(pLexer->getToken() == Lexer::T_COMMA);

  return strResult;
}
/*************************************************************************/
}
}
}
}
}
}
