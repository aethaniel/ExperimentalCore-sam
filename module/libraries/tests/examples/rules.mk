#
#  SAM Arduino IDE examples makefile.
#
#  Copyright (c) 2015 Thibaut VIARD. All right reserved.
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#  See the GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#

#|---------------------------------------------------------------------------------------|
#| Extract file names and path                                                           |
#|---------------------------------------------------------------------------------------|
PROJ_ASRCS   = $(filter %.s,$(foreach file,$(SOURCES),$(file)))
PROJ_CSRCS   = $(filter %.c,$(foreach file,$(SOURCES),$(file)))
PROJ_CPPSRCS = $(filter %.cpp,$(foreach file,$(SOURCES),$(file)))

#|---------------------------------------------------------------------------------------|
#| Set important path variables                                                          |
#|---------------------------------------------------------------------------------------|
VPATH    = $(foreach path,$(sort $(foreach file,$(SOURCES),$(dir $(file)))),$(path) :)
INC_PATH = $(patsubst %,-I%,$(sort $(foreach file,$(filter %.h,$(SOURCES)),$(dir $(file)))))
INC_PATH += $(INCLUDES)
LIB_PATH = -L$(dir $(RESOURCES_LINKER)) -L$(dir $(VARIANT_LIB_PATH))

#|---------------------------------------------------------------------------------------|
#| Options for compiler binaries                                                         |
#|---------------------------------------------------------------------------------------|
COMMON_FLAGS = -Wall -Wchar-subscripts -Wcomment
COMMON_FLAGS += -Werror-implicit-function-declaration -Wmain -Wparentheses
COMMON_FLAGS += -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused
COMMON_FLAGS += -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef
COMMON_FLAGS += -Wshadow -Wpointer-arith -Wwrite-strings
COMMON_FLAGS += -Wsign-compare -Waggregate-return -Wmissing-declarations
COMMON_FLAGS += -Wmissing-format-attribute -Wno-deprecated-declarations
COMMON_FLAGS += -Wpacked -Wredundant-decls -Wlong-long
COMMON_FLAGS += -Wunreachable-code -Wcast-align
# -Wmissing-noreturn -Wconversion
COMMON_FLAGS += --param max-inline-insns-single=500 -mcpu=$(DEVICE_CORE) -mthumb -ffunction-sections -fdata-sections
COMMON_FLAGS += -D$(DEVICE_PART) -DDONT_USE_CMSIS_INIT -fdiagnostics-color=always
COMMON_FLAGS += -Wa,-adhlns="$(subst .o,.lst,$@)"
COMMON_FLAGS += $(INC_PATH) -DF_CPU=$(DEVICE_FREQUENCY)
COMMON_FLAGS += -nostdlib --param max-inline-insns-single=500

ifeq ($(DEBUG),0)
COMMON_FLAGS += -Os
else
COMMON_FLAGS += -ggdb3 -O0
COMMON_FLAGS += -Wformat=2
endif

CFLAGS = $(COMMON_FLAGS) -std=gnu11 -Wimplicit-int -Wbad-function-cast -Wmissing-prototypes -Wnested-externs

ifeq ($(DEBUG),1)
CFLAGS += -Wstrict-prototypes
endif

CPPFLAGS = $(COMMON_FLAGS) -std=gnu++11 -fno-rtti -fno-exceptions
#-fno-optional-diags -fno-threadsafe-statics

LDFLAGS = -mcpu=$(DEVICE_CORE) -mthumb $(LIB_PATH)
LDFLAGS += -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align
#LDFLAGS += -nostartfiles
#-std=c++11 --param max-inline-insns-single=100 -fno-rtti -fno-exceptions -fno-threadsafe-statics

#|---------------------------------------------------------------------------------------|
#| Define targets                                                                        |
#|---------------------------------------------------------------------------------------|
AOBJS = $(patsubst %.s,%.o,$(addprefix $(OBJ_PATH)/, $(notdir $(PROJ_ASRCS))))
COBJS = $(patsubst %.c,%.o,$(addprefix $(OBJ_PATH)/, $(notdir $(PROJ_CSRCS))))
CPPOBJS = $(patsubst %.cpp,%.o,$(addprefix $(OBJ_PATH)/, $(notdir $(PROJ_CPPSRCS))))

