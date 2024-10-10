# 
ifndef WASI_SDK_PATH
$(error WASI_SDK_PATH is not set)
endif

# Generic
EXTBIN     = .wasm
EXTLIB     = .a
EXTDLL     = .wasm
EXTPDB     = .pdb
OBJDIR     = obj/wasi-wasm32-$(MODE)
LIBDIR     = lib/wasi-wasm32
BINDIR     = bin/wasi-wasm32
DISTDIR    = ../../dist/wasi
TARGET     = wasm32-wasi-threads -pthread
DEFINES    = 
INCLUDES   = 
CXX        = $(WASI_SDK_PATH)/bin/clang++
CXXFLAGS   = -static -fPIC \
             -fno-strict-aliasing \
             -fno-exceptions \
             -target $(TARGET)
CC         = $(WASI_SDK_PATH)/bin/clang
CFLAGS     = -static -fPIC \
             -fno-strict-aliasing \
             -fno-exceptions \
             -target $(TARGET)
AR         = $(WASI_SDK_PATH)/bin/llvm-ar
ARFLAGS    = rcs
STRIP      = $(WASI_SDK_PATH)/bin/llvm-strip
STRIPFLAGS = --strip-all
LINK       = $(CXX)
LINKFLAGS  = -target $(TARGET) -fPIC -fuse-ld=lld -fno-strict-aliasing
LINKPATH   = -L$(WASI_SDK_PATH)/share/wasi-sysroot/lib/wasm32-wasi-threads
LINKLIBS   = 

# Debug vs. Release
ifeq ($(MODE),release)
DEFINES   := $(DEFINES) -DNDEBUG
CXXFLAGS  := $(CXXFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections -fomit-frame-pointer
CFLAGS    := $(CFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections -fomit-frame-pointer
LINKFLAGS := $(LINKFLAGS) -flto=thin -O3 -g -Wl,--gc-sections -fomit-frame-pointer
else
DEFINES   := $(DEFINES) -D_DEBUG
CXXFLAGS  := $(CXXFLAGS) -Og -g3
CFLAGS    := $(CFLAGS) -Og -g3
LINKFLAGS := $(LINKFLAGS) -g3
endif
