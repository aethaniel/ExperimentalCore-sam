SHELL := /bin/sh

ROOT_PATH := $(CURDIR)
EXAMPLES_PATH := $(ROOT_PATH)/cores/validation

all: print_info
	$(MAKE) --no-builtin-rules VARIANT_NAME=$(VARIANT_NAME) -C $(EXAMPLES_PATH)/blink

clean:
	$(MAKE) --no-builtin-rules VARIANT_NAME=$(VARIANT_NAME) clean -C $(EXAMPLES_PATH)/blink

.phony: print_info clean

print_info:
	@echo ----------------------------------------------------------
	@echo Compiling bootloader using
	@echo CURDIR    = $(CURDIR)
	@echo OS        = $(OS)
	@echo SHELL     = $(SHELL)
	@echo TERM      = $(TERM)
	@echo TRAVIS OS = $(TRAVIS_OS_NAME)
#	"$(CC)" -v
	env

