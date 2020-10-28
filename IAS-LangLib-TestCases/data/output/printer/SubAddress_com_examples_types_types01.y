
DEFINE SubAddress : "http://www.examples.org/types" AS 
 EXTENSION OF Address : "http://www.invenireaude.org/example"
BEGIN
   info AS String;
   alternate AS Address : "http://www.invenireaude.org/example" ;
END;
