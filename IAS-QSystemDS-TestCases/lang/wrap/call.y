PROGRAM wrap::calladd(VAR data    AS Customer : "http://www.invenireaude.org/example")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"CALL TESTADD(
      data.id   => ,
	    data.age  <> ,
	    data.lastname <=
   )
");

PROGRAM wrap::calladdpq(VAR data    AS Customer : "http://www.invenireaude.org/example")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"CALL TESTADD(
      data.id   => ,
	    data.age  <> ,
	    data.age1 <>
   )
");