# Declare as phony all rules not based on files
# $(VARIANT_LIB_PATH) is here also to force checking its dependencies and eventually rebuild
.PHONY: all print_info clean packaging upload_openocd upload_edbg openocd debug $(VARIANT_LIB_PATH)

all: $(OUTPUT_FILE_PATH).bin

print_info:
	@echo VPATH ---------------------------------------------------------------------------------
	@echo $(VPATH)
	@echo SOURCES -------------------------------------------------------------------------------
	@echo $(SOURCES)
#	@echo PROJ_ASRCS ----------------------------------------------------------------------------
#	@echo $(PROJ_ASRCS)
#	@echo AOBJS ---------------------------------------------------------------------------------
#	@echo $(AOBJS)
	@echo PROJ_CSRCS ----------------------------------------------------------------------------
	@echo $(PROJ_CSRCS)
	@echo COBJS ---------------------------------------------------------------------------------
	@echo $(COBJS)
	@echo PROJ_CPPSRCS --------------------------------------------------------------------------
	@echo $(PROJ_CPPSRCS)
	@echo CPPOBJS -------------------------------------------------------------------------------
	@echo $(CPPOBJS)
	@echo CURDIR --------------------------------------------------------------------------------
	@echo $(CURDIR)
	@echo OBJ_PATH ---------------------------------------------------------------------------
	@echo $(OBJ_PATH)
	@echo ---------------------------------------------------------------------------------------

$(OUTPUT_FILE_PATH).bin: $(OUTPUT_FILE_PATH).elf
	$(OBJCOPY) -O binary $(OUTPUT_FILE_PATH).elf $(OUTPUT_FILE_PATH).bin

$(OUTPUT_FILE_PATH).elf: $(OBJ_PATH) $(VARIANT_LIB_PATH) $(PROJECT_PATH)/Makefile $(RESOURCES_LINKER) $(AOBJS) $(COBJS) $(CPPOBJS)
	$(CC) $(LDFLAGS) "-T$(notdir $(RESOURCES_LINKER))" "-Wl,-Map,$(OUTPUT_FILE_PATH).map" --specs=nano.specs --specs=nosys.specs -o "$(OUTPUT_FILE_PATH).elf" -Wl,--start-group $(AOBJS) $(COBJS) $(CPPOBJS) -lm -lgcc -l$(VARIANT_NAME) -Wl,--end-group
	$(NM) $(OUTPUT_FILE_PATH).elf >$(OUTPUT_FILE_PATH)_symbols.txt
	$(SIZE) --format=sysv -t -x $(OUTPUT_FILE_PATH).elf

$(VARIANT_LIB_PATH):
	@echo +++ Checking if library needs to be built [$(notdir $@)]
	make --no-builtin-rules -C $(dir $(VARIANT_LIB_PATH)) DEBUG=$(DEBUG)

#|---------------------------------------------------------------------------------------|
#| Compile or assemble                                                                  |
#|---------------------------------------------------------------------------------------|
$(AOBJS): $(OBJ_PATH)/%.o: %.s $(OBJ_PATH)
	@echo +++ Assembling [$(notdir $<)]
	$(AS) $(AFLAGS) $< -o $@

$(COBJS): $(OBJ_PATH)/%.o: %.c $(OBJ_PATH)
	@echo +++ Compiling [$(notdir $<)]
	$(CC) $(CFLAGS) -c $< -o $@

$(CPPOBJS): $(OBJ_PATH)/%.o: %.cpp $(OBJ_PATH)
	@echo +++ Compiling [$(notdir $<)]
	$(CC) $(CPPFLAGS) -c $< -o $@

#|---------------------------------------------------------------------------------------|
#| Output folder                                                                         |
#|---------------------------------------------------------------------------------------|
$(OBJ_PATH):
	@echo +++ Creation of [$@]
	@-mkdir $(OBJ_PATH)

#|---------------------------------------------------------------------------------------|
#| Dependencies                                                                          |
#|---------------------------------------------------------------------------------------|
$(OBJ_PATH)/%.d : %.s $(OBJ_PATH)
	@echo +++ Dependencies of [$(notdir $<)]
	@$(CC) $(AFLAGS) -MM -c $< -MT $(basename $@).o -o $@

$(OBJ_PATH)/%.d : %.S $(OBJ_PATH)
	@echo +++ Dependencies of [$(notdir $<)]
	@$(CC) $(AFLAGS) -MM -c $< -MT $(basename $@).o -o $@

