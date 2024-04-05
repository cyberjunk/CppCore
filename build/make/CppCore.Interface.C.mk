
include platforms/detect-host.mk

NAME       = CppCore.Interface.C
APPNAME    = CppCore.Interface.C
INCDIR     = ../../include/
SRCDIR     = ../../src/$(NAME)
OBJDIR    := $(OBJDIR)/$(NAME)
DEFINES   := $(DEFINES)
INCLUDES  := $(INCLUDES) \
             -I$(INCDIR) \
             -I$(SRCDIR)
CXXFLAGS  := $(CXXFLAGS) \
             -std=c++17
LINKFLAGS := $(LINKFLAGS) -shared
LINKPATH  := $(LINKPATH)
LINKLIBS  := $(LINKLIBS)
OBJS       = Crypto.o
RESO       =

################################################################################################

VERSIONFILE       = $(INCDIR)/CppCore/Version.h
VERSIONMACROMAJOR = CPPCORE_VERSION_MAJOR
VERSIONMACROMINOR = CPPCORE_VERSION_MINOR
VERSIONMACROPATCH = CPPCORE_VERSION_PATCH

include platforms/extract-version.mk

################################################################################################
# CPU Specific

ifeq ($(TARGET_ARCH),x86)
DEFINES   := $(DEFINES)
endif

ifeq ($(TARGET_ARCH),x64)
DEFINES   := $(DEFINES)
endif

ifeq ($(TARGET_ARCH),arm)
DEFINES   := $(DEFINES)
endif

ifeq ($(TARGET_ARCH),arm64)
DEFINES   := $(DEFINES)
endif

################################################################################################
# OS Specific

ifeq ($(TARGET_OS),win)
DEFINES   := $(DEFINES)
INCLUDES  := $(INCLUDES)
CXXFLAGS  := $(CXXFLAGS)
LINKFLAGS := $(LINKFLAGS) \
             -Xlinker /SUBSYSTEM:CONSOLE",10.00" \
             -Xlinker /PDBALTPATH:$(NAME)$(SUFFIX)$(EXTPDB) \
             -DLL
LINKLIBS  := $(LINKLIBS)
RESO      := $(RESO) Resources.res
ifeq ($(TARGET_ARCH),x86)
DEFINES   := $(DEFINES) 
endif
ifeq ($(TARGET_ARCH),x64)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm64)
DEFINES   := $(DEFINES)
endif
endif

ifeq ($(TARGET_OS),osx)
DEFINES     := $(DEFINES)
INCLUDES    := $(INCLUDES)
CXXFLAGS    := $(CXXFLAGS)
LINKFLAGS   := $(LINKFLAGS) \
               -dynamiclib \
               -current_version $(VERSION3) \
               -compatibility_version $(VERSION2) \
               -install_name $(NAME)$(EXTDLL) \
               -Wl,-object_path_lto,$(OBJDIR)/lto.o
LINKLIBS    := $(LINKLIBS)
RESO        := $(RESO)
ifeq ($(TARGET_ARCH),x86)
DEFINES     := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),x64)
DEFINES     := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm)
DEFINES     := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm64)
DEFINES     := $(DEFINES)
endif
endif

ifeq ($(TARGET_OS),linux)
DEFINES   := $(DEFINES)
INCLUDES  := $(INCLUDES)
CXXFLAGS  := $(CXXFLAGS)
LINKFLAGS := $(LINKFLAGS)
LINKLIBS  := $(LINKLIBS)
RESO      := $(RESO)
ifeq ($(TARGET_ARCH),x86)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),x64)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm64)
DEFINES   := $(DEFINES)
endif
endif

ifeq ($(TARGET_OS),android)
DEFINES   := $(DEFINES)
CXXFLAGS  := $(CXXFLAGS)
LINKFLAGS := $(LINKFLAGS)
LINKLIBS  := $(LINKLIBS)
RESO      := $(RESO)
ifeq ($(TARGET_ARCH),x86)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),x64)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm64)
DEFINES   := $(DEFINES)
endif
endif

ifeq ($(TARGET_OS),ios)
DEFINES   := $(DEFINES)
CXXFLAGS  := $(CXXFLAGS)
LINKFLAGS := $(LINKFLAGS) \
             -dynamiclib \
             -install_name @rpath/$(NAME)$(EXTDLL)
LINKLIBS  := $(LINKLIBS)
RESO      := $(RESO)
ifeq ($(TARGET_ARCH),x86)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),x64)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm)
DEFINES   := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),arm64)
DEFINES   := $(DEFINES)
endif
endif

################################################################################################

OBJS  := $(patsubst %,$(OBJDIR)/%,$(OBJS))
JOBJS := $(patsubst %,$(OBJDIR)/%,$(JOBJS))

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
	@echo [LNK] $(LIBDIR)/$(NAME)$(SUFFIX)$(EXTDLL)
	$(LINK) $(LINKFLAGS) $(LINKPATH) $(OBJS) $(RESO) $(LINKLIBS) -o $(LIBDIR)/$(NAME)$(SUFFIX)$(EXTDLL)

clean:
	-$(call deletefiles,$(OBJDIR),*.o)
	-$(call deletefiles,$(OBJDIR),*.res)
	-$(call deletefiles,$(LIBDIR),$(NAME)$(SUFFIX)$(EXTDLL))
	-$(call deletefiles,$(LIBDIR),$(NAME)$(SUFFIX)$(EXTLIB))
	-$(call deletefiles,$(LIBDIR),$(NAME)$(SUFFIX)$(EXTPDB))

################################################################################################

include ./platforms/dist.mk
