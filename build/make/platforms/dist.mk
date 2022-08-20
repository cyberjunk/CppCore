# default publisher common name if not specified
ifeq ($(PUBLISHERCN),)
PUBLISHERCN = CppCore Developer
endif

# default full publisher if not specified
ifeq ($(PUBLISHER),)
PUBLISHER = CN=CppCore Developer
endif

# default key if not specified
ifeq ($(SIGN_PFX_FILE),)
SIGN_PFX_FILE = ../../CppCore.pfx
ifeq ($(SIGN_PFX_PASS),)
SIGN_PFX_PASS = CppCore
endif
endif

##############################################################################################################
# WINDOWS
##############################################################################################################

PUBLISHERID = $(shell powershell -command "& {\
  Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass;\
  . $(DISTDIR)/CppCore.ps1;\
  Get-PublisherHash '$(PUBLISHER)'; }")

ifeq ($(TARGET_OS),win)
dist-prep:
	chcp 1252
	echo [PUB] $(PUBLISHER)
	echo [PFX] $(SIGN_PFX_FILE)
	$(call rmdir,$(DISTDIR)/$(NAME))	
	$(call mkdir,$(DISTDIR)/$(NAME))
dist-%:
	echo [PKG] $(NAME)-$*.appx
	$(call rmdir,$(DISTDIR)/$(NAME)-$*)	
	$(call mkdir,$(DISTDIR)/$(NAME)-$*)
	$(call copyfiles,./bin/win-$*/$(NAME)$(EXTBIN),$(DISTDIR)/$(NAME)-$*/$(NAME)$(EXTBIN))
	$(call copyfiles,$(SRCDIR)/app.png,$(DISTDIR)/$(NAME)-$*/app.png)
	$(call replace,$(DISTDIR)/$(NAME).appxmanifest,{ARCH},$*,$(DISTDIR)/$(NAME)-$*/AppxManifest.xml)
	$(call replace,$(DISTDIR)/$(NAME)-$*/AppxManifest.xml,{PUBLISHER},$(PUBLISHER),$(DISTDIR)/$(NAME)-$*/AppxManifest.xml)
	$(call replace,$(DISTDIR)/$(NAME)-$*/AppxManifest.xml,{PUBLISHERID},$(PUBLISHERID),$(DISTDIR)/$(NAME)-$*/AppxManifest.xml)
ifeq ($(SIGN_PFX_FILE),)
	$(call makepkg,$(DISTDIR)/$(NAME)-$*,$(DISTDIR)/$(NAME)/$(NAME)-$*.appx)
else
ifeq ($(SIGN_PFX_PASS),)
	$(call sign,$(DISTDIR)/$(NAME)-$*/$(NAME)$(EXTBIN),$(SIGN_PFX_FILE))
	$(call makepkgs,$(DISTDIR)/$(NAME)-$*,$(DISTDIR)/$(NAME)/$(NAME)-$*.appx,$(SIGN_PFX_FILE))	
	$(call sign,$(DISTDIR)/$(NAME)/$(NAME)-$*.appx,$(SIGN_PFX_FILE))
