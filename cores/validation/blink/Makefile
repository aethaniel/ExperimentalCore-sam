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

CORE = cortex-m4

#DEVICE = __SAM4S16C__
#VARIANT_NAME = atmel_sam4s_xplained
#VARIANT_FREQUENCY = 120000000ul

DEVICE = __SAM4SD32C__
VARIANT_NAME = atmel_sam4s_xplained_pro
VARIANT_FREQUENCY = 120000000ul

#DEVICE = __SAM4S16C__
#VARIANT_NAME = atmel_sam4s_wpir_rd
#VARIANT_FREQUENCY = 120000000ul

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

#|---------------------------------------------------------------------------------------|
#| Tools                                                                                 |
#|---------------------------------------------------------------------------------------|
# change this value if openocd isn't in the user/system PATH
TOOL_OPENOCD = openocd
TOOL_EDBG = $(ROOT_PATH)/tools/edbg

#|---------------------------------------------------------------------------------------|
#| Include paths                                                                         |
#|---------------------------------------------------------------------------------------|
INCLUDES  = -I$(ROOT_PATH)/tools/CMSIS_API/Include
INCLUDES += -I$(ROOT_PATH)/tools/CMSIS_Devices/ATMEL
INCLUDES += -I$(ROOT_PATH)/cores/arduino

#|---------------------------------------------------------------------------------------|
#| Output paths                                                                          |
#|---------------------------------------------------------------------------------------|
OUTPUT_PATH = $(PROJECT_PATH)/obj
OUTPUT_NAME = $(PROJECT_NAME)
OUTPUT_FILE_PATH = $(PROJECT_PATH)/$(PROJECT_NAME)
VARIANT_LIB_PATH = $(VARIANT_PATH)/lib$(VARIANT_NAME).a

#|---------------------------------------------------------------------------------------|
#| Source files                                                                          |
#|---------------------------------------------------------------------------------------|
SOURCES=\
$(CORE_ARM_PATH)/core_init.h            \
$(CORE_ARM_PATH)/CoreHardwareSerial.hpp \
$(CORE_ARM_PATH)/core_math.hpp          \
$(CORE_ARM_PATH)/CorePrint.hpp          \
$(CORE_ARM_PATH)/CorePrintable.hpp      \
$(CORE_ARM_PATH)/CoreRingBuffer.hpp     \
$(CORE_ARM_PATH)/CoreStream.hpp         \
$(CORE_ARM_PATH)/CoreString.hpp         \
$(CORE_ARM_PATH)/IPAddress.hpp          \
$(CORE_ARM_PATH)/core_character.h       \
$(CORE_ARM_PATH)/core_itoa.h            \
$(CORE_ARM_PATH)/core_reset.h           \
$(CORE_ARM_PATH)/core_shift.h           \
$(CORE_ARM_PATH)/core_hooks.h           \
$(CORE_ARM_PATH)/core_cortex_vectors.h  \
$(CORE_COMMON_PATH)/Server.hpp          \
$(CORE_COMMON_PATH)/Udp.hpp             \
$(CORE_COMMON_PATH)/Client.hpp          \
$(CORE_COMMON_PATH)/core_binary.h       \
$(CORE_COMMON_PATH)/core_constants.h    \
$(CORE_COMMON_PATH)/core_new.hpp        \
$(CORE_COMMON_PATH)/core_reset.h        \
$(CORE_COMMON_PATH)/core_watchdog.h     \
$(CORE_AVR_PATH)/core_dtostrf.h         \
$(CORE_AVR_PATH)/core_interrupt.h       \
$(CORE_AVR_PATH)/core_pgmspace.h        \
$(CORE_SAM_PATH)/Arduino.h              \
$(CORE_SAM_PATH)/CoreSerial.hpp         \
$(CORE_SAM_PATH)/core_analog.h          \
$(CORE_SAM_PATH)/core_delay.h           \
$(CORE_SAM_PATH)/core_digital.h         \
$(CORE_SAM_PATH)/core_interrupts.h      \
$(CORE_SAM_PATH)/core_private.h         \
$(CORE_SAM_PATH)/core_pulse.hpp         \
$(CORE_SAM_PATH)/core_tone.hpp          \
$(CORE_SAM_PATH)/core_variant.h         \
$(CORE_SAM_PATH)/CoreSerial.hpp         \
$(CORE_SAM_PATH)/CoreSPI.hpp            \
$(CORE_SAM_PATH)/CoreWire.hpp           \
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
PROJ_CPPHDRS  = $(filter %.hpp,$(foreach file,$(SOURCES),$(notdir $(file))))

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
COMMON_FLAGS += $(INC_PATH) -DF_CPU=$(VARIANT_FREQUENCY)
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
#LDFLAGS += -nostartfiles
#-std=c++11 --param max-inline-insns-single=100 -fno-rtti -fno-exceptions -fno-threadsafe-statics

