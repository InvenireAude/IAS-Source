/*
 * File: IAS-LangLib-TestCases/data/lang/com/examples/utilitytabresult.y
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
IMPORT com::examples::printer;

PROGRAM com::examples::utilitytabresult(VAR number AS ARRAY OF Integer, VAR street AS String)
RETURNS ARRAY OF Address:"http://www.invenireaude.org/example"
BEGIN

 VAR result AS ARRAY OF Address:"http://www.invenireaude.org/example";

 VAR i AS Integer;

  i=0;
  WHILE i < number[0] DO
    BEGIN
       VAR a AS Address:"http://www.invenireaude.org/example";

       IF (i % 2) == 0 THEN BEGIN
         a =  NEW Address:"http://www.invenireaude.org/example";
       END ELSE
         a =  NEW Address:"http://www.invenireaude.org/examplef";

       a.street=street;
       a.block=i;

       result=a;
       i=i+1;
  	 END;


 RETURN result;

END;
