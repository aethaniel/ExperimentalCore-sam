#
#  SAM Arduino IDE Module makefile.
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

SHELL := /bin/sh

.SUFFIXES: .d .o .c .h .cpp .hpp .s .S

#ROOT_PATH := $(CURDIR)
ROOT_PATH := .
EXAMPLES_PATH := $(ROOT_PATH)/module/libraries/tests/examples
VARIANTS_PATH := $(ROOT_PATH)/module/variants

# Variant list can be overriden via command line or ENV
VARIANTS?=$(shell ls --hide=*.mk $(VARIANTS_PATH))

ifeq ($(TRAVIS),true)
PRINT_INFO_TRAVIS=print_info_travis
else
PRINT_INFO_TRAVIS=
endif

CORE_VERSION := $(shell grep version= $(ROOT_PATH)/module/platform.txt | sed 's/version=//g')
PACKAGE_NAME := $(basename $(notdir $(CURDIR)))
FOLDER2ARCHIVE := module
#../$(basename $(notdir $(ROOT_PATH)))

# -----------------------------------------------------------------------------
# packaging specific
PACKAGE_OS_VALID=win32 win64 lin32 lin64 osx

# handle non-packaging request (normal build)
ifeq ($(PACKAGE_OS),)
# we are not requested to build the release package
# specify default variant, if not provided
VARIANT_NAME ?= atmel_sam4s_xplained
define PACKAGE_PROCESS=
@echo "Packaging won't be fully processed."
endef
else
  ifeq (,$(findstring $(PACKAGE_OS), $(PACKAGE_OS_VALID)))
    define PACKAGE_PROCESS=
@echo "Wrong OS specified for Packaging."
		endef
  else
		define PACKAGE_PROCESS=
@echo "Packaging for OS $(PACKAGE_OS)."
tar --transform "s|module|$(PACKAGE_NAME)-$(CORE_VERSION)-$(PACKAGE_OS)|g" --exclude=.gitattributes --exclude=.travis.yml --exclude-vcs \
--exclude-vcs-ignores --exclude=.clang --exclude=.codelite --exclude=obj --exclude=CMSIS_SVD \
-cvjf $(PACKAGE_NAME)-$(CORE_VERSION).tar.bz2 "$(FOLDER2ARCHIVE)"
    endef
  endif
endif
#		--transform "s/" \

# end of packaging specific
# -----------------------------------------------------------------------------


.PHONY: all clean print_info clean print_info_travis packaging packaging_clean

all: print_info $(PRINT_INFO_TRAVIS)
	$(MAKE) --no-builtin-rules VARIANT_NAME=$(VARIANT_NAME) -C $(EXAMPLES_PATH)/blink

clean:
	$(MAKE) --no-builtin-rules VARIANT_NAME=$(VARIANT_NAME) clean -C $(EXAMPLES_PATH)/blink

print_info:
	@echo ----------------------------------------------------------
	@echo Building ExperimentalCore-SAM using
	@echo CURDIR        = $(CURDIR)
	@echo OS            = $(OS)
	@echo SHELL         = $(SHELL)
	@echo TERM          = $(TERM)
	@echo VARIANTS_PATH = $(VARIANTS_PATH)
	@echo VARIANTS      = $(VARIANTS)
	@echo VARIANT_NAME  = $(VARIANT_NAME)
	@echo EXAMPLES_PATH = $(EXAMPLES_PATH)
	@echo CORE_VERSION  = $(CORE_VERSION)
	@echo PACKAGE_NAME  = $(PACKAGE_NAME)
	@echo PACKAGE_OS    = $(PACKAGE_OS)
#	@echo PACKAGE_PROCESS = $(PACKAGE_PROCESS)
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

# Arduino module packaging:
#   - exclude version control system files, here git files and folders .git, .gitattributes and .gitignore
#   - exclude 'extras' folder
#   - exclude 'obj' folder from variants
packaging: packaging_clean
	@echo ----------------------------------------------------------
	$(foreach variant,$(VARIANTS),$(MAKE) --no-builtin-rules VARIANT_NAME=$(variant) clean -C $(VARIANTS_PATH)/$(variant) ; )
	$(foreach variant,$(VARIANTS),$(MAKE) --no-builtin-rules VARIANT_NAME=$(variant) all -C $(VARIANTS_PATH)/$(variant) ; )
	$(PACKAGE_PROCESS)

packaging_clean:
	-$(RM) $(PACKAGE_NAME)-*.tar.bz2
