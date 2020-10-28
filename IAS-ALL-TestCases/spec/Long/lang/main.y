IMPORT std::default;
IMPORT std::qs;

PROGRAM fun()
RETURNS Long
BEGIN
 RETURN 5L;
END;


PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
RETURNS TestLong : "http://www.invenireaude.org/example"
BEGIN

  VAR l AS Long;
  VAR s AS String;
  l = 8589934592L;
  s = l;
  result.dd = (l AS Decimal);
  result.dd = ("2020.00" AS Decimal) / "20.20";
  result.value = 1000;
  result.value2 = "12345";
  result.tab = l;
  result.tab = 13L + fun();
  result.tab = 10012345678901L * 100;
  result.ii = (result.tab[2] AS Integer);
  result.tab = 10012345678901L;

  ctx.MID = "long.json";
  ctx.FMT = "JSON";

END;

