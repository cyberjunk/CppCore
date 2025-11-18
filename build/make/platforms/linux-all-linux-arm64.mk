# Generic
EXTBIN     = 
EXTLIB     = .a
EXTDLL     = .so
EXTPDB     = .pdb
OBJDIR     = obj/linux-arm64-$(MODE)
LIBDIR     = lib/linux-arm64
BINDIR     = bin/linux-arm64
TARGET     = aarch64-linux-gnu
DEFINES    =
INCLUDES   = -I/usr/$(TARGET)/include
CXX        = clang++
CXXFLAGS   = -target $(TARGET) -fPIC -static -fno-strict-aliasing -fno-strict-overflow
CC         = clang
CFLAGS     = -target $(TARGET) -fPIC -static -fno-strict-aliasing -fno-strict-overflow
AR         = llvm-ar
ARFLAGS    = rcs
STRIP      = llvm-strip
STRIPFLAGS = --strip-all
LINK       = $(CXX)
LINKFLAGS  = -target $(TARGET) -fuse-ld=lld -fno-strict-aliasing
LINKPATH   = 
LINKLIBS   = 
DEBARCH    = arm64
LSBREL     = $(shell lsb_release -r -s)
DISTDIR    = ../../dist/ubuntu-$(LSBREL)

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
LINKFLAGS := $(LINKFLAGS) -flto=thin -O3 -g -Wl,--gc-sections -Wl,--as-needed -fomit-frame-pointer
else
DEFINES   := $(DEFINES) -D_DEBUG
CXXFLAGS  := $(CXXFLAGS) -Og -g3
CFLAGS    := $(CFLAGS) -Og -g3
LINKFLAGS := $(LINKFLAGS) -g3
endif
