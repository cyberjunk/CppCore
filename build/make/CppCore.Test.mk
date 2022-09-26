
include platforms/detect-host.mk

NAME       = CppCore.Test
OUT        = $(BINDIR)/$(NAME)$(SUFFIX)$(EXTBIN)
INCDIR     = ../../include
SRCDIR     = ../../src/$(NAME)
OBJDIR    := $(OBJDIR)/$(NAME)
DEFINES   := $(DEFINES)
INCLUDES  := $(INCLUDES) -I$(INCDIR)/
CXXFLAGS  := $(CXXFLAGS) \
             -std=c++17 \
             -Wno-deprecated-declarations \
             -Wno-c++20-extensions \
             -Wno-c++2a-extensions \
             -Wno-unknown-warning-option
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS)
LINKPATH  := $(LINKPATH)
LINKLIBS  := $(LINKLIBS)
OBJS       = Test.o
RESO       =

VERSIONFILE       = $(INCDIR)/CppCore/Version.h
VERSIONMACROMAJOR = CPPCORE_VERSION_MAJOR
VERSIONMACROMINOR = CPPCORE_VERSION_MINOR
VERSIONMACROPATCH = CPPCORE_VERSION_PATCH

################################################################################################
# CPU Specific

ifeq ($(TARGET_ARCH),x86)
CPUFLAGS  := $(CPUFLAGS)
endif

ifeq ($(TARGET_ARCH),x64)
CPUFLAGS  := $(CPUFLAGS)
endif

ifeq ($(TARGET_ARCH),arm)
CPUFLAGS  := $(CPUFLAGS)
endif

ifeq ($(TARGET_ARCH),arm64)
CPUFLAGS  := $(CPUFLAGS)
endif

################################################################################################
# OS Specific

ifeq ($(TARGET_OS),win)
OUTDIST   := $(DISTDIR)/$(NAME)-$(TARGET_ARCH)/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES) -D_CRT_SECURE_NO_WARNINGS -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
CXXFLAGS  := $(CXXFLAGS)
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS) -Xlinker /SUBSYSTEM:CONSOLE",10.00"
LINKLIBS  := $(LINKLIBS)
RESO      := $(RESO) Resources.res
endif

ifeq ($(TARGET_OS),osx)
OUTDIST   := $(DISTDIR)/$(NAME).app/Contents/MacOS/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES)
CXXFLAGS  := $(CXXFLAGS)
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS) -Wl,-object_path_lto,$(OBJDIR)/lto.o
LINKLIBS  := $(LINKLIBS)
RESO      := $(RESO)
endif

ifeq ($(TARGET_OS),linux)
OUTDIST   := $(DISTDIR)/$(NAME)-$(TARGET_ARCH)/usr/bin/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES)
CXXFLAGS  := $(CXXFLAGS)
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS)
LINKLIBS  := $(LINKLIBS) -lpthread
RESO      := $(RESO)
endif

ifeq ($(TARGET_OS),android)
OUTDIST   := $(DISTDIR)/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES)
CXXFLAGS  := $(CXXFLAGS)
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS)
LINKLIBS  := $(LINKLIBS) -ldl
RESO      := $(RESO)
endif

################################################################################################

OBJS := $(patsubst %,$(OBJDIR)/%,$(OBJS))

$(OBJDIR)/%.o:
	@echo [CXX] $@
	$(CXX) $(CPUFLAGS) $(DEFINES) $(INCLUDES) $(CXXFLAGS) -c $(@:$(OBJDIR)%.o=$(SRCDIR)%.cpp) -o $@

################################################################################################

RESO := $(patsubst %,$(OBJDIR)/%,$(RESO))

$(OBJDIR)/%.res:
	@echo [RC]  $@
	$(RC) $(RCFLAGS) $(DEFINES) $(INCLUDES) -FO$@ $(@:$(OBJDIR)/%.res=$(SRCDIR)/%.rc)

################################################################################################

.DEFAULT_GOAL := build
.PHONY: clean

build: $(OBJS) $(RESO)
	@echo [LNK] $(OUT)
	$(LINK) $(LINKFLAGS) $(LINKPATH) $(OBJS) $(RESO) $(LINKLIBS) -o $(OUT)

clean:
	$(call deletefiles,$(OBJDIR),*.o)
	$(call deletefiles,$(BINDIR),$(NAME)$(SUFFIX)$(EXTBIN))
	$(call deletefiles,$(BINDIR),$(NAME)$(SUFFIX)$(EXTPDB))
	$(call deletefiles,$(DISTDIR),*.deb)
	$(call deletefiles,$(DISTDIR),*.exe)
	$(call deletefiles,$(DISTDIR),*.msixbundle)
	$(call deletefiles,$(DISTDIR),*.pkg)
