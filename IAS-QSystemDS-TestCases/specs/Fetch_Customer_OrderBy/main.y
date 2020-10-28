
IMPORT std::default;
IMPORT wrap::fetch;

PROGRAM main(VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS  GetCustomerList : "http://www.invenireaude.org/example")
RETURNS GetCustomerList : "http://www.invenireaude.org/example"
BEGIN

  data.customers=wrap::fetchCustomerOrderByAgeAndName();
  RETURN data;

END;