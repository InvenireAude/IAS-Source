IMPORT std::default;
IMPORT std::qs;
IMPORT tc::helpers;

DEFINE MyArray : "http://www.examples.org/akc" AS BEGIN
 values AS ARRAY OF String;
END;

PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
BEGIN

  ctx.MID = "Message.txt";
  ctx.FMT = "String";

  VAR s AS String;
  VAR list AS MyArray : "http://www.examples.org/akc";

  s = "BĄK|PAŁKA|ZAPAŁKA|ĄĆŹŻ";
  list.values = std::split(s,"|");

  tc::save("JSON","list01.json",list);

  s = std::replace(s,"|","\n");
  s = std::replace(s,"ĄĆ","ąć");

  list.values = std::split(s,"\n");
  tc::save("JSON","list02.json",list);

  list.values = std::split("BĄK|PAŁKA|ZAPAŁKA|ĄĆŹŻ","Ą");
  tc::save("JSON","list03.json",list);

END;

