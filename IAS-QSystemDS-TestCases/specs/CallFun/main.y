
IMPORT std::default;
IMPORT wrap::fun;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data   AS Customer : "http://www.invenireaude.org/example")
RETURNS Customer : "http://www.invenireaude.org/example"
BEGIN

  data.age = (wrap::callfun(data) AS Integer);

  RETURN data;

END;