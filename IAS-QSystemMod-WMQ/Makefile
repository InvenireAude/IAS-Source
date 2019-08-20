#########################################################################
ARTIFACT=IASQSystemMod-WMQ
ARTIFACT_ALT_NAMES+=txmmod_mqm.so
ARTIFACT_ALT_NAMES+=qsmod_mqm.so
ARTIFACT_ALT_NAMES+=qsmod_mqic.so
#########################################################################
DEP_PROJECTS+=IAS-CommonLib
DEP_PROJECTS+=IAS-DataModelLib
DEP_PROJECTS+=IAS-LangLib
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

sdo : xsd/qsystem.xsd
	rm -rf src/yyy
	rm -rf src/Impl
	echo ${LD_LIBRARY_PATH}
	../IAS-DataModelLib-CodeGen/out/bin/ias_sdo_codegen -s -x xsd/qsystem.xsd:xsd/qsystem.workers.xsd -d src
	rmdir src/src/Impl
	rmdir src/src

#########################################################################
-include Makefile.depend
