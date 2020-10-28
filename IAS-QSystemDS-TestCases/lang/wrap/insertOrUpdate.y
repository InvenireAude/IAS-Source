IMPORT wrap::insert;
IMPORT wrap::update;

PROGRAM wrap::insertOrUpdateCustomer(VAR ctx  AS Context  : "http://www.invenireaude.org/qsystem/workers",
				             		 VAR data AS Customer : "http://www.invenireaude.org/example")
BEGIN

 TRY BEGIN
 	wrap::insertCustomer(ctx,data);
 END CATCH (VAR e AS ConstraintViolationException : "http://www.invenireaude.org/qsystem/workers/ds") BEGIN
 	wrap::updateCustomer(ctx,data);
 END;

END;