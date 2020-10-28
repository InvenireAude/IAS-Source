/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/cast.y
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
IMPORT std::default;


/****************************************************************/
/* String                                                      */
/****************************************************************/

PROGRAM com::examples::basic::relation::testString(VAR name AS String)
BEGIN

 VAR v1 AS String;
 VAR v2 AS String;
 VAR v3 AS String;

 v1 = "abc";
 v2 = "abc";
 v3 = "abdef";

 IF NOT (v1 == v2) THEN THROW "TC failed: 'v1 == v2': " + name ;
 IF (v2 == v3) THEN THROW "TC failed: 'v2 == v3': " + name ;

 IF NOT (v3 <> v2) THEN THROW "TC failed: 'v3 <> v2': " + name ;
 IF (v1 <> v2) THEN THROW "TC failed: 'v1 <> v2': " + name ;

 IF (v2 > v3) THEN THROW "TC failed: 'v2 > v3': " + name ;
 IF (v3 < v1) THEN THROW "TC failed: 'v3 > v1': " + name ;
 IF NOT (v3 > v2) THEN THROW "TC failed: 'v3 > v2': " + name ;
 IF NOT (v2 < v3) THEN THROW "TC failed: 'v2 < v3': " + name ;

 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v1) THEN THROW "TC failed: 'v3 >= v1': " + name ;
 IF NOT (v3 >= v2) THEN THROW "TC failed: 'v3 >= v2': " + name ;
 IF NOT (v2 <= v3) THEN THROW "TC failed: 'v2 <= v3': " + name ;

 IF NOT (v1 <= v2) THEN THROW "TC failed: 'v1 <= v2': " + name ;
 IF NOT (v1 >= v2) THEN THROW "TC failed: 'v1 >= v2': " + name ;
 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v2) THEN THROW "TC failed: 'v2 <= v3': " + name ;

END;

/****************************************************************/
/* Integer                                                      */
/****************************************************************/

PROGRAM com::examples::basic::relation::testInteger(VAR name AS String)
BEGIN

 VAR v1 AS Integer;
 VAR v2 AS Integer;
 VAR v3 AS Integer;

 v1 = -123;
 v2 = -100-23;
 v3 = 124;

 IF NOT (v1 == v2) THEN THROW "TC failed: 'v1 == v2': " + name ;
 IF (v2 == v3) THEN THROW "TC failed: 'v2 == v3': " + name ;

 IF NOT (v3 <> v2) THEN THROW "TC failed: 'v3 <> v2': " + name ;
 IF (v1 <> v2) THEN THROW "TC failed: 'v1 <> v2': " + name ;

 IF (v2 > v3) THEN THROW "TC failed: 'v2 > v3': " + name ;
 IF (v3 < v1) THEN THROW "TC failed: 'v3 > v1': " + name ;
 IF NOT (v3 > v2) THEN THROW "TC failed: 'v3 > v2': " + name ;
 IF NOT (v2 < v3) THEN THROW "TC failed: 'v2 < v3': " + name ;

 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v1) THEN THROW "TC failed: 'v3 >= v1': " + name ;
 IF NOT (v3 >= v2) THEN THROW "TC failed: 'v3 >= v2': " + name ;
 IF NOT (v2 <= v3) THEN THROW "TC failed: 'v2 <= v3': " + name ;

 IF NOT (v1 <= v2) THEN THROW "TC failed: 'v1 <= v2': " + name ;
 IF NOT (v1 >= v2) THEN THROW "TC failed: 'v1 >= v2': " + name ;
 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v2) THEN THROW "TC failed: 'v2 <= v3': " + name ;

END;

/****************************************************************/
/* Decimal                                                      */
/****************************************************************/