#|---------------------------------------------------------------------------------------|
#| Define targets                                                                        |
#|---------------------------------------------------------------------------------------|
AOBJS = $(patsubst %.s,%.o,$(PROJ_ASRCS))
COBJS = $(patsubst %.c,%.o,$(PROJ_CSRCS))
CPPOBJS = $(patsubst %.cpp,%.o,$(PROJ_CPPSRCS))

all: $(OUTPUT_FILE_PATH).bin

$(OUTPUT_FILE_PATH).bin: $(OUTPUT_FILE_PATH).elf
	$(OBJCOPY) -O binary $(OUTPUT_FILE_PATH).elf $(OUTPUT_FILE_PATH).bin

$(OUTPUT_FILE_PATH).elf: $(OUTPUT_PATH) $(VARIANT_LIB_PATH) $(PROJECT_PATH)/Makefile $(RESOURCES_LINKER) $(AOBJS) $(COBJS) $(CPPOBJS)
	$(CC) $(LDFLAGS) "-T$(notdir $(RESOURCES_LINKER))" "-Wl,-Map,$(OUTPUT_FILE_PATH).map" --specs=nano.specs --specs=nosys.specs -o "$(OUTPUT_FILE_PATH).elf" -Wl,--start-group $(addprefix $(OUTPUT_PATH)/,$(AOBJS)) $(addprefix $(OUTPUT_PATH)/,$(COBJS)) $(addprefix $(OUTPUT_PATH)/,$(CPPOBJS)) -lm -lgcc -l$(VARIANT_NAME) -Wl,--end-group
	$(NM) $(OUTPUT_FILE_PATH).elf >$(OUTPUT_FILE_PATH)_symbols.txt
	$(SIZE) --format=sysv -t -x $(OUTPUT_FILE_PATH).elf

.phony: $(VARIANT_LIB_PATH)
$(VARIANT_LIB_PATH):
#	make --no-builtin-rules --print-directory -C $(dir $(VARIANT_LIB_PATH))
	make --no-builtin-rules -C $(dir $(VARIANT_LIB_PATH)) DEBUG=$(DEBUG)

#|---------------------------------------------------------------------------------------|
#| Compile and assemble                                                                  |
#|---------------------------------------------------------------------------------------|
$(AOBJS): %.o: %.s $(PROJ_CHDRS)
	@echo +++ Assembling [$(notdir $<)]
	@$(AS) $(AFLAGS) $< -o $(OUTPUT_PATH)/$(@F)

$(COBJS): %.o: %.c $(PROJ_CHDRS)
	@echo +++ Compiling [$(notdir $<)]
	@$(CC) $(CFLAGS) -c $< -o $(OUTPUT_PATH)/$(@F)

$(CPPOBJS): %.o: %.cpp $(PROJ_CHDRS) $(PROJ_CPPHDRS)
	@echo +++ Compiling [$(notdir $<)]
	@$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_PATH)/$(@F)
#	echo $(NM) $(OUTPUT_PATH)/$(@F)

$(OUTPUT_PATH):
	@-mkdir $(OUTPUT_PATH)

clean:
	-rm -f $(OUTPUT_PATH)/* $(OUTPUT_PATH)/*.*
	-rmdir $(OUTPUT_PATH)
	-rm -f $(OUTPUT_FILE_PATH).elf
	-rm -f $(OUTPUT_FILE_PATH).bin
	-rm -f $(OUTPUT_FILE_PATH).map
	-rm -f $(OUTPUT_FILE_PATH)_symbols.txt

$(OUTPUT_PATH)/%.o : %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

.phony: $(OUTPUT_PATH) clean test

upload_openocd: $(OUTPUT_FILE_PATH).elf
	$(TOOL_OPENOCD) -f "$(RESOURCES_OPENOCD_UPLOAD)" -c "program $(OUTPUT_FILE_PATH).elf verify reset"

upload_edbg: $(OUTPUT_FILE_PATH).bin
	$(TOOL_EDBG) -l
	$(TOOL_EDBG) -bepvf $(OUTPUT_FILE_PATH).bin

openocd: $(OUTPUT_FILE_PATH).elf
	$(TOOL_OPENOCD) -f "$(RESOURCES_OPENOCD_START)" -c "init" -c "halt"

debug: $(OUTPUT_FILE_PATH).elf
	$(GDB) -x "$(RESOURCES_GDB)" -readnow -se $(OUTPUT_FILE_PATH).elf
