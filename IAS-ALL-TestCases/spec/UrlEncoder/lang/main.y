IMPORT std::default;
IMPORT std::qs;
IMPORT std::fmt;
IMPORT tc::helpers;

DEFINE UrlData : "http://www.invenireaude.org/example" AS BEGIN
 sometext1 AS String;
 sometext2 AS String;
 someval   AS Integer;
END;

PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
RETURNS UrlData : "http://www.invenireaude.org/example"
BEGIN

 VAR data AS UrlData : "http://www.invenireaude.org/example";
 data.sometext1 = "A B C";
 data.someval   = 1;

 tc::save("String","url.txt",fmt::serialize("URLEnc",data));

 VAR url AS String;
 ctx.attributes = std::newAttribute("URLpt", "http://www.invenireaude.org/example#UrlData");

 url="http::/localhost/a?sometext1=xyz&someval=1&sometext2=a%20b%20c";
 result = fmt::parse("URLEnc",url,ctx.attributes);
 tc::save("JSON","fullurl.json",fmt::serialize("URLEnc",data));

 url="sometext1=XYZ&someval=666&sometext2=A%20B%20C";
 result = fmt::parse("URLEnc",url,ctx.attributes);
 tc::save("JSON","shorturl.json",fmt::serialize("URLEnc",data));

 ctx.MID = "url.json";
 ctx.FMT = "JSON";

 url="someval=666";
 result = fmt::parse("URLEnc",url,ctx.attributes);
END;

