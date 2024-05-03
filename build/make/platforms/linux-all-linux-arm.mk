# Generic
EXTBIN     = 
EXTLIB     = .a
EXTDLL     = .so
EXTPDB     = .pdb
OBJDIR     = obj/linux-arm-$(MODE)
LIBDIR     = lib/linux-arm
BINDIR     = bin/linux-arm
TARGET     = arm-linux-gnueabihf
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
DEBARCH    = armhf
LSBREL     = $(shell lsb_release -r -s)
DISTDIR    = ../../dist/ubuntu-$(LSBREL)

# CPU Flags
ifeq ($(TARGET_CPUREV),legacy)
CPUFLAGS   = -march=armv7-a -mfloat-abi=hard -mfpu=neon-fp16
endif
ifeq ($(TARGET_CPUREV),default)
CPUFLAGS   = -march=armv7-a -mfloat-abi=hard -mfpu=neon-fp16
endif
ifeq ($(TARGET_CPUREV),modern)
CPUFLAGS   = -march=armv7-a -mfloat-abi=hard -mfpu=neon-fp16
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
