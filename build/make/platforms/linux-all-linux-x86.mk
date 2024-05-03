# Generic
EXTBIN     = 
EXTLIB     = .a
EXTDLL     = .so
EXTPDB     = .pdb
OBJDIR     = obj/linux-x86-$(MODE)
LIBDIR     = lib/linux-x86
BINDIR     = bin/linux-x86
TARGET     = i686-linux-gnu
DEFINES    = 
INCLUDES   = -I/usr/$(TARGET)/include
CXX        = clang++
CXXFLAGS   = -target $(TARGET) -fPIC -static -fno-strict-aliasing
CC         = clang
CFLAGS     = -target $(TARGET) -fPIC -static -fno-strict-aliasing
AR         = llvm-ar
ARFLAGS    = rcs
STRIP      = llvm-strip
STRIPFLAGS = --strip-all
LINK       = $(CXX)
LINKFLAGS  = -target $(TARGET) -fuse-ld=lld -static-libstdc++ -static-libgcc -fno-strict-aliasing
LINKPATH   =
LINKLIBS   = 
DEBARCH    = i386
LSBREL     = $(shell lsb_release -r -s)
DISTDIR    = ../../dist/ubuntu-$(LSBREL)

# CPU Flags
ifeq ($(TARGET_CPUREV),legacy)
CPUFLAGS   = -march=i686 -mtune=generic
endif
ifeq ($(TARGET_CPUREV),default)
CPUFLAGS   = -march=i686 -mtune=generic -msse -msse2 
endif
ifeq ($(TARGET_CPUREV),modern)
CPUFLAGS   = -march=i686 -mtune=generic -msse -msse2 -msse3 -mssse3 
endif

# Debug vs. Release
ifeq ($(MODE),release)
DEFINES   := $(DEFINES) -DNDEBUG
CXXFLAGS  := $(CXXFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections
CFLAGS    := $(CFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections
LINKFLAGS := $(LINKFLAGS) -flto=thin -O3 -g -Wl,--gc-sections
else
DEFINES   := $(DEFINES) -D_DEBUG
CXXFLAGS  := $(CXXFLAGS) -Og -g3
CFLAGS    := $(CFLAGS) -Og -g3
LINKFLAGS := $(LINKFLAGS) -g3
endif
