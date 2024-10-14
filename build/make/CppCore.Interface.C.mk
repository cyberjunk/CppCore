
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
             -std=c++17  \
             -fno-builtin \
             -fvisibility=hidden \
             -fno-exceptions \
             -fno-unwind-tables \
             -fno-asynchronous-unwind-tables \
             -mno-stack-arg-probe \
             -fno-stack-protector \
             -fno-stack-check
LINKFLAGS := $(LINKFLAGS) -fno-builtin
LINKPATH  := $(LINKPATH)
LINKLIBS  := $(LINKLIBS)
OBJS       = cppcore.o
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
             -shared \
             -nostdlib \
             -Xlinker /SAFESEH:NO \
             -Xlinker /ENTRY:DllMain \
             -Xlinker /SUBSYSTEM:CONSOLE",10.00" \
             -Xlinker /PDBALTPATH:$(LIBNAME)$(SUFFIX)$(EXTPDB) \
             -DLL
LINKLIBS  := $(LINKLIBS) -lUCRT -lMSVCRT
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
CXXFLAGS    := $(CXXFLAGS)
LINKFLAGS   := $(LINKFLAGS) \
               -shared \
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
CXXFLAGS  := $(CXXFLAGS)
LINKFLAGS := $(LINKFLAGS) \
             -shared \
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
LINKFLAGS := $(LINKFLAGS) -shared
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
             -shared \
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

ifeq ($(TARGET_OS),wasi)
OUTDIST   := $(DISTDIR)/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES) -DCPPCORE_NO_SOCKET -D_WASI_EMULATED_SIGNAL
CXXFLAGS  := $(CXXFLAGS)
CFLAGS    := $(CFLAGS)
DEC1MB    := 1048576
DEC8MB    := 8388608
HEX1MB    := 0x00100000
LINKFLAGS := $(LINKFLAGS) \
             -mexec-model=reactor \
             -Wl,-z,stack-size=$(HEX1MB) \
             -Wl,--initial-memory=$(DEC8MB) \
             -Wl,--max-memory=$(DEC8MB) \
             -Wl,--export,__data_end \
             -Wl,--export,__heap_base \
             -Wl,--export,__tls_base \
             -Wl,--export,__stack_pointer \
             -Wl,--export-dynamic \
             -Wl,--no-entry
LINKLIBS  := $(LINKLIBS)
RESO      := $(RESO)
endif

#-Wl,--import-memory \
#-Wl,--global-base=2048 \
#-Wl,-z,stack-size=0x00100000 \
#-Wl,--max-memory=8388608 \
#-Wl,--initial-memory=1179648 \
#-Wl,--initial-heap=1048576 \
#-Wl,--export-all \
#-Wl,--export,__tls_base \
#-Wl,--export,__stack_pointer \

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
