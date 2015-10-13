SHELL := /bin/sh

ROOT_PATH := $(CURDIR)
EXAMPLES_PATH := $(ROOT_PATH)/cores/validation

ifeq "TRAVIS" "true"
PRINT_INFO_TRAVIS=print_info_travis
else
PRINT_INFO_TRAVIS=
endif

# specify default variant, if not provided
VARIANT_NAME ?= atmel_sam4s_xplained

all: print_info $(PRINT_INFO_TRAVIS)
	$(MAKE) --no-builtin-rules VARIANT_NAME=$(VARIANT_NAME) -C $(EXAMPLES_PATH)/blink

clean:
	$(MAKE) --no-builtin-rules VARIANT_NAME=$(VARIANT_NAME) clean -C $(EXAMPLES_PATH)/blink

.phony: print_info clean $(PRINT_INFO_TRAVIS)

print_info:
	@echo ----------------------------------------------------------
	@echo Compiling bootloader using
	@echo CURDIR       = $(CURDIR)
	@echo OS           = $(OS)
	@echo SHELL        = $(SHELL)
	@echo TERM         = $(TERM)
	@echo VARIANT_NAME = $(VARIANT_NAME)
#	"$(CC)" -v
#	env

print_info_travis:
	@echo ----------------------------------------------------------
	@echo Travis-CI envvars
	@echo TRAVIS_OS_NAME      = $(TRAVIS_OS_NAME)
	@echo TRAVIS_LANGUAGE     = $(TRAVIS_LANGUAGE)
	@echo TRAVIS_REPO_SLUG    = $(TRAVIS_REPO_SLUG)
	@echo TRAVIS_BRANCH       = $(TRAVIS_BRANCH)
	@echo TRAVIS_TAG          = $(TRAVIS_TAG)
	@echo TRAVIS_PULL_REQUEST = $(TRAVIS_PULL_REQUEST)
	@echo TRAVIS_COMMIT       = $(TRAVIS_COMMIT)
	@echo TRAVIS_COMMIT_RANGE = $(TRAVIS_COMMIT_RANGE)
	@echo TRAVIS_JOB_ID       = $(TRAVIS_JOB_ID)
	@echo TRAVIS_JOB_NUMBER   = $(TRAVIS_JOB_NUMBER)
	@echo TRAVIS_BUILD_DIR    = $(TRAVIS_BUILD_DIR)
	@echo TRAVIS_BUILD_ID     = $(TRAVIS_BUILD_ID)
	@echo TRAVIS_BUILD_NUMBER = $(TRAVIS_BUILD_NUMBER)

