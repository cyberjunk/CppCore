
include platforms/detect-host.mk

NAME       = CppCore.Interface.C
LIBNAME    = libcppcore
INCDIR     = ../../include/
SRCDIR     = ../../src/$(NAME)
OBJDIR    := $(OBJDIR)/$(NAME)
DEFINES   := $(DEFINES)
INCLUDES  := $(INCLUDES) \
             -I$(INCDIR) \
             -I$(SRCDIR)
CXXFLAGS  := $(CXXFLAGS) \
             -std=c++17 \
             -fno-exceptions \
             -fno-unwind-tables \
             -fno-asynchronous-unwind-tables \
             -fno-stack-protector \
             -fno-stack-check \
             -mno-stack-arg-probe
LINKFLAGS := $(LINKFLAGS) -shared
LINKPATH  := $(LINKPATH)
LINKLIBS  := $(LINKLIBS)
OBJS       = cppcore.o
RESO       =

#-fno-builtin -nostdlib -fno-common 
# -Wl,-no-pie -Wl,--no-dynamic-linker

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
CXXFLAGS  := $(CXXFLAGS) -fno-builtin
LINKFLAGS := $(LINKFLAGS) \
             -fno-builtin \
             -nostdlib \
             -Xlinker /ENTRY:DllMain \
             -Xlinker /SAFESEH:NO \
             -Xlinker /SUBSYSTEM:CONSOLE",10.00" \
             -Xlinker /PDBALTPATH:$(LIBNAME)$(SUFFIX)$(EXTPDB) \
             -DLL
ifeq ($(MODE),release)
LINKLIBS  := $(LINKLIBS) -lUCRT -lMSVCRT
else
LINKLIBS  := $(LINKLIBS) -lUCRTD -lMSVCRTD
endif
RESO      := $(RESO) resources.res
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
CXXFLAGS    := $(CXXFLAGS) -fno-builtin
LINKFLAGS   := $(LINKFLAGS) \
               -fno-builtin \
               -dynamiclib \
               -nostdlib \
               -current_version $(VERSION3) \
               -compatibility_version $(VERSION2) \
               -install_name $(LIBNAME)$(EXTDLL) \
               -Wl,-object_path_lto,$(OBJDIR)/lto.o \
               -Wl,-no_data_in_code_info \
               -Wl,-no_function_starts \
               -Wl,-no_keep_dwarf_unwind \
               -Wl,-no_compact_unwind
LINKLIBS    := $(LINKLIBS) -lSystem
RESO        := $(RESO)
ifeq ($(TARGET_ARCH),x86)
DEFINES     := $(DEFINES)
endif
ifeq ($(TARGET_ARCH),x64)
DEFINES     := $(DEFINES)
LINKFLAGS   := $(LINKFLAGS)
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
CXXFLAGS  := $(CXXFLAGS) -fno-builtin
LINKFLAGS := $(LINKFLAGS) \
             -fno-builtin \
             -nostdlib \
             -Wl,--no-eh-frame-hdr
LINKLIBS  := $(LINKLIBS) -lc
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
CXXFLAGS  := $(CXXFLAGS) -fno-builtin
LINKFLAGS := $(LINKFLAGS) \
             -fno-builtin \
             -dynamiclib \
             -nostdlib \
             -install_name @rpath/$(LIBNAME)$(EXTDLL) \
             -Wl,-object_path_lto,$(OBJDIR)/lto.o \
             -Wl,-no_data_in_code_info \
             -Wl,-no_function_starts \
             -Wl,-no_keep_dwarf_unwind \
             -Wl,-no_compact_unwind
LINKLIBS  := $(LINKLIBS) -lSystem
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
	@echo [LNK] $(LIBDIR)/$(LIBNAME)$(SUFFIX)$(EXTDLL)
	$(LINK) $(LINKFLAGS) $(LINKPATH) $(OBJS) $(RESO) $(LINKLIBS) -o $(LIBDIR)/$(LIBNAME)$(SUFFIX)$(EXTDLL)

clean:
	-$(call deletefiles,$(OBJDIR),*.o)
	-$(call deletefiles,$(OBJDIR),*.res)
	-$(call deletefiles,$(LIBDIR),$(LIBNAME)$(SUFFIX)$(EXTDLL))
	-$(call deletefiles,$(LIBDIR),$(LIBNAME)$(SUFFIX)$(EXTLIB))
	-$(call deletefiles,$(LIBDIR),$(LIBNAME)$(SUFFIX)$(EXTPDB))

################################################################################################

include ./platforms/dist.mk
