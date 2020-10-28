IMPORT std::default;
IMPORT std::qs;

PROGRAM testf(
 VAR v AS Customer : "http://www.examples.org/akc"
)
RETURNS Customer : "http://www.examples.org/akc"
BEGIN
 v.firstname="John";
 RETURN v;
END;

PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
RETURNS AnyType
BEGIN

 VAR v AS Customer : "http://www.examples.org/akc";
 v.lastname="Wayne";

 ctx.MID = "Message.json";
 ctx.FMT = "JSON";

 RETURN testf(COPYOF(v));

END;


