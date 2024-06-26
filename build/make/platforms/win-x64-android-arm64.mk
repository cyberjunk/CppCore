# Requires NDK 22b or later

# Replace any backlash in homes
ANDROID_NDK_HOME := $(subst \,/,$(ANDROID_NDK_HOME))
ANDROID_HOME     := $(subst \,/,$(ANDROID_HOME))

# Android Specific
ANDROID_API         = 23
ANDROID_TOOLCHAIN   = $(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/windows-x86_64
ANDROID_SYSIMAGE    = 'system-images;android-$(ANDROID_API);google_apis;arm64-v8a'
ANDROID_ABI         = 'google_apis/arm64-v8a'
ANDROID_DEVICE      = 'Nexus 5'

# Generic
EXTBIN     =
EXTLIB     = .a
EXTDLL     = .so
EXTPDB     = .pdb
OBJDIR     = obj/android-arm64-$(MODE)
LIBDIR     = lib/android-arm64
BINDIR     = bin/android-arm64
DISTDIR    = ../../dist/android-$(ANDROID_API)
TARGET     = aarch64-linux-android
DEFINES    = -DANDROID -D__ANDROID_API__=$(ANDROID_API) -DANDROID_ARM_NEON=ON 
INCLUDES   = -I$(ANDROID_NDK_HOME)/sources/android/cpufeatures
CXX        = $(ANDROID_TOOLCHAIN)/bin/$(TARGET)$(ANDROID_API)-clang++.cmd
CXXFLAGS   = -static -fPIC \
             -fno-strict-aliasing \
             -target $(TARGET) \
             -isystem $(ANDROID_TOOLCHAIN)/sysroot/usr/include/$(TARGET)
CC         = $(ANDROID_TOOLCHAIN)/bin/$(TARGET)$(ANDROID_API)-clang.cmd
CFLAGS     = -static -fPIC \
             -fno-strict-aliasing \
             -target $(TARGET) \
             -isystem $(ANDROID_TOOLCHAIN)/sysroot/usr/include/$(TARGET)
AR         = $(ANDROID_TOOLCHAIN)/bin/llvm-ar.exe
ARFLAGS    = rcs
STRIP      = $(ANDROID_TOOLCHAIN)/bin/llvm-strip.exe
STRIPFLAGS = --strip-all
LINK       = $(CXX)
LINKFLAGS  = -target $(TARGET) -fPIC -fuse-ld=lld -static-libstdc++ -static-libgcc -nostartfiles -fno-strict-aliasing \
             $(ANDROID_TOOLCHAIN)/sysroot/usr/lib/$(TARGET)/$(ANDROID_API)/crtbegin_static.o \
             $(ANDROID_TOOLCHAIN)/sysroot/usr/lib/$(TARGET)/$(ANDROID_API)/crtend_android.o
LINKPATH   = -L$(ANDROID_TOOLCHAIN)/sysroot/usr/lib/$(TARGET)/$(ANDROID_API) \
             -L$(ANDROID_TOOLCHAIN)/sysroot/usr/lib/$(TARGET)
LINKLIBS   = -landroid

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

# SDK Tools
AVDMANAGER = $(ANDROID_HOME)/cmdline-tools/latest/bin/avdmanager.bat
SDKMANAGER = $(ANDROID_HOME)/cmdline-tools/latest/bin/sdkmanager.bat
ADB        = $(ANDROID_HOME)/platform-tools/adb.exe
EMULATOR   = $(ANDROID_HOME)/emulator/emulator.exe

# Debug vs. Release
ifeq ($(MODE),release)
DEFINES   := $(DEFINES) -DNDEBUG
CXXFLAGS  := $(CXXFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections -fomit-frame-pointer
CFLAGS    := $(CFLAGS) -flto=thin -O3 -g -ffunction-sections -fdata-sections -fomit-frame-pointer
LINKFLAGS := $(LINKFLAGS) -flto=thin -O3 -g -Wl,--gc-sections -Wl,--as-needed -fomit-frame-pointer
else
DEFINES   := $(DEFINES) -D_DEBUG
CXXFLAGS  := $(CXXFLAGS) -Og -g3
CFLAGS    := $(CFLAGS) -Og -g3
LINKFLAGS := $(LINKFLAGS) -g3
endif
