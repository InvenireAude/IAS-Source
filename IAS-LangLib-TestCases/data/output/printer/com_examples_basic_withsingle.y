PROGRAM com::examples::basic::withsingle(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.invenireaude.org/example",
            VAR output AS Customer : "http://www.invenireaude.org/example")  BEGIN

    VAR i AS Integer : "IAS/DM/Default";
    VAR i2 AS Integer : "IAS/DM/Default";

    output=COPYOF(input);
    output.address=NEW Address : "http://www.invenireaude.org/examplef";
    output.address=NEW Address : "http://www.invenireaude.org/example";

    FOR i = 1 TO 2 DO
      BEGIN

        VAR a AS Address : "http://www.invenireaude.org/example";

        a=NEW Address : "http://www.invenireaude.org/examplef";
        a.street="Nowa";
        a.block=i;
        output.address=a;
      END;

    output.address[2]=NEW Address : "http://www.invenireaude.org/example";
    output.address=NEW Address : "http://www.invenireaude.org/examplef";

    WITH output.address[1] DO
      street="Jednynka";

    WITH output.address DO
      BEGIN
        IF  NOT  ISSET (block) THEN
          block=0
        ELSE
          block=((1000 + (2 * i)) + block);

        IF  NOT  ISSET (street) THEN
          street="nowka";

        i=(i + 1);
      END;

    WITH output.address DO
      IF (block > 1000) THEN
        street="Duze numery";

    WITH aa AS output.address DO
      IF (TYPENS(aa) <> "http://www.invenireaude.org/example") THEN
        aa.street=(aa.street + "Lepszy typ");

    WITH aa AS output.address[2] DO
      aa.street="Gorszy";
  END;
