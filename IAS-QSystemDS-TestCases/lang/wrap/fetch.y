PROGRAM wrap::fetchCustomer(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				             VAR data    AS Customer : "http://www.invenireaude.org/example")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ONCE
   firstname  => data.firstname,
   middlename => data.middlename,
   lastname   => data.lastname,
?  birthDate  => data.birthDate,
?  wakeup     => data.wakeup,
?  updated    => data.updated,
   age   	  => data.age,
?  money  => data.money,
?  rawdata => data.photo
 FROM 'CUSTOMER_VW'
 WHERE
   id = data.id
");

PROGRAM wrap::fetchCustomerForUpdate(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				             VAR data    AS Customer : "http://www.invenireaude.org/example")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ONCE
   firstname  => data.firstname,
   middlename => data.middlename,
   lastname   => data.lastname,
 ? birthDate  => data.birthDate,
 ? wakeup     => data.wakeup,
 ? updated    => data.updated,
   age        => data.age,
 ? money      => data.money,
 ? rawdata    => data.photo
 FROM 'CUSTOMER_VW'
 WHERE
   id = data.id
 FOR UPDATE
");

// ? rawdata    => data.misc

PROGRAM wrap::fetchCustomerList(VAR ctx        AS Context  : "http://www.invenireaude.org/qsystem/workers")
RETURNS ARRAY OF Customer : "http://www.invenireaude.org/example"
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ARRAY INTO result
   id         => id,
   firstname  => firstname,
   middlename => middlename,
   lastname   => lastname,
?  birthDate  => birthDate,
?  wakeup     => wakeup,
?  updated    => updated,
   age        => age,
?  money  =>  money
 FROM 'CUSTOMER_VW'
");

PROGRAM wrap::fetchCustomerList(VAR ctx        AS Context  : "http://www.invenireaude.org/qsystem/workers",
                                VAR offset     AS Integer,
                                VAR page       AS Integer)
RETURNS ARRAY OF Customer : "http://www.invenireaude.org/example"
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ARRAY INTO result PAGE(offset,page)
   id         => id,
   firstname  => firstname,
   middlename => middlename,
   lastname   => lastname,
?  birthDate  => birthDate,
?  wakeup     => wakeup,
?  updated    => updated,
   age        => age,
?  money  =>  money
 FROM 'CUSTOMER_VW'
");

PROGRAM wrap::fetchCustomerOrderByAgeAndName()
RETURNS ARRAY OF Customer : "http://www.invenireaude.org/example"
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ARRAY INTO result
   id         => id,
   firstname  => firstname,
   middlename => middlename,
   lastname   => lastname,
?  birthDate  => birthDate,
?  wakeup     => wakeup,
?  updated    => updated,
   age        => age,
?  money  =>  money
 FROM 'CUSTOMER_VW'
ORDER BY age,lastname, firstname DESC
");

PROGRAM wrap::fetchCustomerOrderByMap(
  VAR order AS String
)
RETURNS ARRAY OF Customer : "http://www.invenireaude.org/example"
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ARRAY INTO result
   id         => id,
   firstname  => firstname,
   middlename => middlename,
   lastname   => lastname,
?  birthDate  => birthDate,
?  wakeup     => wakeup,
?  updated    => updated,
   age        => age,
?  money  =>  money
 FROM 'CUSTOMER_VW'
ORDER BY MAP order (
     id => (id DESC),
    'age' => (age DESC),
    'name+' => (lastname ASC,firstname),
    'name-' => (lastname DESC, firstname DESC),
     _ => ()
   )
");


PROGRAM wrap::fetchCustomerGroupBy()
RETURNS ARRAY OF Customer : "http://www.invenireaude.org/example"
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ARRAY INTO result
   count(id)   => id,
   avg(age)    => age,
   sum(money)  =>  money,
   lastname    => lastname
 FROM 'CUSTOMER_VW'
GROUP BY lastname
ORDER BY lastname
");

PROGRAM wrap::fetchAddresses(VAR ctx      AS Context  : "http://www.invenireaude.org/qsystem/workers",
				              VAR data    AS Customer : "http://www.invenireaude.org/example")
EXTERNAL "libIASQSystemLib:ias_qs_lang_db_proxy:WrappedStatement"
(
"db",
"SELECT ARRAY INTO data.address
	MAP type (
		F     => Address : 'http://www.invenireaude.org/examplef'(
           ? country => country
		),
	    _     => Address : 'http://www.invenireaude.org/example'
   )
   street => street,
   block  => block
 FROM 'ADDRESS_VW'
 WHERE 'CUSTOMER_ID' = data.id
");
