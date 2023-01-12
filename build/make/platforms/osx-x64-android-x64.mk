# Requires NDK 22b or later

# Android Specific
ANDROID_API         = 23
ANDROID_TOOLCHAIN   = $(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64
ANDROID_SYSIMAGE    = 'system-images;android-$(ANDROID_API);google_apis;x86_64'
ANDROID_ABI         = 'google_apis/x86_64'
ANDROID_DEVICE      = 'Nexus 5'

# Generic
EXTBIN     =
EXTLIB     = .a
EXTDLL     = .so
EXTPDB     = .pdb
OBJDIR     = obj/android-x64-$(MODE)
LIBDIR     = lib/android-x64
BINDIR     = bin/android-x64
DISTDIR    = ../../dist/android-$(ANDROID_API)
TARGET     = x86_64-linux-android
DEFINES    = -DANDROID -D__ANDROID_API__=$(ANDROID_API)
INCLUDES   = -I$(ANDROID_NDK_HOME)/sources/android/cpufeatures
CXX        = $(ANDROID_TOOLCHAIN)/bin/$(TARGET)$(ANDROID_API)-clang++
CXXFLAGS   = -static -fPIC \
             -target $(TARGET) \
             -isystem $(ANDROID_TOOLCHAIN)/sysroot/usr/include/$(TARGET)
CC         = $(ANDROID_TOOLCHAIN)/bin/$(TARGET)$(ANDROID_API)-clang
CFLAGS     = -static -fPIC \
             -target $(TARGET) \
             -isystem $(ANDROID_TOOLCHAIN)/sysroot/usr/include/$(TARGET)
AR         = $(ANDROID_TOOLCHAIN)/bin/llvm-ar
ARFLAGS    = rcs
STRIP      = $(ANDROID_TOOLCHAIN)/bin/llvm-strip
STRIPFLAGS = --strip-all
LINK       = $(CXX)
LINKFLAGS  = -target $(TARGET) -fPIC -fuse-ld=lld -static-libstdc++ -static-libgcc -nostartfiles \
             $(ANDROID_TOOLCHAIN)/sysroot/usr/lib/$(TARGET)/$(ANDROID_API)/crtbegin_static.o \
             $(ANDROID_TOOLCHAIN)/sysroot/usr/lib/$(TARGET)/$(ANDROID_API)/crtend_android.o
LINKPATH   = -L$(ANDROID_TOOLCHAIN)/sysroot/usr/lib/$(TARGET)/$(ANDROID_API) \
             -L$(ANDROID_TOOLCHAIN)/sysroot/usr/lib/$(TARGET)
LINKLIBS   = -landroid

# CPU Flags
ifeq ($(TARGET_CPUREV),legacy)
CPUFLAGS   = -march=x86-64 -mtune=generic
endif
ifeq ($(TARGET_CPUREV),default)
CPUFLAGS   = -march=x86-64-v2 -mtune=generic
endif
ifeq ($(TARGET_CPUREV),modern)
CPUFLAGS   = -march=x86-64-v3 -mtune=generic
endif

# SDK Tools
AVDMANAGER = $(ANDROID_HOME)/cmdline-tools/latest/bin/avdmanager
SDKMANAGER = $(ANDROID_HOME)/cmdline-tools/latest/bin/sdkmanager
ADB        = $(ANDROID_HOME)/platform-tools/adb
EMULATOR   = $(ANDROID_HOME)/emulator/emulator

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
