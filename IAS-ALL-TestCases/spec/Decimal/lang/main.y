IMPORT std::default;
IMPORT std::qs;
IMPORT tc::helpers;

PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
RETURNS String
BEGIN

  ctx.FMT = "String";

  VAR d1 AS Decimal;
  VAR d2 AS Decimal;
  VAR c AS Customer : "http://www.examples.org/akc";

  d1="+98.765";
  d2="-123.432";

  tc::save(ctx,"D01.txt",d2);
  tc::save(ctx,"D02.txt",d1/d2);
  tc::save(ctx,"D03.txt",d1);

  d2 = "1";

  tc::save(ctx,"D04.txt",d2);
  c.money = "9876543210987654.3";

  IF c.money <> "9876543210987654.3"
   THEN THROW "Bad comparison";

  //c.money = c.money + 12.345678;
  //c.money = "0.0";
  //c.money = c.money + (0.4413 AS Float);
  c.bigMoney = "1234.1234";

  ctx.FMT = "JSON";
  tc::save(ctx,"customer.json",c);

END;