else
	$(call signp,$(DISTDIR)/$(NAME)-$*/$(NAME)$(EXTBIN),$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
	$(call makepkgs,$(DISTDIR)/$(NAME)-$*,$(DISTDIR)/$(NAME)/$(NAME)-$*.appx,$(SIGN_PFX_FILE))	
	$(call signp,$(DISTDIR)/$(NAME)/$(NAME)-$*.appx,$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
endif
endif
dist: dist-prep dist-x64 dist-x86 dist-arm64
	echo [BDL] $(NAME).msixbundle
	$(call makebundle,$(DISTDIR)/$(NAME),$(DISTDIR)/$(NAME).msixbundle)
ifneq ($(SIGN_PFX_FILE),)
ifeq ($(SIGN_PFX_PASS),)
	$(call sign,$(DISTDIR)/$(NAME).msixbundle,$(SIGN_PFX_FILE))
else
	$(call signp,$(DISTDIR)/$(NAME).msixbundle,$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
endif
endif
endif

##############################################################################################################
# OSX
##############################################################################################################

ifeq ($(TARGET_OS),osx)
KEYCHAIN = sign-$(NAME).keychain-db
dist-%:
	@echo [DST] $(NAME)-$*
dist: dist-x64 dist-arm64
	@echo [MKD] $(NAME).app/Contents/MacOS
	@mkdir -p $(DISTDIR)/$(NAME).app/Contents/MacOS
	@echo [LIP] $(NAME)$(EXTBIN)
	@lipo -create -output $(OUTDIST) \
	  ./bin/osx-x64/$(NAME)$(EXTBIN) \
	  ./bin/osx-arm64/$(NAME)$(EXTBIN)
	@echo [KCH] $(KEYCHAIN)
#	@security delete-keychain $(KEYCHAIN)
	@security create-keychain -p "$(SIGN_PFX_PASS)" $(KEYCHAIN)
	@security set-keychain-settings -lut 21600 $(KEYCHAIN)
	@security unlock-keychain -p "$(SIGN_PFX_PASS)" $(KEYCHAIN)
	@echo [IMP] $(SIGN_PFX_FILE)
	@security import $(SIGN_PFX_FILE) -P $(SIGN_PFX_PASS) -k $(KEYCHAIN) -T /usr/bin/codesign
	@security set-key-partition-list -S apple-tool:,apple:,codesign: -s -k $(SIGN_PFX_PASS) $(KEYCHAIN)
	@security list-keychain -d user -s $(KEYCHAIN)
	@echo [SIG] $(NAME).app
	@codesign --sign "$(PUBLISHERCN)" --keychain $(KEYCHAIN) $(DISTDIR)/$(NAME).app
	@echo [PKG] $(NAME).pkg
	@productbuild --component $(DISTDIR)/$(NAME).app /Applications $(DISTDIR)/$(NAME).pkg
	@echo [SIG] $(NAME).pkg
#	@productsign --sign "$(PUBLISHERCN)" --keychain $(KEYCHAIN) $(DISTDIR)/$(NAME).pkg $(DISTDIR)/$(NAME)2.pkg
	@echo [DEL] $(KEYCHAIN)
	@security delete-keychain $(KEYCHAIN)
endif

##############################################################################################################
# LINUX
##############################################################################################################

ifeq ($(TARGET_OS),linux)
dist-%:
	echo [DST] $(NAME)-$*
dist: dist-x64 dist-x86 dist-arm64 dist-arm
	@echo [DEB] $(DEBFILE)
	mkdir -p $(DISTDIR)/$(NAME)/DEBIAN
	mkdir -p $(DISTDIR)/$(NAME)/usr/bin
	mkdir -p $(DISTDIR)/$(NAME)/usr/share/applications
	mkdir -p $(DISTDIR)/$(NAME)/usr/share/pixmaps
	sed 's/{ARCH}/${DEBARCH}/g' $(DISTDIR)/$(NAME).control > $(DISTDIR)/$(NAME)/DEBIAN/control
	cp $(SRCDIR)/app.png $(DISTDIR)/$(NAME)/usr/share/pixmaps/$(NAME).png
	cp $(DISTDIR)/$(NAME).desktop $(DISTDIR)/$(NAME)/usr/share/applications/$(NAME).desktop
	cp $(OUT) $(OUTDIST)
	dpkg-deb --build $(DISTDIR)/$(NAME) $(DISTDIR)/$(DEBFILE) > /dev/null 2>&1
endif

##############################################################################################################
# ANDROID
##############################################################################################################

ifeq ($(TARGET_OS),android)
dist-%:
	echo [DST] $(NAME)-$*
dist: dist-x64 dist-x86 dist-arm64 dist-arm
endif
