IMPORT std::default;
IMPORT std::qs;
IMPORT std::fmt;
IMPORT std::storage;

PROGRAM sendmultipart(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
RETURNS Customer : "http://www.invenireaude.org/example"
BEGIN

  CREATE result BEGIN
    firstname = "John";
    lastname  = "Doe";
  END;

  // turn mulitform on, save the format of the main part (eg. xml, json)
  IF ISSET(ctx.FMT) THEN
    std::setAttribute(ctx,".IAS_MULTIFORM_FMT",ctx.FMT);
  ctx.FMT = "MultiPart";
  std::setAttribute(ctx,".IAS_MPF_DATA_NAME","my_data"); // name for the main part - optional, default name="data"

  // add attachment 1
  std::setLocalValue("first", ("AEEAQg==" AS Raw));
  std::setAttribute(ctx,".IAS_MPF_ATTACHMENT_NAME_1","first");
  std::setAttribute(ctx,".IAS_MPF_ATTACHMENT_FILE_1","first.txt");
  // add attachment 2 - name can be a file name as well
  std::setLocalValue("second.txt", ("AEEAQg==" AS Raw));
  std::setAttribute(ctx,".IAS_MPF_ATTACHMENT_NAME_2","second.txt");


  // add attachment 3
  std::setLocalValue("ctx", COPYOF(ctx));
  std::setAttribute(ctx,".IAS_MPF_ATTACHMENT_NAME_3","ctx");

  // add attachment 4
  std::setLocalValue("text", "Ala ma kota ");
  std::setAttribute(ctx,".IAS_MPF_ATTACHMENT_NAME_4","text");
  std::setAttribute(ctx,".IAS_MPF_ATTACHMENT_FILE_4","text.txt");

END;



PROGRAM readmultipart(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
BEGIN

  std::print("Main part is: " + TYPENS(data) + "#" + TYPE(data));

  VAR i AS Integer;
  VAR found AS Integer;

  i = 1;
  found = TRUE;


  WHILE found == TRUE DO BEGIN

   VAR attrName AS String;
   VAR attrFile AS String;

   attrName = ".IAS_MPF_ATTACHMENT_NAME_" + i;
   attrFile = ".IAS_MPF_ATTACHMENT_FILE_" + i;

   found = FALSE;

   WITH a AS ctx.attributes DO
     IF a.name == attrName THEN BEGIN

        VAR value AS AnyType;
        value = std::getLocalValue(a.value);

        std::print("Attachment [" + i + "] :: [" + a.value + "] " + TYPENS(value) + "#" + TYPE(value));

        WITH af AS ctx.attributes DO // why just not use 'filename' as 'name' ?
          IF af.name == attrFile THEN
            std::print("  File: [" + af.value + "]");

        IF value ISINSTANCE (String) THEN
          std::print("  Data: [" + value + "]");

        found = TRUE;
      END;

   i = i + 1;
  END;

  std::save("stdout",ctx);

END;

PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
RETURNS AnyType
BEGIN

  // save it as test case result
  ctx.MID="Message.multipart.txt";

  result = sendmultipart(ctx,data);
  readmultipart(ctx, result);


END;

