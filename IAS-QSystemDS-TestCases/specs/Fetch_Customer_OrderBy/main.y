
IMPORT std::default;
IMPORT wrap::fetch;

PROGRAM main(VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS  GetCustomerList : "http://www.examples.org/akc")
RETURNS GetCustomerList : "http://www.examples.org/akc"
BEGIN

  data.customers=wrap::fetchCustomerOrderByAgeAndName();
  RETURN data;

END;