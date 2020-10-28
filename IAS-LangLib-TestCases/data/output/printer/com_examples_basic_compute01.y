PROGRAM com::examples::basic::compute01(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.invenireaude.org/example",
            VAR output AS Customer : "http://www.invenireaude.org/example")  BEGIN

    VAR i AS Integer : "IAS/DM/Default";
    VAR b1 AS Boolean : "IAS/DM/Default";
    VAR b2 AS Boolean : "IAS/DM/Default";

    output=COPYOF(input);
    i=0;

    WHILE (i < 10) DO
      BEGIN

        VAR aaaa AS Address : "http://www.invenireaude.org/example";

        aaaa=NEW Address : "http://www.invenireaude.org/examplef";
        aaaa.street=std::replace(("_Stara_" + i),"Stara","Nowa");
        aaaa.block=((((10 * i) + SIZEOF(output.address)) + ((10 * 5) / 2)) - 100);
        output.address=aaaa;
        i=(i + 1);
      END;

    output.firstname=NULL;
    b1=TRUE;
    b2=FALSE;
    output.lastname=((((output.lastname + " ") + b1) + " ") + b2);
  END;
