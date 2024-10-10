
include platforms/detect-host.mk

NAME       = CppCore.Test
OUT        = $(BINDIR)/$(NAME)$(SUFFIX)$(EXTBIN)
INCDIR     = ../../include
SRCDIR     = ../../src/$(NAME)
OBJDIR    := $(OBJDIR)/$(NAME)
DEFINES   := $(DEFINES)
INCLUDES  := $(INCLUDES) -I$(INCDIR)/
CXXFLAGS  := $(CXXFLAGS) \
             -std=c++17 \
             -Wno-deprecated-declarations \
             -Wno-c++20-extensions \
             -Wno-c++2a-extensions \
             -Wno-unknown-warning-option
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS)
LINKPATH  := $(LINKPATH)
LINKLIBS  := $(LINKLIBS)
OBJS       = Test.o
RESO       =

VERSIONFILE       = $(INCDIR)/CppCore/Version.h
VERSIONMACROMAJOR = CPPCORE_VERSION_MAJOR
VERSIONMACROMINOR = CPPCORE_VERSION_MINOR
VERSIONMACROPATCH = CPPCORE_VERSION_PATCH

################################################################################################
# CPU Specific

ifeq ($(TARGET_ARCH),x86)
CPUFLAGS  := $(CPUFLAGS)
endif

ifeq ($(TARGET_ARCH),x64)
CPUFLAGS  := $(CPUFLAGS)
endif

ifeq ($(TARGET_ARCH),arm)
CPUFLAGS  := $(CPUFLAGS)
endif

ifeq ($(TARGET_ARCH),arm64)
CPUFLAGS  := $(CPUFLAGS)
endif

################################################################################################
# OS Specific

ifeq ($(TARGET_OS),win)
OUTDIST   := $(DISTDIR)/$(NAME)-$(TARGET_ARCH)/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES) -D_CRT_SECURE_NO_WARNINGS -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
CXXFLAGS  := $(CXXFLAGS)
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS) \
             -Xlinker /SUBSYSTEM:CONSOLE",10.00" \
             -Xlinker /PDBALTPATH:$(NAME)$(SUFFIX)$(EXTPDB)
LINKLIBS  := $(LINKLIBS)
RESO      := $(RESO) Resources.res
endif

ifeq ($(TARGET_OS),osx)
OUTDIST   := $(DISTDIR)/$(NAME).app/Contents/MacOS/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES)
CXXFLAGS  := $(CXXFLAGS) -fdeclspec -ObjC++
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS) -Wl,-object_path_lto,$(OBJDIR)/lto.o
LINKLIBS  := $(LINKLIBS) -framework AppKit
RESO      := $(RESO)
endif

ifeq ($(TARGET_OS),linux)
OUTDIST   := $(DISTDIR)/$(NAME)-$(TARGET_ARCH)/usr/bin/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES)
CXXFLAGS  := $(CXXFLAGS)
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS)
LINKLIBS  := $(LINKLIBS) -lpthread
RESO      := $(RESO)
endif

ifeq ($(TARGET_OS),android)
OUTDIST   := $(DISTDIR)/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES)
CXXFLAGS  := $(CXXFLAGS)
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS)
LINKLIBS  := $(LINKLIBS) -ldl
RESO      := $(RESO)
endif

ifeq ($(TARGET_OS),ios)
OUTDIST   := $(DISTDIR)/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES)
CXXFLAGS  := $(CXXFLAGS) -fdeclspec -ObjC++
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS) -Wl,-object_path_lto,$(OBJDIR)/lto.o
LINKLIBS  := $(LINKLIBS) -framework Foundation
RESO      := $(RESO)
endif

ifeq ($(TARGET_OS),wasi)
OUTDIST   := $(DISTDIR)/$(NAME)$(EXTBIN)
DEFINES   := $(DEFINES) -DCPPCORE_NO_SOCKET -D_WASI_EMULATED_SIGNAL
CXXFLAGS  := $(CXXFLAGS)
CFLAGS    := $(CFLAGS)
LINKFLAGS := $(LINKFLAGS) -Wl,-z,stack-size=0x00100000
LINKLIBS  := $(LINKLIBS)
RESO      := $(RESO)
endif

################################################################################################

OBJS := $(patsubst %,$(OBJDIR)/%,$(OBJS))

$(OBJDIR)/%.o:
	@echo [CXX] $@
	$(CXX) $(CPUFLAGS) $(DEFINES) $(INCLUDES) $(CXXFLAGS) -c $(@:$(OBJDIR)%.o=$(SRCDIR)%.cpp) -o $@

################################################################################################

RESO := $(patsubst %,$(OBJDIR)/%,$(RESO))

$(OBJDIR)/%.res:
	@echo [RC]  $@
	$(RC) $(RCFLAGS) $(DEFINES) $(INCLUDES) -FO$@ $(@:$(OBJDIR)/%.res=$(SRCDIR)/%.rc)

################################################################################################

.DEFAULT_GOAL := build
.PHONY: clean

build: $(OBJS) $(RESO)
	@echo [LNK] $(OUT)
	$(LINK) $(LINKFLAGS) $(LINKPATH) $(OBJS) $(RESO) $(LINKLIBS) -o $(OUT)

run:
ifeq ($(TARGET_OS),android)
	echo [SDK] $(ANDROID_HOME)
#	$(SDKMANAGER) --list_installed
	$(SDKMANAGER) 'emulator'
	$(SDKMANAGER) $(ANDROID_SYSIMAGE)
#	$(SDKMANAGER) 'extras;intel;Hardware_Accelerated_Execution_Manager'
	$(AVDMANAGER) create avd --force \
	  --name $(NAME)_AVD \
	  --abi $(ANDROID_ABI) \
	  --device $(ANDROID_DEVICE) \
	  --package $(ANDROID_SYSIMAGE)
	$(AVDMANAGER) list avd
	$(ADB) start-server
ifeq ($(DETECTED_OS),win)
	start "" $(EMULATOR) -no-window -no-audio -no-snapshot -gpu guest -avd $(NAME)_AVD
else
	$(EMULATOR) -no-window -no-audio -no-snapshot -gpu guest -avd $(NAME)_AVD &
endif
	$(ADB) wait-for-any-device
	$(ADB) devices
	$(ADB) push $(OUT) /data/local/tmp
	$(ADB) shell chmod 777 /data/local/tmp/$(NAME)$(SUFFIX)$(EXTBIN)
	$(ADB) shell ./data/local/tmp/$(NAME)$(SUFFIX)$(EXTBIN)
	$(ADB) -s emulator-5554 emu kill
	$(ADB) wait-for-any-disconnect
	$(ADB) kill-server
	$(AVDMANAGER) delete avd --name $(NAME)_AVD
else ifeq ($(TARGET_OS),ios)
#	TODO: Run in emulator like on Android
else ifeq ($(TARGET_OS),wasi)
ifeq ($(WASMER_DIR),)
	wasmer $(OUT)
else
	$(WASMER_DIR)/bin/wasmer $(OUT)
endif
else
	$(OUT)
endif

clean:
	$(call deletefiles,$(OBJDIR),*.o)
	$(call deletefiles,$(OBJDIR),*.res)
	$(call deletefiles,$(BINDIR),$(NAME)$(SUFFIX)$(EXTBIN))
	$(call deletefiles,$(BINDIR),$(NAME)$(SUFFIX)$(EXTPDB))
