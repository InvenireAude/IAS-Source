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
 RETURN "Hello World!";
END;

