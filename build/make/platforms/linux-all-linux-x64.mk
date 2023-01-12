# Generic
EXTBIN     = 
EXTLIB     = .a
EXTDLL     = .so
EXTPDB     = .pdb
OBJDIR     = obj/linux-x64-$(MODE)
LIBDIR     = lib/linux-x64
BINDIR     = bin/linux-x64
TARGET     = x86_64-linux-gnu
DEFINES    = 
INCLUDES   = 
CXX        = clang++
CXXFLAGS   = -target $(TARGET) -fPIC -static
CC         = clang
CFLAGS     = -target $(TARGET) -fPIC -static
AR         = llvm-ar
ARFLAGS    = rcs
STRIP      = llvm-strip
STRIPFLAGS = --strip-all
LINK       = $(CXX)
LINKFLAGS  = -target $(TARGET) -fuse-ld=lld -static-libstdc++ -static-libgcc
LINKPATH   =
LINKLIBS   = 
DEBARCH    = amd64
LSBREL     = $(shell lsb_release -r -s)
DISTDIR    = ../../dist/ubuntu-$(LSBREL)

# CPU Flags
ifeq ($(TARGET_CPUREV),legacy)
CPUFLAGS   = -march=x86-64 -mtune=generic
endif
ifeq ($(TARGET_CPUREV),default)
ifeq ($(LSBREL),20.04)
CPUFLAGS   = -march=x86-64 -mtune=generic
else
CPUFLAGS   = -march=x86-64-v2 -mtune=generic
endif
endif
ifeq ($(TARGET_CPUREV),modern)
ifeq ($(LSBREL),20.04)
CPUFLAGS   = -march=x86-64 -mtune=generic
else
CPUFLAGS   = -march=x86-64-v3 -mtune=generic
endif
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
