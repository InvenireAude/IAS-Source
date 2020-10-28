
IMPORT std::default;
IMPORT wrap::fetch;
IMPORT wrap::update;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS Customer : "http://www.invenireaude.org/example")
RETURNS Customer : "http://www.invenireaude.org/example"
BEGIN

  wrap::fetchCustomerForUpdate(ctx,data);

  data.id=data.id;
  data.lastname="Novacek";
  data.age=71;

  wrap::updateCustomer(ctx,data);

  wrap::fetchCustomer(ctx,data);
  wrap::fetchAddresses(ctx,data);

  RETURN data;

END;