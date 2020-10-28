PROGRAM com::examples::basic::loop01(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.invenireaude.org/example",
            VAR output AS Customer : "http://www.invenireaude.org/example")  BEGIN

    VAR i AS Integer : "IAS/DM/Default";

    i=0;

    WHILE (i < 10) DO
      BEGIN

        VAR a AS Address : "http://www.invenireaude.org/example";

        IF ((i MOD 2) == 0) THEN
          BEGIN
            a=NEW Address : "http://www.invenireaude.org/example";
          END
        ELSE
          a=NEW Address : "http://www.invenireaude.org/examplef";
        a.street="Nowa";
        a.block=i;
        input.address=a;
        i=(i + 1);
      END;

    i=0;

    WHILE (i < SIZEOF(input.address)) DO
      BEGIN

        VAR tmp AS Address : "http://www.invenireaude.org/example";

        tmp=input.address[i];

        IF  NOT  ISNULL (tmp) THEN
          BEGIN
            IF tmp ISINSTANCE (Address: "http://www.invenireaude.org/example") THEN
              BEGIN
                tmp.street=((TYPE(tmp) + ":") + TYPENS(tmp));
              END;
            tmp.block=(STRLEN(tmp.street) + i);
          END;

        i=(i + 1);
      END;

    output=COPYOF(input);
  END;
