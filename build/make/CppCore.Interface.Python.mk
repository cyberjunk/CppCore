
include platforms/detect-host.mk

NAME       = CppCore.Interface.Python
APPNAME    = CppCore.Interface.Python
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
ifeq ($(TARGET_OS),win)
	$(eval VSCMD_ARG_TGT_ARCH=$(TARGET_ARCH))
	$(call copyfiles,$(DISTDIR)/CppCore.Interface.C/$(TARGET_ARCH)/CppCore.Interface.C$(EXTDLL),$(SRCDIR)/libcppcore$(EXTDLL))
endif
ifeq ($(TARGET_OS),osx)
	$(eval _PYTHON_HOST_PLATFORM=macosx-10.15-universal2)
	cp $(DISTDIR)/CppCore.Interface.C/CppCore.Interface.C.dylib $(SRCDIR)/cppcore/libcppcore.dylib
endif
ifeq ($(TARGET_OS),linux)
	$(eval _PYTHON_HOST_PLATFORM:=$(shell \
	  case $(TARGET_ARCH) in \
	    (x64)   echo linux_x86_64;; \
		(x86)   echo linux_i686;; \
		(arm64) echo linux_aarch64;; \
		(arm)   echo linux_armv7hl;; \
	  esac))
	cp $(DISTDIR)/CppCore.Interface.C-$(TARGET_ARCH)/usr/lib/CppCore.Interface.C.so $(SRCDIR)/cppcore/libcppcore.so
endif
#	echo ${VSCMD_ARG_TGT_ARCH}
#	echo ${CPPCORE_VERSION}
	python -m build --wheel --outdir $(DISTDIR) $(SRCDIR)