$(OBJ_PATH)/%.d : %.c $(OBJ_PATH)
	@echo +++ Dependencies of [$(notdir $<)]
	@$(CC) $(CFLAGS) -MM -c $< -MT $(basename $@).o -o $@

$(OBJ_PATH)/%.d : %.cpp $(OBJ_PATH)
	@echo +++ Dependencies of [$(notdir $<)]
	@$(CC) $(CPPFLAGS) -MM -c $< -MT $(basename $@).o -o $@

#|---------------------------------------------------------------------------------------|
#| Cleanup                                                                               |
#|---------------------------------------------------------------------------------------|
clean:
	-rm -f $(OBJ_PATH)/* $(OBJ_PATH)/*.*
	-rmdir $(OBJ_PATH)
	-rm -f $(OUTPUT_FILE_PATH).elf
	-rm -f $(OUTPUT_FILE_PATH).bin
	-rm -f $(OUTPUT_FILE_PATH).map
	-rm -f $(OUTPUT_FILE_PATH)_symbols.txt

$(OBJ_PATH)/%.o : %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

#|---------------------------------------------------------------------------------------|
#| Upload example binary using openocd software tool                                     |
#|---------------------------------------------------------------------------------------|
upload_openocd: $(OUTPUT_FILE_PATH).elf
	$(TOOL_OPENOCD) -f "$(RESOURCES_OPENOCD_UPLOAD)" -c "program $(OUTPUT_FILE_PATH).elf verify reset"

#|---------------------------------------------------------------------------------------|
#| Upload example binary using JLink Commander software tool                            |
#|---------------------------------------------------------------------------------------|
upload_jlink: $(OUTPUT_FILE_PATH).elf
	$(TOOL_JLINK) -CommandFile "$(RESOURCES_JLINK_UPLOAD)"

#|---------------------------------------------------------------------------------------|
#| Upload example binary using edbg software tool                                        |
#|---------------------------------------------------------------------------------------|
upload_edbg: $(OUTPUT_FILE_PATH).bin
	$(TOOL_EDBG) -l
	$(TOOL_EDBG) -t list
ifeq ($(DEVICE_CORE),cortex-m3)
	$(TOOL_EDBG) -bepv --target=atmel_cm3 --file $(OUTPUT_FILE_PATH).bin
else ifeq ($(DEVICE_CORE),cortex-m4)
	$(TOOL_EDBG) -bepv --target=atmel_cm4 --file $(OUTPUT_FILE_PATH).bin
else ifeq ($(DEVICE_CORE),cortex-m7)
	$(TOOL_EDBG) -bepv --target=atmel_cm7 --file $(OUTPUT_FILE_PATH).bin
endif

#|---------------------------------------------------------------------------------------|
#| Start openocd GDB server (in a separate shell) in order to prepare a debug session    |
#| Must be called before 'debug' rule                                                    |
#|---------------------------------------------------------------------------------------|
openocd: $(OUTPUT_FILE_PATH).elf
	$(TOOL_OPENOCD) -f "$(RESOURCES_OPENOCD_START)" -c "init" -c "halt"

#|---------------------------------------------------------------------------------------|
#| Debug session start                                                                   |
#| Must be called after 'openocd' rule                                                   |
#|---------------------------------------------------------------------------------------|
debug: $(OUTPUT_FILE_PATH).elf
	$(GDB) -x "$(RESOURCES_GDB)" -readnow -se $(OUTPUT_FILE_PATH).elf

#|---------------------------------------------------------------------------------------|
#| Module packaging for Arduino IDE Board Manager                                        |
#| This rule is added in case of                                                         |
#|---------------------------------------------------------------------------------------|
packaging:

#|---------------------------------------------------------------------------------------|
#| Include dependencies, if existing                                                     |
#| Little trick to avoid dependencies build for some rules when useless                  |
#| CAUTION: this won't work as expected with 'make clean all'                            |
#|---------------------------------------------------------------------------------------|
DEP_EXCLUDE_RULES := clean print_info
ifeq (,$(findstring $(MAKECMDGOALS), $(DEP_EXCLUDE_RULES)))
-include $(AOBJS:%.o=%.d)
-include $(COBJS:%.o=%.d)
-include $(CPPOBJS:%.o=%.d)
endif

