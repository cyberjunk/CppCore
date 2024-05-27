# Generic
EXTBIN     = 
EXTLIB     = .a
EXTDLL     = .dylib
EXTPDB     = .pdb
OBJDIR     = obj/ios-x64-$(MODE)
LIBDIR     = lib/ios-x64
BINDIR     = bin/ios-x64
DISTDIR    = ../../dist/ios-13.0
TARGET     = x86_64-apple-ios13.0-simulator
MINVER     = -miphoneos-version-min=13.0
CPUFLAGS   = -march=x86-64-v2 -mtune=generic -mpclmul
SDKROOT    = $(shell xcrun --sdk iphonesimulator --show-sdk-path)
DEFINES    = 
INCLUDES   = 
CXX        = clang++
CXXFLAGS   = $(MINVER) -target $(TARGET) -isysroot $(SDKROOT) -static -fno-strict-aliasing
CC         = clang
CFLAGS     = $(MINVER) -target $(TARGET) -isysroot $(SDKROOT) -static -fno-strict-aliasing
AR         = ar
ARFLAGS    = rcs
STRIP      = strip
STRIPFLAGS = -S
LINK       = $(CXX)
LINKFLAGS  = $(MINVER) -target $(TARGET) -isysroot $(SDKROOT) -fno-strict-aliasing
LINKPATH   =
LINKLIBS   = 

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
