#########################################################################
ARTIFACT=IASQSystemFmt-PCF
ARTIFACT_ALT_NAMES+=qsfmt_PCF.so
ARTIFACT_ALT_NAMES+=qsfmt_MQADMIN.so
ARTIFACT_ALT_NAMES+=qsfmt_MQEVENT.so
#########################################################################
DEP_PROJECTS+=IAS-CommonLib
DEP_PROJECTS+=IAS-DataModelLib
DEP_PROJECTS+=IAS-QSystemLib
#########################################################################
include Makefile.FILES
#########################################################################
include ../IAS-BuilderTools/Makefile
#########################################################################
-include $(CPPDEPS)
#########################################################################
-include Makefile.$(IAS_PLATFORM)
all : makedirs $(TARGET) links
#########################################################################
LD_LIBRARY_PATH:=../IAS-CommonLib/out/lib:$(LD_LIBRARY_PATH)
LD_LIBRARY_PATH:=../IAS-DataModelLib/out/lib:$(LD_LIBRARY_PATH)

#########################################################################
-include Makefile.depend
