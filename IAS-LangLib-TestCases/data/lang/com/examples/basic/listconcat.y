/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/withsingle.y
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


PROGRAM createList(VAR street_ AS String)
RETURNS ARRAY OF Address : "http://www.examples.org/akc"
BEGIN

 CREATE result BEGIN
   street = street_;
   block  = 1;
 END;

 CREATE result BEGIN
   street = street_;
   block  = 2;
 END;

 result = result + COPYOF(result);
END;

PROGRAM com::examples::basic::listconcat(VAR p1 AS Integer,
			 			    		 	  VAR input AS Customer : "http://www.examples.org/akc",
		 			    		      VAR output AS Customer : "http://www.examples.org/akc")
BEGIN

  VAR ls1 AS ARRAY OF String;
  VAR ls2 AS ARRAY OF String;

  ls1 = "test1";
  ls1 = "test2";
  ls2 = "test3";

  VAR li1 AS ARRAY OF Integer;
  VAR li2 AS ARRAY OF Integer;

  li1 = "1";
  li1 = "2";
  li2 = "3";

  ls1 = ls1 + ls2;
  li1 = li1 + li2;

  output.firstname = "";

  WITH l AS ls1 DO
   output.firstname = output.firstname + l + ",";

  WITH l AS li1 DO
   output.firstname = output.firstname + l + ",";

  output.address = COPYOF(input.address);
  output.address[1].street = "Check";
  output.address =  COPYOF(input.address) + COPYOF(input.address);

   output.address = output.address + NEW Address : "http://www.examples.org/akc" BEGIN
     street = "Novacky";
   END;

   output.address = output.address  + NEW Address : "http://www.examples.org/akc" BEGIN
     street = "Mazacky";
   END;

   output.address = output.address  + createList("Testing1") + createList("Testing2");

END;
