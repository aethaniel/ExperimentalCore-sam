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

#-------------------------------------------------------------------------------
# Tools and definitions
#-------------------------------------------------------------------------------

# Set DEBUG variable for once if not coming from command line
ifndef DEBUG
DEBUG := 0
endif

# Tool suffix when cross-compiling
CROSS_COMPILE := arm-none-eabi-

# Compilation tools
CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar
SIZE := $(CROSS_COMPILE)size
STRIP := $(CROSS_COMPILE)strip
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
GDB := $(CROSS_COMPILE)gdb
NM := $(CROSS_COMPILE)nm

ROOT_PATH = ../../../..

#VARIANT_NAME ?= atmel_sam4s_xplained
#VARIANT_NAME ?= atmel_sam4s_xplained_pro
VARIANT_NAME ?= atmel_samg55_xplained_pro
VARIANT_PATH = $(ROOT_PATH)/variants/$(VARIANT_NAME)
include $(VARIANT_PATH)/variant.mk

CORE_ROOT_PATH := $(ROOT_PATH)/cores/arduino
CORE_ARM_PATH := $(ROOT_PATH)/cores/arduino/arch_arm
CORE_COMMON_PATH := $(ROOT_PATH)/cores/arduino/arch_common
CORE_AVR_PATH := $(ROOT_PATH)/cores/arduino/avr_compat
CORE_SAM_PATH := $(ROOT_PATH)/cores/arduino/port_sam

PROJECT_PATH := $(ROOT_PATH)/libraries/tests/examples/$(PROJECT_NAME)

RESOURCES_JLINK_UPLOAD := $(PROJECT_PATH)/$(VARIANT_NAME).jlink
RESOURCES_OPENOCD_UPLOAD:= $(VARIANT_PATH)/openocd_scripts/variant_upload.cfg
RESOURCES_OPENOCD_START := $(VARIANT_PATH)/openocd_scripts/variant_debug_start.cfg
RESOURCES_GDB := $(VARIANT_PATH)/debug_scripts/variant.gdb
RESOURCES_LINKER := $(VARIANT_PATH)/linker_scripts/gcc/variant_without_bootloader.ld

#|---------------------------------------------------------------------------------------|
#| Upload tools                                                                          |
#|---------------------------------------------------------------------------------------|
# change this value if openocd isn't in the user/system PATH
TOOL_OPENOCD := openocd
TOOL_JLINK := JLink
TOOL_EDBG := $(ROOT_PATH)/tools/edbg

#|---------------------------------------------------------------------------------------|
#| Include paths                                                                         |
#|---------------------------------------------------------------------------------------|
INCLUDES  = -I$(ROOT_PATH)/tools/CMSIS_API/Include
INCLUDES += -I$(ROOT_PATH)/tools/CMSIS_Devices/ATMEL
INCLUDES += -I$(VARIANT_PATH)
INCLUDES += -I$(CORE_ROOT_PATH)
INCLUDES += -I$(CORE_ARM_PATH)
INCLUDES += -I$(CORE_COMMON_PATH)
INCLUDES += -I$(CORE_AVR_PATH)
INCLUDES += -I$(CORE_SAM_PATH)
INCLUDES += -I$(PROJECT_PATH)

#|---------------------------------------------------------------------------------------|
#| Output paths                                                                          |
#|---------------------------------------------------------------------------------------|
OBJ_PATH := $(PROJECT_PATH)/obj_$(VARIANT_NAME)
OUTPUT_FILE_PATH := $(PROJECT_PATH)/$(PROJECT_NAME)_$(VARIANT_NAME)
VARIANT_LIB_PATH := $(VARIANT_PATH)/lib$(VARIANT_NAME).a

#|---------------------------------------------------------------------------------------|
#| Source files                                                                          |
#|---------------------------------------------------------------------------------------|
SOURCES =\
$(PROJECT_PATH)/$(PROJECT_NAME).cpp
