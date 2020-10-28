PROGRAM wrap::deleteAddresses(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				              VAR data    AS Customer : "http://www.invenireaude.org/example")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"DELETE FROM ADDRESS
 WHERE 'CUSTOMER_ID' = data.id
");
