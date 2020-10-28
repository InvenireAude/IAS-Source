
IMPORT std::default;
IMPORT wrap::call;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data   AS Customer : "http://www.invenireaude.org/example")
RETURNS Customer : "http://www.invenireaude.org/example"
BEGIN

  wrap::calladd(data);

  RETURN data;

END;