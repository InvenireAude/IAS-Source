IMPORT std::default;
IMPORT std::qs;

PROGRAM std::applyTemplate(VAR pattern AS String, VAR args AS AnyType)
RETURNS String
EXTERNAL "libIASQSystemLib:ias_qs_lang_tools_proxy:ApplyTemplate"(
"templatefun"
);


PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
RETURNS AnyType
BEGIN

  ctx.MID = "Template.txt";
  ctx.FMT = "String";

  VAR ctxTest   AS Context  : "http://www.invenireaude.org/qsystem/workers";

  ctxTest.attributes = std::newAttribute("a1","v1");
  ctxTest.attributes = std::newAttribute("a2","v2");

	RETURN std::applyTemplate(
      "START${*attributes}\n${name}:${value}\t F1=${:template::dump()}\t F2=${:template::test(name)}${*attributes}\nEND",
      ctxTest);

END;