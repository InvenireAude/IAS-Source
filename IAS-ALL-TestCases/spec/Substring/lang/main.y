IMPORT std::default;
IMPORT std::qs;
IMPORT std::fmt;
IMPORT tc::helpers;


PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
BEGIN

  VAR value AS String;
  VAR json AS String;

  value =
        "Dwudziestego Ósmego Czerwca Tysiąc Dziewięćset Pięćdziesiątego";
  value = std::substring(value,13,33);

  tc::save("String","S01.txt",value);

  IF std::strlen(value) == 33 THEN
    value = std::substring(value,0,6);

  tc::save("String","S02.txt",value);
  tc::save("JSON","S02.json",value);

  json = fmt::serialize("JSON",value);
  VAR s AS String;
  s =fmt::parse("JSON", json);

  IF s <> value THEN
    THROW "Test case failed: s != value";

END;

