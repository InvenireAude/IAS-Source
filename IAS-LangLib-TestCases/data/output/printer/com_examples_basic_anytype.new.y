PROGRAM com::examples::basic::anytype(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.invenireaude.org/example",
            VAR output AS Customer : "http://www.invenireaude.org/example")  BEGIN

    VAR a AS Address : "http://www.invenireaude.org/examplef";
    VAR i AS Integer : "IAS/DM/Default";
    VAR aa AS AnyType : "IAS/DM/Default";

    i=100;
    a.block=100;
    a.street="jakas ulica";
    output=COPYOF(input);
    output.misc=COPYOF(input);
    aa=a;
    output.address=aa;
    output.address=COPYOF(aa);
    aa=(i + i);
    aa=(i + aa);
    output.address[1].block=aa;

    com::examples::utilityany(13,output.address[3]);
  END;
