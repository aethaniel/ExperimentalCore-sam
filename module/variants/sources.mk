#
#  SAM Arduino IDE variant makefile.
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
#| Source files                                                                          |
#|---------------------------------------------------------------------------------------|
SRC_DISCARDED=

SRC_ARCH_ARM=\
$(CORE_ARM_PATH)/core_math.cpp          \
$(CORE_ARM_PATH)/core_abi.cpp           \
$(CORE_ARM_PATH)/core_hooks.c           \
$(CORE_ARM_PATH)/core_itoa.c            \
$(CORE_ARM_PATH)/core_main.cpp          \
$(CORE_ARM_PATH)/core_shift.c           \
$(CORE_ARM_PATH)/core_cortex_vectors.c  \
$(CORE_ARM_PATH)/CorePrint.cpp          \
$(CORE_ARM_PATH)/CoreRingBuffer.cpp     \
$(CORE_ARM_PATH)/CoreStream.cpp         \
$(CORE_ARM_PATH)/CoreString.cpp         \
$(CORE_ARM_PATH)/IPAddress.cpp
INCLUDES += -I$(CORE_ARM_PATH)

SRC_ARCH_COMMON=\
$(CORE_COMMON_PATH)/core_new.cpp
INCLUDES += -I$(CORE_COMMON_PATH)

SRC_ARCH_AVR=\
$(CORE_AVR_PATH)/core_dtostrf.c
INCLUDES += -I$(CORE_AVR_PATH)

SRC_PORT_SAM=\
$(CORE_SAM_PATH)/core_init.c            \
$(CORE_SAM_PATH)/core_delay.c           \
$(CORE_SAM_PATH)/core_digital.c         \
$(CORE_SAM_PATH)/core_interrupts.c      \
$(CORE_SAM_PATH)/core_private.c         \
$(CORE_SAM_PATH)/core_reset.c           \
$(CORE_SAM_PATH)/core_watchdog.c        \
$(CORE_SAM_PATH)/core_pulse.cpp         \
$(CORE_SAM_PATH)/core_tone.cpp          \
$(CORE_SAM_PATH)/core_analog.c          \
$(CORE_SAM_PATH)/CoreSPI.cpp            \
$(CORE_SAM_PATH)/CoreWire.cpp           \
$(CORE_SAM_PATH)/CoreSerial.cpp
INCLUDES += -I$(CORE_SAM_PATH)

SOURCES=$(SRC_ARCH_ARM) $(SRC_ARCH_COMMON) $(SRC_ARCH_AVR) $(SRC_PORT_SAM)
