PROGRAM com::examples::basic::cast(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.invenireaude.org/example",
            VAR output AS Customer : "http://www.invenireaude.org/example")  BEGIN

    VAR anything AS AnyType : "IAS/DM/Default";
    VAR a AS Address : "http://www.invenireaude.org/example";

    output=NEW Customer : "http://www.invenireaude.org/example";
    output.birth=( ( "2013-09-08T12:46:39+0200" AS DateTime : "IAS/DM/Default" )  + (((10 * 365) * 24) * 3600));
    output.firstname=("100" + 100);
    output.lastname= ( (( ( "100" AS Integer : "IAS/DM/Default" )  + (((10 * 365) * 24) * 3600)) + 100) AS Date : "IAS/DM/Default" ) ;
    output.someDate= (  ( output.lastname AS Date : "IAS/DM/Default" )  AS Integer : "IAS/DM/Default" ) ;
    output.someTime= (  (  ( output.birth AS String : "IAS/DM/Default" )  AS DateTime : "IAS/DM/Default" )  AS Integer : "IAS/DM/Default" ) ;
    anything=NEW Address : "http://www.invenireaude.org/examplef";
    a=anything;
    a.street="Street";
    a.block=1;
    a.street=((((a.street + "#") + a.street) + "% ") + ( ( anything AS Address : "http://www.invenireaude.org/examplef" ) ).street);
    ( ( anything AS Address : "http://www.invenireaude.org/examplef" ) ).country="Far, far away";
    ( ( anything AS Address : "http://www.invenireaude.org/examplef" ) ).street=(a.street + "!");
    output.address=anything;
  END;
