#-------------------------------------------------------------------------------
#		Tools
#-------------------------------------------------------------------------------

# Set DEBUG variable for once if not coming from command line
ifndef DEBUG
DEBUG=0
endif

# Tool suffix when cross-compiling
CROSS_COMPILE = arm-none-eabi-

# Compilation tools
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
SIZE = $(CROSS_COMPILE)size
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
GDB = $(CROSS_COMPILE)gdb
NM = $(CROSS_COMPILE)nm

# change this value if openocd isn't in the user/system PATH
OPENOCD = openocd

#DEVICE = __SAM4S16C__
DEVICE = __SAM4SD32C__
CORE = cortex-m4
VARIANT_NAME = atmel_sam4s_xplained_pro
CORE_FREQUENCY = 4000000ul
PROJECT_NAME=blink

ROOT_PATH=../../..
VARIANT_PATH = $(ROOT_PATH)/variants/$(VARIANT_NAME)
RESOURCES_OPENOCD_UPLOAD = $(VARIANT_PATH)/openocd_scripts/variant_upload.cfg
RESOURCES_OPENOCD_START = $(VARIANT_PATH)/openocd_scripts/variant_debug_start.cfg
RESOURCES_GDB = $(VARIANT_PATH)/debug_scripts/variant.gdb
RESOURCES_LINKER = $(VARIANT_PATH)/linker_scripts/gcc/variant_without_bootloader.ld
CORE_ARM_PATH=$(ROOT_PATH)/cores/arduino/arch_arm
CORE_COMMON_PATH=$(ROOT_PATH)/cores/arduino/arch_common
CORE_AVR_PATH=$(ROOT_PATH)/cores/arduino/avr_compat
CORE_SAM_PATH=$(ROOT_PATH)/cores/arduino/port_sam
PROJECT_PATH=$(ROOT_PATH)/cores/validation/$(PROJECT_NAME)

INCLUDES  = -I$(ROOT_PATH)/../ArduinoModule-CMSIS/CMSIS/CMSIS/Include
INCLUDES += -I$(ROOT_PATH)/../ArduinoModule-CMSIS-Atmel/CMSIS/Device/ATMEL
INCLUDES += -I$(ROOT_PATH)/cores/arduino

OUTPUT_PATH = $(PROJECT_PATH)/obj
OUTPUT_NAME = $(PROJECT_NAME)
OUTPUT_FILE = $(PROJECT_NAME).elf
OUTPUT_FILE_PATH = $(PROJECT_PATH)/$(OUTPUT_FILE)
VARIANT_LIB_PATH = $(VARIANT_PATH)/lib$(VARIANT_NAME).a

#|---------------------------------------------------------------------------------------|
#| Source files                                                                          |
#|---------------------------------------------------------------------------------------|
SOURCES=\
$(CORE_ARM_PATH)/core.h                 \
$(CORE_ARM_PATH)/CoreHardwareSerial.h   \
$(CORE_ARM_PATH)/CoreMath.h             \
$(CORE_ARM_PATH)/CorePrint.h            \
$(CORE_ARM_PATH)/CorePrintable.h        \
$(CORE_ARM_PATH)/CoreRingBuffer.h       \
$(CORE_ARM_PATH)/CoreStream.h           \
$(CORE_ARM_PATH)/CoreString.h           \
$(CORE_ARM_PATH)/core_character.h       \
$(CORE_ARM_PATH)/core_itoa.h            \
$(CORE_ARM_PATH)/core_private.h         \
$(CORE_ARM_PATH)/core_reset.h           \
$(CORE_ARM_PATH)/core_shift.h           \
$(CORE_COMMON_PATH)/core_binary.h       \
$(CORE_COMMON_PATH)/core_constants.h    \
$(CORE_COMMON_PATH)/core_new.h          \
$(CORE_AVR_PATH)/core_dtostrf.h         \
$(CORE_AVR_PATH)/core_interrupt.h       \
$(CORE_AVR_PATH)/core_pgmspace.h        \
$(CORE_SAM_PATH)/Arduino.h              \
$(CORE_SAM_PATH)/CoreUART.h             \
$(CORE_SAM_PATH)/CoreUSART.h            \
$(CORE_SAM_PATH)/core_analog.h          \
$(CORE_SAM_PATH)/core_delay.h           \
$(CORE_SAM_PATH)/core_digital.h         \
$(CORE_SAM_PATH)/core_interrupts.h      \
$(CORE_SAM_PATH)/core_pulse.h           \
$(CORE_SAM_PATH)/core_reset.h           \
$(CORE_SAM_PATH)/CoreTone.h             \
$(CORE_SAM_PATH)/core_variant.h         \
$(VARIANT_PATH)/pins_arduino.h          \
$(VARIANT_PATH)/variant.h               \
$(PROJECT_PATH)/$(PROJECT_NAME).cpp

