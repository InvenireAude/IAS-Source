PROGRAM com::examples::basic::loop02(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.invenireaude.org/example",
            VAR output AS Customer : "http://www.invenireaude.org/example")  BEGIN

    VAR i AS Integer : "IAS/DM/Default";
    VAR i2 AS Integer : "IAS/DM/Default";

    output=COPYOF(input);

    FOR i = 1 TO 100 DO
      BEGIN

        VAR a AS Address : "http://www.invenireaude.org/example";

        a=NEW Address : "http://www.invenireaude.org/examplef";
        a.street="Nowa";
        a.block=i;
        output.address=a;
      END;
  END;
