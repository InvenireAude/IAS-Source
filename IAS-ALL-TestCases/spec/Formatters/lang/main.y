IMPORT std::default;
IMPORT std::qs;
IMPORT std::fmt;
IMPORT tc::helpers;


PROGRAM createObj()
RETURNS Customer : "http://www.invenireaude.org/example"
BEGIN
 WITH result DO BEGIN

  id         = "ID123";
  firstname  = "John";
  lastname   = "Doe";
  middlename = "Middle";
  age        = 66;
  age1       = " 99";
  birth      = "1954-01-02T10:20:30";
  count = 99;
  money = "12.345";
  bigMoney = "12.345";
  wakeup = "05:06:07";
  birthDate = "1954-01-02";
  updated = "2019-12-24T10:20:30";

  photo = "SGVsbG9Xb3JsZAo=";
	misc = NEW Context  : "http://www.invenireaude.org/qsystem/workers";
	info = "some info";
  attr = "attribute";
  extra = "extra data";

  CREATE address BEGIN
    street = "Long St.";
    city   = "New York";
    block  = "101";
  END;


  CREATE mailingAddress BEGIN
    street = "Nearby St.";
    city   = "New York";
    block  = "105";
  END;

  address = NEW Address :  "http://www.invenireaude.org/examplef" BEGIN
    street = "Dark St.";
    city   = "San Sebastian";
    block  = "666";
    country = "San Marino";
    backup.info = "no backup";
  END;

 END;
END;

PROGRAM testFormat(
  VAR c AS Customer : "http://www.invenireaude.org/example",
  VAR f AS String
 )
BEGIN
 VAR s   AS String;
 VAR s2   AS String;
 VAR c2 AS Customer : "http://www.invenireaude.org/example";
 VAR ctx AS Context  : "http://www.invenireaude.org/qsystem/workers";

 s  = fmt::serialize(f,c,ctx.attributes);
 c2 = fmt::parse(f,s,ctx.attributes);
 s2  = fmt::serialize(f,c2,ctx.attributes);

 tc::save("String","payload1."+std::toLower(f), s);
 tc::save("String","payload2."+std::toLower(f), s2);

END;

PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)BEGIN
 VAR c AS Customer : "http://www.invenireaude.org/example";
 c = createObj();
 testFormat(c, "JSON");
 testFormat(c, "XML");
END;

