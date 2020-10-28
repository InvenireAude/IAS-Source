PROGRAM wrap::callfun(VAR data    AS Customer : "http://www.invenireaude.org/example")
RETURNS Long
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"CALL INTO result GETNUM(
      data.age =>
    )
");
