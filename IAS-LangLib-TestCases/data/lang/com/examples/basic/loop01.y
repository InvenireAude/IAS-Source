/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/basic/loop01.y
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

IMPORT com::examples::utility;
IMPORT com::examples::printer;
IMPORT com::examples::multi;
IMPORT com::examples::newaddress;

PROGRAM com::examples::basic::loop01(VAR p1 AS Integer,
			 			    		 VAR input AS Customer : "http://www.invenireaude.org/example",
			 			    		 VAR output AS Customer : "http://www.invenireaude.org/example")
BEGIN

   VAR i AS Integer;

   i=0;
   WHILE i < 10 DO
     BEGIN
       VAR a AS Address:"http://www.invenireaude.org/example";

       IF (i % 2) == 0 THEN BEGIN
         a =  NEW Address:"http://www.invenireaude.org/example";
       END ELSE
         a =  NEW Address:"http://www.invenireaude.org/examplef";

       a.street="Nowa";
       a.block=i;

       input.address=a;
       i=i+1;
  	 END;

   i=0;
   WHILE i < SIZEOF(input.address) DO
     BEGIN
        VAR tmp AS Address:"http://www.invenireaude.org/example";
        tmp = input.address[i];

        IF NOT ISNULL(tmp) THEN BEGIN

        	IF tmp ISINSTANCE (Address:"http://www.invenireaude.org/example") THEN
        		BEGIN
        			tmp.street = TYPE(tmp) + ":" + TYPENS(tmp);
        		END;

        	tmp.block = STRLEN(tmp.street) + i;
        END;

        i=i+1;
     END;

   //input.age=std::rand();
   output=COPYOF(input);

END;