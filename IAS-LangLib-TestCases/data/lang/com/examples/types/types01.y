/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/types/types01.y
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

DEFINE ExampleType : "http://www.examples.org/types" AS
BEGIN
	p1 AS String;
	p2 AS Address : "http://www.invenireaude.org/example";
END;

DEFINE SubExampleType : "http://www.examples.org/types" AS
  EXTENSION OF ExampleType : "http://www.examples.org/types"
 BEGIN
	p3 AS String;
	p4 AS Address : "http://www.invenireaude.org/example";
END;

DEFINE ExampleTypeDef      : "http://www.examples.org/types" AS EXTENSION OF String;
DEFINE ExampleTypeDefShort : "http://www.examples.org/types" AS EXTENSION OF String;
DEFINE ExampleTypeAbstract : "http://www.examples.org/types" ;


DEFINE SubAddress : "http://www.examples.org/types" AS
 EXTENSION OF Address:"http://www.invenireaude.org/example"
BEGIN
	info      AS String;
	alternate AS Address : "http://www.invenireaude.org/example";
END;

PROGRAM com::examples::types::types01(VAR p1 AS Integer,
			 			    		    VAR input AS Customer : "http://www.invenireaude.org/example",
			 			    		    VAR output AS Customer : "http://www.invenireaude.org/example")
BEGIN

   VAR t AS  ExampleType : "http://www.examples.org/types";
   VAR ts AS SubExampleType : "http://www.examples.org/types";
   VAR sa AS SubAddress : "http://www.examples.org/types";

   t.p2 = NEW Address:"http://www.invenireaude.org/example" BEGIN
   	 street="Typowa";
   	 block=102;
   	END;

   WITH t.p2 DO BEGIN
     street = street + " "+ street;
   END;

   ts.p4 = NEW Address:"http://www.invenireaude.org/examplef";
   ts.p4.street="SubStreet";
   ts.p4.block=201;

   VAR ss AS ExampleTypeDef : "http://www.examples.org/types";
   ss= "Extra delivery";
   sa.info = ss;
   sa.alternate = NEW Address:"http://www.invenireaude.org/examplef";
   sa.alternate.street="SubStreet";
   sa.alternate.block=201;

   output = COPYOF(input);

   VAR a AS Address:"http://www.invenireaude.org/example";

   a=t.p2;
   t.p2= NEW  Address:"http://www.invenireaude.org/example";

   output.address=a;

   output.address=COPYOF(ts.p4);
   output.address=COPYOF(sa);

END;
