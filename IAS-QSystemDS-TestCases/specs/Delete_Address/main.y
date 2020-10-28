
IMPORT std::default;
IMPORT wrap::fetch;
IMPORT wrap::delete;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS Customer : "http://www.invenireaude.org/example")
RETURNS Customer : "http://www.invenireaude.org/example"
BEGIN


  wrap::deleteAddresses(ctx,data);

  wrap::fetchCustomer(ctx,data);
  wrap::fetchAddresses(ctx,data);

  RETURN data;

END;