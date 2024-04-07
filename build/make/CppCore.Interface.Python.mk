
include platforms/detect-host.mk

NAME       = CppCore.Interface.Python
NATIVENAME = CppCore.Interface.C
LIBNAME    = libcppcore
INCDIR     = ../../include/
SRCDIR     = ../../src/$(NAME)

################################################################################################

VERSIONFILE       = $(INCDIR)/CppCore/Version.h
VERSIONMACROMAJOR = CPPCORE_VERSION_MAJOR
VERSIONMACROMINOR = CPPCORE_VERSION_MINOR
VERSIONMACROPATCH = CPPCORE_VERSION_PATCH

include platforms/extract-version.mk

################################################################################################

.DEFAULT_GOAL := build
.PHONY: clean
.EXPORT_ALL_VARIABLES:

build:
	$(eval CPPCORE_VERSION=$(VERSION3))
	echo [VER] $(CPPCORE_VERSION)
ifeq ($(TARGET_OS),win)
	$(eval VSCMD_ARG_TGT_ARCH=$(TARGET_ARCH))
	$(call copyfiles,$(DISTDIR)/$(NATIVENAME)/$(TARGET_ARCH)/$(LIBNAME)$(EXTDLL),$(SRCDIR)/cppcore/$(LIBNAME)e$(EXTDLL))
endif
ifeq ($(TARGET_OS),osx)
	$(eval _PYTHON_HOST_PLATFORM=macosx-10.15-universal2)
	cp $(DISTDIR)/$(NATIVENAME)/$(LIBNAME)$(EXTDLL) $(SRCDIR)/cppcore/$(LIBNAME)$(EXTDLL)
endif
ifeq ($(TARGET_OS),linux)
	$(eval _PYTHON_HOST_PLATFORM:=$(shell \
	  case $(TARGET_ARCH) in \
	    (x64)   echo linux_x86_64;; \
		(x86)   echo linux_i686;; \
		(arm64) echo linux_aarch64;; \
		(arm)   echo linux_armv7hl;; \
	  esac))
	cp $(DISTDIR)/$(NATIVENAME)-$(TARGET_ARCH)/usr/lib/$(LIBNAME)$(EXTDLL) $(SRCDIR)/cppcore/$(LIBNAME)$(EXTDLL)
endif
	python -m build --wheel --outdir $(DISTDIR) $(SRCDIR)
