
IMPORT std::default;
IMPORT wrap::fetch;
IMPORT wrap::insert;

PROGRAM main(VAR ctx    AS Context  : "http://www.invenireaude.org/qsystem/workers",
		   	 VAR data  AS Customer : "http://www.invenireaude.org/example")
RETURNS Customer : "http://www.invenireaude.org/example"
BEGIN


  VAR customer AS Customer : "http://www.invenireaude.org/example";

  customer.id=data.id;
  customer.lastname="Novacek";
  customer.photo=std::copyStringToRaw("ABCDEF");
  customer.age=71;
  customer.money="123.45";
  customer.birthDate = "1999-01-02";
  customer.wakeup    = "05:30:55";
  customer.updated   = "2015-06-07T05:30:55";

  VAR address AS Address : "http://www.invenireaude.org/example";
  address.street="Fresh fruits";
  address.block=12;
  customer.address=address;

  address = NEW Address : "http://www.invenireaude.org/examplef";
  address.street="Old potatoes";
  address.block=21;
  customer.address=address;

  std::save("/tmp/customer.xml",customer);
  std::save("/tmp/type.xml",TYPE(customer.photo));

  wrap::insertCustomer(ctx,customer);

  WITH a AS customer.address DO
  	wrap::insertAddress(ctx,customer.id,a,getCode(a));

  wrap::fetchCustomer(ctx,data);
  wrap::fetchAddresses(ctx,data);

  RETURN data;

END;