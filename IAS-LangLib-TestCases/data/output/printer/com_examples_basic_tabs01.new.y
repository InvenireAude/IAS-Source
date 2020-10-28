PROGRAM com::examples::basic::tabs01(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.invenireaude.org/example",
            VAR output AS Customer : "http://www.invenireaude.org/example")  BEGIN

    VAR tab1 AS ARRAY OF Integer : "IAS/DM/Default";
    VAR tab2 AS ARRAY OF String : "IAS/DM/Default";
    VAR list AS ARRAY OF Address : "http://www.invenireaude.org/example";
    VAR a AS Address : "http://www.invenireaude.org/example";

    tab1=1;
    tab1=1;
    tab1=1;
    tab1=1;
    tab2=1;
    tab2=2;
    tab2=tab2[1];
    output=input;

    com::examples::utilitytab(tab1,output);

    output.address=com::examples::utilitytabresult(12,"Pierwsza tura.");
    list=com::examples::utilitytabresult(16,"Druga tura.");
    a=NEW Address : "http://www.invenireaude.org/examplef";
    output.address[3]=a;
    a.street="testowa";
    a.block=111;
    output.address[2].block=102;
    output.address=list[15];
    output.address[8]=list[14];
    output.address[9]=COPYOF(list[15]);
  END;
