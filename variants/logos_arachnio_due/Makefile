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

DEVICE = __SAM4S2A__
CORE = cortex-m4
VARIANT_NAME = logos_arachnio_due
CORE_FREQUENCY = 4000000ul

ROOT_PATH=../..
VARIANT_PATH = $(ROOT_PATH)/variants/$(VARIANT_NAME)
RESOURCES_OPENOCD_UPLOAD = $(VARIANT_PATH)/openocd_scripts/variant_upload.cfg
RESOURCES_OPENOCD_START = $(VARIANT_PATH)/openocd_scripts/variant_debug_start.cfg
RESOURCES_GDB = $(VARIANT_PATH)/debug_scripts/variant.gdb
RESOURCES_LINKER = $(VARIANT_PATH)/linker_scripts/gcc/variant_without_bootloader.ld
CORE_ARM_PATH=$(ROOT_PATH)/cores/arduino/arch_arm
CORE_COMMON_PATH=$(ROOT_PATH)/cores/arduino/arch_common
CORE_AVR_PATH=$(ROOT_PATH)/cores/arduino/avr_compat
CORE_SAM_PATH=$(ROOT_PATH)/cores/arduino/port_sam

INCLUDES  = -I$(ROOT_PATH)/../ArduinoModule-CMSIS/CMSIS/CMSIS/Include
INCLUDES += -I$(ROOT_PATH)/../ArduinoModule-CMSIS-Atmel/CMSIS/Device/ATMEL
INCLUDES += -I$(ROOT_PATH)/cores/arduino

OUTPUT_PATH = $(VARIANT_PATH)/obj
OUTPUT_NAME = lib$(VARIANT_NAME)
OUTPUT_FILE_PATH = $(VARIANT_PATH)/$(OUTPUT_NAME).a

#|---------------------------------------------------------------------------------------|
#| Source files                                                                          |
#|---------------------------------------------------------------------------------------|
#$(CORE_SAM_PATH)/core_analog.c
#$(CORE_ARM_PATH)/IPAddress.cpp
#$(CORE_ARM_PATH)/IPAddress.h
#$(CORE_COMMON_PATH)/Server.h
#$(CORE_COMMON_PATH)/Udp.h
#$(CORE_COMMON_PATH)/Client.h
#$(CORE_SAM_PATH)/CoreSPI.cpp
#$(CORE_SAM_PATH)/CoreSPI.h
#$(CORE_SAM_PATH)/CoreWire.cpp
#$(CORE_SAM_PATH)/CoreWire.h
#$(CORE_SAM_PATH)/CoreSerial.cpp

SOURCES=\
$(CORE_ARM_PATH)/core_init.h            \
$(CORE_ARM_PATH)/core_math.cpp          \
$(CORE_ARM_PATH)/core_math.hpp          \
$(CORE_ARM_PATH)/core_abi.cpp           \
$(CORE_ARM_PATH)/core_character.h       \
$(CORE_ARM_PATH)/core_hooks.c           \
$(CORE_ARM_PATH)/core_hooks.h           \
$(CORE_ARM_PATH)/core_itoa.c            \
$(CORE_ARM_PATH)/core_itoa.h            \
$(CORE_ARM_PATH)/core_main.cpp          \
$(CORE_ARM_PATH)/core_reset.hpp         \
$(CORE_ARM_PATH)/core_shift.c           \
$(CORE_ARM_PATH)/core_shift.h           \
$(CORE_ARM_PATH)/core_cortex_vectors.c  \
$(CORE_ARM_PATH)/core_cortex_vectors.h  \
$(CORE_ARM_PATH)/CorePrint.cpp          \
$(CORE_ARM_PATH)/CorePrint.hpp          \
$(CORE_ARM_PATH)/CorePrintable.hpp      \
$(CORE_ARM_PATH)/CoreHardwareSerial.hpp \
$(CORE_ARM_PATH)/CoreRingBuffer.cpp     \
$(CORE_ARM_PATH)/CoreRingBuffer.hpp     \
$(CORE_ARM_PATH)/CoreStream.cpp         \
$(CORE_ARM_PATH)/CoreStream.hpp         \
$(CORE_ARM_PATH)/CoreString.cpp         \
$(CORE_ARM_PATH)/CoreString.hpp         \
$(CORE_COMMON_PATH)/core_binary.h       \
$(CORE_COMMON_PATH)/core_constants.h    \
$(CORE_COMMON_PATH)/core_new.cpp        \
$(CORE_COMMON_PATH)/core_new.hpp        \
$(CORE_AVR_PATH)/core_dtostrf.c         \
$(CORE_AVR_PATH)/core_dtostrf.h         \
$(CORE_AVR_PATH)/core_interrupt.h       \
$(CORE_AVR_PATH)/core_pgmspace.h        \
$(CORE_SAM_PATH)/Arduino.h              \
$(CORE_SAM_PATH)/core_init.c            \
$(CORE_SAM_PATH)/core_analog.h          \
$(CORE_SAM_PATH)/core_delay.c           \
$(CORE_SAM_PATH)/core_delay.h           \
$(CORE_SAM_PATH)/core_digital.c         \
$(CORE_SAM_PATH)/core_digital.h         \
$(CORE_SAM_PATH)/core_interrupts.c      \
$(CORE_SAM_PATH)/core_interrupts.h      \
$(CORE_SAM_PATH)/core_private.c         \
$(CORE_SAM_PATH)/core_private.h         \
$(CORE_SAM_PATH)/core_reset.cpp         \
$(CORE_SAM_PATH)/core_variant.h         \
$(CORE_SAM_PATH)/core_pulse.cpp         \
$(CORE_SAM_PATH)/core_pulse.hpp         \
$(CORE_SAM_PATH)/core_tone.cpp          \
$(CORE_SAM_PATH)/core_tone.hpp          \
$(CORE_SAM_PATH)/CoreSerial.hpp         \
$(VARIANT_PATH)/pins_arduino.h          \
$(VARIANT_PATH)/variant.h               \
$(VARIANT_PATH)/variant.cpp             \
$(VARIANT_PATH)/variant_startup.c       \
$(VARIANT_PATH)/variant_init.cpp

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
LIB_PATH  = -L$(dir $(RESOURCES_LINKER))

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
COMMON_FLAGS += --param max-inline-insns-single=500

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

