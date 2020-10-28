IMPORT std::default;
IMPORT std::qs;
CREATE ALIAS "abc" AS "http://www.invenireaude.org/qsystem/workers";

DEFINE dateTime : "http://www.w3.org/2001/XMLSchema-instance" AS
EXTENSION OF DateTime : "IAS/DM/Default";

DEFINE integer : "http://www.w3.org/2001/XMLSchema-instance" AS
EXTENSION OF Integer : "IAS/DM/Default";

PROGRAM main(
	VAR ctx   AS Context  : "abc",
	VAR data  AS AnyType
)
BEGIN

    ctx.FMT = "XML";

    VAR ts AS dateTime : "http://www.w3.org/2001/XMLSchema-instance";

    ts = "2020-10-20T10:20:30";
	  std::save("/tmp/t.xml", ts);
    ts = std::load("/tmp/t.xml");

    ctx.MID = "datetime.xml";
    std::send("output",ctx,ts);

    VAR i AS integer : "http://www.w3.org/2001/XMLSchema-instance";
    i = 99;
	  std::save("/tmp/i.xml", i);
    i = std::load("/tmp/i.xml");

    ctx.MID = "integer.xml";
    std::send("output",ctx,i);

END;