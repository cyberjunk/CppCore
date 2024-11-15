# Generic
EXTBIN     = .exe
EXTLIB     = .lib
EXTDLL     = .dll
EXTPDB     = .pdb
OBJDIR     = obj/win-arm64-$(MODE)
LIBDIR     = lib/win-arm64
BINDIR     = bin/win-arm64
DISTDIR    = ../../dist/win-10
TARGET     = aarch64-pc-windows-msvc
DEFINES    = -DWIN32 -DWIN64
INCLUDES   = 
CXX        = clang++
CXXFLAGS   = -target $(TARGET) -fno-strict-aliasing
CC         = clang
CFLAGS     = -target $(TARGET) -fno-strict-aliasing
AR         = llvm-ar
ARFLAGS    = rcs
STRIP      = llvm-strip
STRIPFLAGS = --strip-all
LINK       = $(CXX)
LINKFLAGS  = -target $(TARGET) -fuse-ld=lld -Xlinker /MACHINE:ARM64 -fno-strict-aliasing
LINKPATH   =
LINKLIBS   = 

# MSVC Resource Compiler
RC         = llvm-rc
RCFLAGS    = -L0x0409 -NOLOGO

# CPU Flags
ifeq ($(TARGET_CPUREV),legacy)
CPUFLAGS   = -march=armv8-a -mtune=generic
endif
ifeq ($(TARGET_CPUREV),default)
CPUFLAGS   = -march=armv8-a -mtune=generic
endif
ifeq ($(TARGET_CPUREV),modern)
CPUFLAGS   = -march=armv8-a+crc+sha2 -mtune=generic
endif

# Debug vs. Release
ifeq ($(MODE),release)
DEFINES   := $(DEFINES) -DNDEBUG
CXXFLAGS  := $(CXXFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-plt
CFLAGS    := $(CFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-plt
LINKFLAGS := $(LINKFLAGS) -flto=thin -O3 -g -o optimized.bc -fomit-frame-pointer -RELEASE \
             -Xlinker /OPT:REF \
             -Xlinker /OPT:ICF=3 \
             -Xlinker /DEBUG:FULL \
             -Xlinker /MANIFEST:EMBED
LINKLIBS  := $(LINKLIBS)
else
DEFINES   := $(DEFINES) -D_DEBUG
CXXFLAGS  := $(CXXFLAGS) -Og -g3 -Xclang -MTd
CFLAGS    := $(CFLAGS) -Og -g3 -Xclang -MTd
LINKFLAGS := $(LINKFLAGS) -g3 -DEBUG
LINKLIBS  := $(LINKLIBS) -llibcmtd.lib -lDbgHelp.lib
endif
