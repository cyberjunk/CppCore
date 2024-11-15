# Generic
EXTBIN     = 
EXTLIB     = .a
EXTDLL     = .dylib
EXTPDB     = .pdb
OBJDIR     = obj/ios-arm64-$(MODE)
LIBDIR     = lib/ios-arm64
BINDIR     = bin/ios-arm64
DISTDIR    = ../../dist/ios-13.0
TARGET     = arm64-apple-ios13.0
MINVER     = -miphoneos-version-min=13.0
DEFINES    = 
INCLUDES   = 
CXX        = clang++
CXXFLAGS   = $(MINVER) -target $(TARGET) -static \
             -isysroot $(shell xcrun --sdk iphoneos --show-sdk-path) \
             -fno-strict-aliasing
CC         = clang
CFLAGS     = $(MINVER) -target $(TARGET) -static \
             -isysroot $(shell xcrun --sdk iphoneos --show-sdk-path) \
             -fno-strict-aliasing
AR         = ar
ARFLAGS    = rcs
STRIP      = strip
STRIPFLAGS = -S
LINK       = $(CXX)
LINKFLAGS  = $(MINVER) -target $(TARGET) \
             -isysroot $(shell xcrun --sdk iphoneos --show-sdk-path) \
             -fno-strict-aliasing
LINKPATH   =
LINKLIBS   = 

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
LINKFLAGS := $(LINKFLAGS) -flto=thin -O3 -g -dead_strip -dead_strip_dylibs -fomit-frame-pointer
else
DEFINES   := $(DEFINES) -D_DEBUG
CXXFLAGS  := $(CXXFLAGS) -Og -g3
CFLAGS    := $(CFLAGS) -Og -g3
LINKFLAGS := $(LINKFLAGS) -g3
endif
