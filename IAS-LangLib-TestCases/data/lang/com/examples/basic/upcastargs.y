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


 PROGRAM testfun(VAR n AS Name : "http://www.examples.org/akc")
 RETURNS Name : "http://www.examples.org/akc"
 BEGIN
  RETURN (n AS String);
 END;




PROGRAM com::examples::basic::upcastargs(VAR p1 AS Integer,
			 			    		 	   VAR input AS Customer : "http://www.examples.org/akc",
			 			    		     VAR output AS Customer : "http://www.examples.org/akc")
BEGIN


 VAR s AS String;
 VAR n AS Name : "http://www.examples.org/akc";
 s = "string1";
 n = s;

 testfun("a");
 output.firstname = testfun(s);
 output.lastname = testfun(n);
 output.someText = (testfun("string2") AS String);

END;





