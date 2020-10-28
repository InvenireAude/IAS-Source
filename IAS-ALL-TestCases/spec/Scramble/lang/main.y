IMPORT std::default;
IMPORT std::qs;

PROGRAM scramblePassword(
  VAR id AS String,
	VAR password AS String
) RETURNS String
BEGIN

	result = std::toBase64(
		std::fromHex(std::sha256("KxVpvuMBE^#~1&>x)R/&QQa%VeROK%0hck*4"+std::fromHex(std::sha256(password))
	)));

  VAR ctx  AS Context  : "http://www.invenireaude.org/qsystem/workers";
  ctx.MID = id + ".txt";
  ctx.FMT = "String";

  std::send("output",ctx,result);
END;


PROGRAM main(
	VAR ctx   AS Context  : "http://www.invenireaude.org/qsystem/workers",
	VAR data  AS AnyType
)
BEGIN
  scramblePassword("P01","password");
  scramblePassword("P02","Ździbło!@#");
END;

