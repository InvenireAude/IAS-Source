

PROGRAM wrap::insertCustomer(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				             VAR data    AS Customer : "http://www.invenireaude.org/example")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"INSERT INTO CUSTOMER
   data.id  => id,
   ? data.firstname  => firstname,
   ? data.middlename => middlename,
   ? data.lastname   => lastname,
   ? data.age        => age,
   ? data.money      => money,
   ? data.birthDate  => birthDate,
   ? data.wakeup     => wakeup,
   ? data.updated    => updated,
   ? data.photo      => rawdata
");

//   ? data            => rawdata
PROGRAM getCode(VAR a AS Address:"http://www.invenireaude.org/example")
RETURNS String
BEGIN
   IF a ISTYPE(Address:"http://www.invenireaude.org/examplef") THEN BEGIN
       RETURN "F";
 	 END ELSE BEGIN
       RETURN "C";
     END;
END;


PROGRAM wrap::insertAddress(VAR ctx       AS Context  : "http://www.invenireaude.org/qsystem/workers",
							VAR cid       AS String,
				            VAR address   AS Address  : "http://www.invenireaude.org/example",
				            VAR type       AS String)
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"INSERT INTO ADDRESS
   cid => 'CUSTOMER_ID',
   address.street =>  STREET,
   address.block  =>  BLOCK,
   type   =>  TYPE
");