#|---------------------------------------------------------------------------------------|
#| Extract file names and path                                                           |
#|---------------------------------------------------------------------------------------|
PROJ_ASRCS  = $(filter %.s,$(foreach file,$(SOURCES),$(notdir $(file))))
PROJ_CSRCS  = $(filter %.c,$(foreach file,$(SOURCES),$(notdir $(file))))
PROJ_CPPSRCS  = $(filter %.cpp,$(foreach file,$(SOURCES),$(notdir $(file))))
PROJ_CHDRS  = $(filter %.h,$(foreach file,$(SOURCES),$(notdir $(file))))

#|---------------------------------------------------------------------------------------|
#| Set important path variables                                                          |
#|---------------------------------------------------------------------------------------|
VPATH    = $(foreach path,$(sort $(foreach file,$(SOURCES),$(dir $(file)))) $(subst \,/,$(OUTPUT_PATH)),$(path) :)
INC_PATH = $(patsubst %,-I%,$(sort $(foreach file,$(filter %.h,$(SOURCES)),$(dir $(file)))))
INC_PATH += $(INCLUDES)
LIB_PATH  = -L$(dir $(RESOURCES_LINKER)) -L$(dir $(VARIANT_LIB_PATH))

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
COMMON_FLAGS += --param max-inline-insns-single=500 -mcpu=$(CORE) -mthumb -ffunction-sections -fdata-sections
COMMON_FLAGS += -D$(DEVICE) -DDONT_USE_CMSIS_INIT -fdiagnostics-color=always
COMMON_FLAGS += -Wa,-adhlns="$(OUTPUT_PATH)/$(subst .o,.lst,$@)"
COMMON_FLAGS += $(INC_PATH) -DF_CPU=$(CORE_FREQUENCY)
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

LDFLAGS = -mcpu=$(CORE) -mthumb $(LIB_PATH)
LDFLAGS += -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align
LDFLAGS += -nostartfiles
#-std=c++11 --param max-inline-insns-single=100 -fno-rtti -nostdlib -fno-exceptions -fno-threadsafe-statics -nostdlib

#|---------------------------------------------------------------------------------------|
#| Define targets                                                                        |
#|---------------------------------------------------------------------------------------|
AOBJS = $(patsubst %.s,%.o,$(PROJ_ASRCS))
COBJS = $(patsubst %.c,%.o,$(PROJ_CSRCS))
CPPOBJS = $(patsubst %.cpp,%.o,$(PROJ_CPPSRCS))

all: $(OUTPUT_FILE_PATH)

