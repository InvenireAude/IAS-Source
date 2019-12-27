
IMPORT std::default;
IMPORT wrap::fetch;
IMPORT wrap::insert;

PROGRAM main(VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS  GetCustomerList : "http://www.examples.org/akc")
RETURNS GetCustomerList : "http://www.examples.org/akc"
BEGIN

  VAR i AS Integer;

  FOR i = 0 TO 100 DO BEGIN
    VAR customer AS Customer : "http://www.examples.org/akc";

    WITH customer DO BEGIN
      customer.id = 1000 +  i;
      customer.lastname="Novacky" + (i/10);
      customer.age= i % 10;
      customer.money= ("1.99" AS Decimal) * i;
    END;
    wrap::insertCustomer(ctx,customer);

  END;

  data.customers = wrap::fetchCustomerGroupBy();
  RETURN data;

END;