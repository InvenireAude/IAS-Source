IMPORT std::default;
IMPORT std::qs;

PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
RETURNS String
BEGIN
 ctx.MID = "Message.txt";
 ctx.FMT = "String";

 CREATE ctx.attributes BEGIN
   name = "name";
   value = "abc";
 END;

 VAR d AS Long;
 d = 1L;
 IF ctx.attributes[0].value == "ABC" THEN
   RETURN "Bład";

// This is static check exception
//  IF 1 == "ABC" THEN
//    RETURN "Bład";

IF ctx.attributes[0].value == 1 THEN
   RETURN "Bład";

// This is static check exception
// IF 1 == std::copyRawToString(("YWJjCg==" AS Raw)) THEN
//    RETURN "Bład";

  RETURN "OK";
END;