#|---------------------------------------------------------------------------------------|
#| Define targets                                                                        |
#|---------------------------------------------------------------------------------------|
AOBJS = $(patsubst %.s,%.o,$(PROJ_ASRCS))
COBJS = $(patsubst %.c,%.o,$(PROJ_CSRCS))
CPPOBJS = $(patsubst %.cpp,%.o,$(PROJ_CPPSRCS))

all: $(OUTPUT_FILE_PATH)

test:
	@echo VPATH ---------------------------------------------------------------------------------------
	@echo $(VPATH)
	@echo SOURCES -------------------------------------------------------------------------------------
	@echo $(SOURCES)
	@echo PROJ_CHDRS ----------------------------------------------------------------------------------
	@echo $(PROJ_CHDRS)
	@echo PROJ_CPPHDRS --------------------------------------------------------------------------------
	@echo $(PROJ_CPPHDRS)
	@echo AOBJS ---------------------------------------------------------------------------------------
	@echo $(AOBJS)
	@echo PROJ_CSRCS ----------------------------------------------------------------------------------
	@echo $(PROJ_CSRCS)
	@echo COBJS ---------------------------------------------------------------------------------------
	@echo $(COBJS)
	@echo PROJ_CPPSRCS --------------------------------------------------------------------------------
	@echo $(PROJ_CPPSRCS)
	@echo CPPOBJS -------------------------------------------------------------------------------------
	@echo $(CPPOBJS)
	@echo ---------------------------------------------------------------------------------------
	@echo $(PWD)

$(OUTPUT_FILE_PATH): $(VARIANT_PATH)/Makefile $(OUTPUT_PATH) $(AOBJS) $(COBJS) $(CPPOBJS)
	$(AR) -rv $(OUTPUT_FILE_PATH) $(addprefix $(OUTPUT_PATH)/,$(AOBJS))
	$(AR) -rv $(OUTPUT_FILE_PATH) $(addprefix $(OUTPUT_PATH)/,$(COBJS))
	$(AR) -rv $(OUTPUT_FILE_PATH) $(addprefix $(OUTPUT_PATH)/,$(CPPOBJS))
	$(NM) $(OUTPUT_FILE_PATH) > $(VARIANT_PATH)/$(OUTPUT_NAME)_symbols.txt

#|---------------------------------------------------------------------------------------|
#| Compile and assemble                                                                  |
#|---------------------------------------------------------------------------------------|
$(AOBJS): %.o: %.s $(PROJ_CHDRS)
	@echo +++ Assembling [$(notdir $<)]
	@$(AS) $(AFLAGS) $< -o $(OUTPUT_PATH)/$(@F)

$(COBJS): %.o: %.c $(PROJ_CHDRS)
	@echo +++ Compiling [$(notdir $<)]
	@$(CC) $(CFLAGS) -c $< -o $(OUTPUT_PATH)/$(@F)

$(CPPOBJS): %.o: %.cpp $(PROJ_CPPHDRS) $(PROJ_CHDRS)
	@echo +++ Compiling [$(notdir $<)]
	@$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_PATH)/$(@F)

$(OUTPUT_PATH):
	@-mkdir $(OUTPUT_PATH)

clean:
	-rm -f $(OUTPUT_PATH)/* $(OUTPUT_PATH)/*.*
	-rm -f $(OUTPUT_FILE_PATH)
	-rm -f $(VARIANT_PATH)/$(OUTPUT_NAME)_symbols.txt

$(OUTPUT_PATH)/%.o : %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

.phony: $(OUTPUT_PATH) clean test

