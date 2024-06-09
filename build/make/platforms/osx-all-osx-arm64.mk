# Generic
EXTBIN     = 
EXTLIB     = .a
EXTDLL     = .dylib
EXTPDB     = .pdb
OBJDIR     = obj/osx-arm64-$(MODE)
LIBDIR     = lib/osx-arm64
BINDIR     = bin/osx-arm64
DISTDIR    = ../../dist/osx-10.15
TARGET     = arm64-apple-darwin19.6.0
MINVER     = -mmacosx-version-min=10.15
DEFINES    = 
INCLUDES   = 
CXX        = clang++
CXXFLAGS   = $(MINVER) -target $(TARGET) -isysroot $(shell xcrun --sdk macosx --show-sdk-path) -static -fno-strict-aliasing
CC         = clang
CFLAGS     = $(MINVER) -target $(TARGET) -isysroot $(shell xcrun --sdk macosx --show-sdk-path) -static -fno-strict-aliasing
AR         = ar
ARFLAGS    = rcs
STRIP      = strip
STRIPFLAGS = -S
LINK       = $(CXX)
LINKFLAGS  = $(MINVER) -target $(TARGET) -isysroot $(shell xcrun --sdk macosx --show-sdk-path) -fno-strict-aliasing
LINKPATH   =
LINKLIBS   = 

# CPU Flags
ifeq ($(TARGET_CPUREV),legacy)
CPUFLAGS   = -mcpu=apple-m1 -mtune=generic
endif
ifeq ($(TARGET_CPUREV),default)
CPUFLAGS   = -mcpu=apple-m1 -mtune=generic
endif
ifeq ($(TARGET_CPUREV),modern)
CPUFLAGS   = -mcpu=apple-m1 -mtune=generic
endif

# Debug vs. Release
ifeq ($(MODE),release)
DEFINES   := $(DEFINES) -DNDEBUG
CXXFLAGS  := $(CXXFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-plt
CFLAGS    := $(CFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-plt
LINKFLAGS := $(LINKFLAGS) -flto=thin -O3 -g -dead_strip -dead_strip_dylibs -fomit-frame-pointer
else
DEFINES   := $(DEFINES) -D_DEBUG
CXXFLAGS  := $(CXXFLAGS) -Og -g3
CFLAGS    := $(CFLAGS) -Og -g3
LINKFLAGS := $(LINKFLAGS) -g3
endif