PROGRAM com::examples::basic::relation::testDecimal(VAR name AS String)
BEGIN

 VAR v1 AS Decimal;
 VAR v2 AS Decimal;
 VAR v3 AS Decimal;

 v1 = "123.45";
 v2 = "00123.4500";
 v3 = "124";

 IF NOT (v1 == v2) THEN THROW "TC failed: 'v1 == v2': " + name ;
 IF (v2 == v3) THEN THROW "TC failed: 'v2 == v3': " + name ;

 IF NOT (v3 <> v2) THEN THROW "TC failed: 'v3 <> v2': " + name ;
 IF (v1 <> v2) THEN THROW "TC failed: 'v1 <> v2': " + name ;

 IF (v2 > v3) THEN THROW "TC failed: 'v2 > v3': " + name ;
 IF (v3 < v1) THEN THROW "TC failed: 'v3 > v1': " + name ;
 IF NOT (v3 > v2) THEN THROW "TC failed: 'v3 > v2': " + name ;
 IF NOT (v2 < v3) THEN THROW "TC failed: 'v2 < v3': " + name ;

 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v1) THEN THROW "TC failed: 'v3 >= v1': " + name ;
 IF NOT (v3 >= v2) THEN THROW "TC failed: 'v3 >= v2': " + name ;
 IF NOT (v2 <= v3) THEN THROW "TC failed: 'v2 <= v3': " + name ;

 IF NOT (v1 <= v2) THEN THROW "TC failed: 'v1 <= v2': " + name ;
 IF NOT (v1 >= v2) THEN THROW "TC failed: 'v1 >= v2': " + name ;
 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v2) THEN THROW "TC failed: 'v2 <= v3': " + name ;

END;

/****************************************************************/
/* Float                                                      */
/****************************************************************/

PROGRAM com::examples::basic::relation::testFloat(VAR name AS String)
BEGIN

 VAR v1 AS Float;
 VAR v2 AS Float;
 VAR v3 AS Float;

 v1 = 123.45;
 v2 = "00123.4500";
 v3 = "124";

 IF NOT (v1 == v2) THEN THROW "TC failed: 'v1 == v2': " + name ;
 IF (v2 == v3) THEN THROW "TC failed: 'v2 == v3': " + name ;

 IF NOT (v3 <> v2) THEN THROW "TC failed: 'v3 <> v2': " + name ;
 IF (v1 <> v2) THEN THROW "TC failed: 'v1 <> v2': " + name ;

 IF (v2 > v3) THEN THROW "TC failed: 'v2 > v3': " + name ;
 IF (v3 < v1) THEN THROW "TC failed: 'v3 > v1': " + name ;
 IF NOT (v3 > v2) THEN THROW "TC failed: 'v3 > v2': " + name ;
 IF NOT (v2 < v3) THEN THROW "TC failed: 'v2 < v3': " + name ;

 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v1) THEN THROW "TC failed: 'v3 >= v1': " + name ;
 IF NOT (v3 >= v2) THEN THROW "TC failed: 'v3 >= v2': " + name ;
 IF NOT (v2 <= v3) THEN THROW "TC failed: 'v2 <= v3': " + name ;

 IF NOT (v1 <= v2) THEN THROW "TC failed: 'v1 <= v2': " + name ;
 IF NOT (v1 >= v2) THEN THROW "TC failed: 'v1 >= v2': " + name ;
 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v2) THEN THROW "TC failed: 'v2 <= v3': " + name ;

END;

/****************************************************************/
/* Long                                                         */
/****************************************************************/

PROGRAM com::examples::basic::relation::testLong(VAR name AS String)
BEGIN

 VAR v1 AS Long;
 VAR v2 AS Long;
 VAR v3 AS Long;

 v1 = 10012345;
 v2 = 10012345L;
 v3 = 101567899998L;

 IF NOT (v1 == v2) THEN THROW "TC failed: 'v1 == v2': " + name ;
 IF (v2 == v3) THEN THROW "TC failed: 'v2 == v3': " + name ;

 IF NOT (v3 <> v2) THEN THROW "TC failed: 'v3 <> v2': " + name ;
 IF (v1 <> v2) THEN THROW "TC failed: 'v1 <> v2': " + name ;

 IF (v2 > v3) THEN THROW "TC failed: 'v2 > v3': " + name ;
 IF (v3 < v1) THEN THROW "TC failed: 'v3 > v1': " + name ;
 IF NOT (v3 > v2) THEN THROW "TC failed: 'v3 > v2': " + name ;
 IF NOT (v2 < v3) THEN THROW "TC failed: 'v2 < v3': " + name ;

 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v1) THEN THROW "TC failed: 'v3 >= v1': " + name ;
 IF NOT (v3 >= v2) THEN THROW "TC failed: 'v3 >= v2': " + name ;
 IF NOT (v2 <= v3) THEN THROW "TC failed: 'v2 <= v3': " + name ;

 IF NOT (v1 <= v2) THEN THROW "TC failed: 'v1 <= v2': " + name ;
 IF NOT (v1 >= v2) THEN THROW "TC failed: 'v1 >= v2': " + name ;
 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v2) THEN THROW "TC failed: 'v2 <= v3': " + name ;

