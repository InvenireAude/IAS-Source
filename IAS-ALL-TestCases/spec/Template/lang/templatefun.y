
IMPORT std::fmt;

PROGRAM template::test(VAR id AS String)
RETURNS String
BEGIN
 RETURN "ID: " + id + "\n";
END;

PROGRAM template::dump(VAR a AS AnyType)
RETURNS String
BEGIN
  RETURN fmt::serialize("JSON",a);
END;