IMPORT std::default;
IMPORT std::qs;

PROGRAM tc::save(
  VAR ctx  AS Context  : "http://www.invenireaude.org/qsystem/workers",
  VAR file AS String,
  VAR data AS AnyType
)
BEGIN
  ctx.MID = file;
  std::send("output",ctx,data);
END;


PROGRAM tc::save(
  VAR format  AS String,
  VAR file AS String,
  VAR data AS AnyType
)
BEGIN
  VAR ctx AS Context  : "http://www.invenireaude.org/qsystem/workers";
  ctx.FMT = format;
  ctx.MID = file;
  std::send("output",ctx,data);
END;