test:
	@echo ---------------------------------------------------------------------------------------
	@echo DEBUG=$(DEBUG)
	@echo $(COMMON_FLAGS)
	@echo ---------------------------------------------------------------------------------------
	@echo binary $(OUTPUT_FILE_PATH)
	@echo VPATH ---------------------------------------------------------------------------------------
	@echo $(VPATH)
	@echo SOURCES ---------------------------------------------------------------------------------------
	@echo $(SOURCES)
	@echo PROJ_CHDRS ---------------------------------------------------------------------------------------
	@echo $(PROJ_CHDRS)
	@echo AOBJS ---------------------------------------------------------------------------------------
	@echo $(AOBJS)
	@echo PROJ_CSRCS ---------------------------------------------------------------------------------------
	@echo $(PROJ_CSRCS)
	@echo COBJS ---------------------------------------------------------------------------------------
	@echo $(COBJS)
	@echo PROJ_CPPSRCS ---------------------------------------------------------------------------------------
	@echo $(PROJ_CPPSRCS)
	@echo CPPOBJS ---------------------------------------------------------------------------------------
	@echo $(CPPOBJS)
	@echo ---------------------------------------------------------------------------------------
	@echo $(PWD)

$(OUTPUT_FILE_PATH): $(PROJECT_PATH)/Makefile $(RESOURCES_LINKER) $(AOBJS) $(COBJS) $(CPPOBJS) $(VARIANT_LIB_PATH)
	$(CC) $(LDFLAGS) "-T$(notdir $(RESOURCES_LINKER))" "-Wl,-Map,$(patsubst %.elf,%.map,$(OUTPUT_FILE_PATH))" --specs=nano.specs --specs=nosys.specs -o "$(OUTPUT_FILE_PATH)" -Wl,--start-group $(addprefix $(OUTPUT_PATH)/,$(AOBJS)) $(addprefix $(OUTPUT_PATH)/,$(COBJS)) $(addprefix $(OUTPUT_PATH)/,$(CPPOBJS)) -lm -lgcc -l$(VARIANT_NAME) -Wl,--end-group
	$(NM) $(OUTPUT_FILE_PATH) >$(patsubst %.elf,%_symbols.txt,$(OUTPUT_FILE_PATH)).txt
	$(OBJCOPY) -O binary $(OUTPUT_FILE_PATH) $(patsubst %.elf,%.bin,$(OUTPUT_FILE_PATH))
	$(SIZE) -A $(OUTPUT_FILE_PATH)

$(VARIANT_LIB_PATH):
#	make --no-builtin-rules --print-directory -C $(dir $(VARIANT_LIB_PATH))
	make DEBUG=$(DEBUG) -C $(dir $(VARIANT_LIB_PATH))

#|---------------------------------------------------------------------------------------|
#| Compile and assemble                                                                  |
#|---------------------------------------------------------------------------------------|
$(AOBJS): %.o: %.s $(PROJ_CHDRS)
	@echo +++ Assembling [$(notdir $<)]
	@$(AS) $(AFLAGS) $< -o $(OUTPUT_PATH)/$(@F)

$(COBJS): %.o: %.c $(PROJ_CHDRS)
	@echo +++ Compiling [$(notdir $<)]
	@$(CC) $(CFLAGS) -c $< -o $(OUTPUT_PATH)/$(@F)

$(CPPOBJS): %.o: %.cpp $(PROJ_CHDRS)
	@echo +++ Compiling [$(notdir $<)]
	@$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_PATH)/$(@F)
#	echo $(NM) $(OUTPUT_PATH)/$(@F)

$(OUTPUT_PATH):
	@-mkdir $(OUTPUT_PATH)

clean:
	-rm -f $(OUTPUT_PATH)/* $(OUTPUT_PATH)/*.*
	-rm -f $(OUTPUT_FILE_PATH)

$(OUTPUT_PATH)/%.o : %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

.phony: $(OUTPUT_PATH) clean test

upload: $(OUTPUT_FILE_PATH)
	$(OPENOCD) -f "$(RESOURCES_OPENOCD_UPLOAD)" -c "program $(OUTPUT_FILE_PATH) verify reset"

openocd: $(OUTPUT_FILE_PATH)
	$(OPENOCD) -f "$(RESOURCES_OPENOCD_START)" -c "init" -c "halt"

debug: $(OUTPUT_FILE_PATH)
	$(GDB) -x "$(RESOURCES_GDB)" -ex "reset" -readnow -se $(OUTPUT_FILE_PATH)
