
include platforms/detect-host.mk

NAME       = CppCore.Interface.JS
NATIVENAME = CppCore.Interface.C
LIBNAME    = libcppcore
INCDIR     = ../../include/
SRCDIR     = ../../src/$(NAME)
BROWSERDIR = ../../dist/browser
WASIDIR    = ../../dist/wasi

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
	-$(call rmdir,$(BROWSERDIR)/$(NAME))
	$(call mkdir,$(BROWSERDIR)/$(NAME))
	$(call copyfiles,$(WASIDIR)/$(NATIVENAME)/wasm32/$(LIBNAME).wasm,$(BROWSERDIR)/$(NAME)/$(LIBNAME).wasm)	
	cd $(SRCDIR) && uglifyjs --compress --mangle --module --source-map --output $(BROWSERDIR)/$(NAME)/$(LIBNAME).js -- $(LIBNAME).js
	jq ".version = \"$(VERSION3)\"" $(SRCDIR)/package.json > $(BROWSERDIR)/$(NAME)/package.json
