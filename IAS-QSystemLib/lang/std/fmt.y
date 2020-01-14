PROGRAM fmt::serialize(VAR format AS String, VAR data AS AnyType)
RETURNS String
EXTERNAL "libIASQSystemLib:ias_qs_lang_fmt_proxy:Serialize"();

PROGRAM fmt::parse(VAR format AS String, VAR payload AS String)
RETURNS AnyType
EXTERNAL "libIASQSystemLib:ias_qs_lang_fmt_proxy:Parse"();

PROGRAM fmt::serialize(
    VAR format AS String,
    VAR data AS AnyType,
    VAR attributes AS ARRAY OF Attribute: "http://www.invenireaude.org/qsystem/workers")
RETURNS String
EXTERNAL "libIASQSystemLib:ias_qs_lang_fmt_proxy:Serialize"();

PROGRAM fmt::parse(VAR format AS String,
                   VAR payload AS String,
                   VAR attributes AS ARRAY OF Attribute: "http://www.invenireaude.org/qsystem/workers")
RETURNS AnyType
EXTERNAL "libIASQSystemLib:ias_qs_lang_fmt_proxy:Parse"();
