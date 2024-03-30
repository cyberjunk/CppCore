
include build/make/platforms/detect-host.mk

##################################################################################
# ALL PLATFORMS
##################################################################################

CppCore.Example.Server:	
	@echo [BLD] CppCore.Example.Server
	+@make -s -C ./build/make/ -f CppCore.Example.Server.mk

CppCore.Example.Server-clean:
	@echo [CLN] CppCore.Example.Server
	+@make -s -C ./build/make/ -f CppCore.Example.Server.mk clean

CppCore.Example.Server-dist:
	@echo [DST] CppCore.Example.Server
	+@make -s -C ./build/make/ -f CppCore.Example.Server.mk dist

CppCore.Example.Client:
	@echo [BLD] CppCore.Example.Client
	+@make -s -C ./build/make/ -f CppCore.Example.Client.mk

CppCore.Example.Client-clean:
	@echo [CLN] CppCore.Example.Client
	+@make -s -C ./build/make/ -f CppCore.Example.Client.mk clean

CppCore.Example.Client-dist:
	@echo [DST] CppCore.Example.Client
	+@make -s -C ./build/make/ -f CppCore.Example.Client.mk dist

CppCore.Example.UI:
	@echo [BLD] CppCore.Example.UI
	+@make -s -C ./build/make/ -f CppCore.Example.UI.mk

CppCore.Example.UI-clean:
	@echo [CLN] CppCore.Example.UI
	+@make -s -C ./build/make/ -f CppCore.Example.UI.mk clean

CppCore.Example.UI-dist:
	@echo [DST] CppCore.Example.UI
	+@make -s -C ./build/make/ -f CppCore.Example.UI.mk dist

CppCore.Test:
	@echo [BLD] CppCore.Test
	+@make -s -C ./build/make/ -f CppCore.Test.mk

CppCore.Test-clean:
	@echo [CLN] CppCore.Test
	+@make -s -C ./build/make/ -f CppCore.Test.mk clean

CppCore.Test-run:
	@echo [RUN] CppCore.Test
	+@make -s -C ./build/make/ -f CppCore.Test.mk run

CppCore.Interface.C:
	@echo [BLD] CppCore.Interface.C
	+@make -s -C ./build/make/ -f CppCore.Interface.C.mk

CppCore.Interface.C-clean:
	@echo [CLN] CppCore.Interface.C
	+@make -s -C ./build/make/ -f CppCore.Interface.C.mk clean

CppCore.Interface.C-dist:
	@echo [DST] CppCore.Interface.C
	+@make -s -C ./build/make/ -f CppCore.Interface.C.mk lib-dist

CppCore.Interface.Python:
	@echo [BLD] CppCore.Interface.Python
	+@make -s -C ./build/make/ -f CppCore.Interface.Python.mk

CppCore.Debug:
	@echo [BLD] CppCore.Debug
	+@make -s -C ./build/make/ -f CppCore.Debug.mk

CppCore.Debug-clean:
	@echo [CLN] CppCore.Debug
	+@make -s -C ./build/make/ -f CppCore.Debug.mk clean

##################################################################################

all: \
	CppCore.Example.Server \
	CppCore.Example.Client \
	CppCore.Example.UI \
	CppCore.Test \
	CppCore.Interface.C \
	CppCore.Debug

clean: \
	CppCore.Example.Server-clean \
	CppCore.Example.Client-clean \
	CppCore.Example.UI-clean \
	CppCore.Test-clean \
	CppCore.Interface.C-clean \
	CppCore.Debug-clean

test: \
	CppCore.Test-run

dist: \
	CppCore.Example.Server-dist \
	CppCore.Example.Client-dist \
	CppCore.Example.UI-dist \
	CppCore.Interface.C-dist

##################################################################################

.PHONY: all clean
.DEFAULT_GOAL := all
