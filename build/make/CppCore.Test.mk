
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
	echo $(ANDROID_HOME)
	
#	$(SDKMANAGER) --list_installed
	$(SDKMANAGER) 'emulator'
	$(SDKMANAGER) $(ANDROID_SYSIMAGE)
#	$(SDKMANAGER) --list_installed
	
#	echo DONE
	$(AVDMANAGER) create avd --force \
	  --name $(NAME)_AVD \
	  --abi $(ANDROID_ABI) \
	  --device pixel_5 \
	  --package $(ANDROID_SYSIMAGE)
	
#	echo AVD
	$(AVDMANAGER) list avd
#	echo TARGET
#	$(AVDMANAGER) list target
#	echo DEVICE
#	$(AVDMANAGER) list device
#	$(AVDMANAGER) create avd --force --name $(NAME)_AVD --abi $(ANDROID_ABI) --device pixel_5 --package $(ANDROID_SYSIMAGE)
#	$(AVDMANAGER) create avd --force --name testX64 --abi google_apis/x86_64 --package 'system-images;android-21;google_apis;x86_64'
#	echo AVD
#	$(AVDMANAGER) list avd
ifeq ($(DETECTED_OS),osx)
	$(ADB) start-server
	$(EMULATOR) -no-window -avd $(NAME)_AVD
#	$(EMULATOR) -no-window -avd $(NAME)_AVD &
#	sleep 20
	$(ADB) wait-for-any-device
	$(ADB) devices
	$(ADB) shell ls
endif
ifeq ($(DETECTED_OS),win)
	$(ADB) start-server
	$(EMULATOR) -no-window -avd $(NAME)_AVD
#	start "" $(EMULATOR) -no-window -avd $(NAME)_AVD
#	ping -n 20 127.0.0.1 >NUL
	$(ADB) wait-for-any-device
	$(ADB) devices
	$(ADB) shell ls
endif
#	start "" $(EMULATOR) -avd testAVD
#	timeout 30
#	$(ADB) push $(OUT) /data/local/tmp	
#	$(ADB) shell chmod +x /data/local/tmp/$(NAME)$(SUFFIX)$(EXTBIN)
#	$(ADB) shell ./data/local/tmp/$(NAME)$(SUFFIX)$(EXTBIN)
#	$(SDKMANAGER) --list_installed
#	$(ADB) -shell -x ls
#	$(AVDMANAGER) delete avd --name testAVD
endif

clean:
	$(call deletefiles,$(OBJDIR),*.o)
	$(call deletefiles,$(OBJDIR),*.res)
	$(call deletefiles,$(BINDIR),$(NAME)$(SUFFIX)$(EXTBIN))
	$(call deletefiles,$(BINDIR),$(NAME)$(SUFFIX)$(EXTPDB))
