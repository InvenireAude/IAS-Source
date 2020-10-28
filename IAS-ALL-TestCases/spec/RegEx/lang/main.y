IMPORT std::default;
IMPORT std::qs;
IMPORT tc::helpers;

PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
BEGIN

  VAR s AS String;

  s = "<html> <html class = \"\"> to jest ok </p> dobry tekst <body>";

  tc::save("String","S01.txt", std::replaceRegExp(s,"<[a-zA-Z0-9/ =\"\']*>","XX"));

  tc::save("String","S02.txt", std::replaceRegExp(s,"<","XX"));

  VAR value AS String;
  VAR regex AS String;

  value = "test</bold-and-bold a.b=\"test\">test";
  //regex = "<[a-zA-Z0-9_\/:\.\- =\"\']*>";
  //tc::save("String","S03.txt", regex + " | " + std::replaceRegExp(value,regex," "));

  regex = "<[a-zA-Z0-9_\/\:\.\\- =\"\']*>";
  tc::save("String","S04.txt", regex + " | " + std::replaceRegExp(value,regex," "));

  regex = "<[a-zA-Z0-9_\\/:.\\- =\"']*>";
  tc::save("String","S05.txt", regex + " | " + std::replaceRegExp(value,regex," "));

END;