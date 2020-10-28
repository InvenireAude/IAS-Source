PROGRAM com::examples::basic::fileops(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.invenireaude.org/example",
            VAR output AS Customer : "http://www.invenireaude.org/example")  BEGIN

    VAR a AS Address : "http://www.invenireaude.org/example";
    VAR c AS Customer : "http://www.invenireaude.org/example";
    VAR o AS AnyType : "IAS/DM/Default";

    std::save("/tmp/sdo.out",input);
    c=std::load("/tmp/sdo.out");
    output=COPYOF(input);
    output.misc=c;
  END;
