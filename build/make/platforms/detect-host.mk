########################################################
# Detect Host OS, CPU and CORES
########################################################

# Windows (no uname)
ifeq ($(OS),Windows_NT)
	DETECTED_OS := win
	DETECTED_EXTBIN := .exe

	# Detect platform arch
	ifneq ($(PROCESSOR_ARCHITEW6432),)
		DETECTED_ARCH := $(PROCESSOR_ARCHITEW6432)
	else
		DETECTED_ARCH := $(PROCESSOR_ARCHITECTURE)
	endif
	
	# Map platform arch to our name
	ifeq ($(DETECTED_ARCH),AMD64)
		DETECTED_ARCH := x64
	else ifeq ($(DETECTED_ARCH),x86)
		DETECTED_ARCH := x86
	else ifeq ($(DETECTED_ARCH),ARM64)
		DETECTED_ARCH := arm64
	else ifeq ($(DETECTED_ARCH),ARM)
		DETECTED_ARCH := arm
	else
		echo ERROR - Unrecognized Host CPU arch
	endif
	
	# Detect # of cores
	DETECTED_CORES := $(NUMBER_OF_PROCESSORS)

# Linux/OSX (anything with uname)
else
	DETECTED_OS := $(shell uname)
	DETECTED_ARCH := $(shell uname -m)
	DETECTED_EXTBIN :=
		
	# Map os name to our linux/osx
	ifeq ($(DETECTED_OS),Linux)
		DETECTED_OS := linux
	else ifeq ($(DETECTED_OS),Darwin)
		DETECTED_OS := osx
	endif
	
	# Map platform arch to our name
	ifeq ($(DETECTED_ARCH),x86_64)
		DETECTED_ARCH := x64
	else ifeq ($(DETECTED_ARCH),i386)
		DETECTED_ARCH := x86
	else ifeq ($(DETECTED_ARCH),x86)
		DETECTED_ARCH := x86
	else ifeq ($(DETECTED_ARCH),aarch64)
		DETECTED_ARCH := arm64
	else ifeq ($(DETECTED_ARCH),arm64)
		DETECTED_ARCH := arm64
	else ifeq ($(DETECTED_ARCH),arm)
		DETECTED_ARCH := arm
	else ifeq ($(DETECTED_ARCH),armv7a)
		DETECTED_ARCH := arm
	else
		echo ERROR - Unrecognized Host CPU arch
	endif
	
	# Detect # of cores
	ifeq ($(DETECTED_OS),linux)
		DETECTED_CORES := $(shell nproc)
	endif
	ifeq ($(DETECTED_OS),osx)
		DETECTED_CORES := $(shell sysctl -n hw.ncpu)
	endif
endif

# Use Detected Platform as Target by default
ifeq ($(TARGET_OS),)
TARGET_OS = $(DETECTED_OS)
endif
ifeq ($(TARGET_ARCH),)
TARGET_ARCH = $(DETECTED_ARCH)
endif

# CPU Revision (legacy|default|modern)
ifeq ($(TARGET_CPUREV),)
TARGET_CPUREV = default
endif

# Debug by default
ifeq ($(MODE),)
MODE = debug
endif

# Debug vs. Release
ifeq ($(MODE),debug)
SUFFIX = _d
else
SUFFIX =
endif

# Folder of platform .mk files
PLATDIR = $(dir $(lastword $(MAKEFILE_LIST)))

# Include shared file for all host and target arch
-include $(PLATDIR)/$(DETECTED_OS)-all.mk

# Include shared file for all target arch
-include $(PLATDIR)/all-all-$(TARGET_OS)-$(TARGET_ARCH).mk

# Include shared file for all host arch
-include $(PLATDIR)/$(DETECTED_OS)-all-$(TARGET_OS)-$(TARGET_ARCH).mk

# Include file for this target arch
-include $(PLATDIR)/$(DETECTED_OS)-$(DETECTED_ARCH)-$(TARGET_OS)-$(TARGET_ARCH).mk

# JAVA JDK
ifeq ($(DETECTED_OS),osx)
JAVA_HOME := $(shell /usr/libexec/java_home)
endif

JAR   = "$(JAVA_HOME)/bin/jar$(DETECTED_EXTBIN)"
JAVAC = "$(JAVA_HOME)/bin/javac$(DETECTED_EXTBIN)"