END;

/****************************************************************/
/* Date                                                         */
/****************************************************************/

PROGRAM com::examples::basic::relation::testDate(VAR name AS String)
BEGIN

 VAR v1 AS Date;
 VAR v2 AS Date;
 VAR v3 AS Date;

 v1 = "2020-01-01";
 v2 = "2020-01-01";
 v3 = "2020-02-02";

 IF NOT (v1 == v2) THEN THROW "TC failed: 'v1 == v2': " + name ;
 IF (v2 == v3) THEN THROW "TC failed: 'v2 == v3': " + name ;

 IF NOT (v3 <> v2) THEN THROW "TC failed: 'v3 <> v2': " + name ;
 IF (v1 <> v2) THEN THROW "TC failed: 'v1 <> v2': " + name ;

 IF (v2 > v3) THEN THROW "TC failed: 'v2 > v3': " + name ;
 IF (v3 < v1) THEN THROW "TC failed: 'v3 > v1': " + name ;
 IF NOT (v3 > v2) THEN THROW "TC failed: 'v3 > v2': " + name ;
 IF NOT (v2 < v3) THEN THROW "TC failed: 'v2 < v3': " + name ;

 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v1) THEN THROW "TC failed: 'v3 >= v1': " + name ;
 IF NOT (v3 >= v2) THEN THROW "TC failed: 'v3 >= v2': " + name ;
 IF NOT (v2 <= v3) THEN THROW "TC failed: 'v2 <= v3': " + name ;

 IF NOT (v1 <= v2) THEN THROW "TC failed: 'v1 <= v2': " + name ;
 IF NOT (v1 >= v2) THEN THROW "TC failed: 'v1 >= v2': " + name ;
 IF (v2 >= v3) THEN THROW "TC failed: 'v2 >= v3': " + name ;
 IF (v3 <= v2) THEN THROW "TC failed: 'v2 <= v3': " + name ;

END;

/****************************************************************/
/* Raw                                                         */
/****************************************************************/

PROGRAM com::examples::basic::relation::testRaw(VAR name AS String)
BEGIN

 VAR v1 AS Raw;
 VAR v2 AS Raw;
 VAR v3 AS Raw;

 v1 = "YWJjZA==";
 v2 = "YWJjZA==";
 v3 = "YWJj";

 IF NOT (v1 == v2) THEN THROW "TC failed: 'v1 == v2': " + name ;
 IF (v2 == v3) THEN THROW "TC failed: 'v2 == v3': " + name ;

 IF NOT (v3 <> v2) THEN THROW "TC failed: 'v3 <> v2': " + name ;
 IF (v1 <> v2) THEN THROW "TC failed: 'v1 <> v2': " + name ;

END;


/****************************************************************/


PROGRAM com::examples::basic::relation(VAR p1     AS Integer,
			 			    	   VAR input  AS Customer : "http://www.invenireaude.org/example",
			 			    	   VAR output AS Customer : "http://www.invenireaude.org/example")
BEGIN

  com::examples::basic::relation::testString("String");

  com::examples::basic::relation::testInteger("Integer");
  com::examples::basic::relation::testDecimal("Decimal");
  com::examples::basic::relation::testFloat("Float");
  com::examples::basic::relation::testLong("Long");

  com::examples::basic::relation::testDate("Date");

  com::examples::basic::relation::testRaw("Raw");
END;
