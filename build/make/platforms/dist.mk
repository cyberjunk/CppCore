
# default publisher common name if not specified
ifeq ($(PUBLISHERCN),)
PUBLISHERCN = CppCore Developer
endif

# default full publisher if not specified
ifeq ($(PUBLISHER),)
PUBLISHER = CN=CppCore Developer
endif

# set this from ENV to enable PKG signing on OSX
#PRODUCTSIGNCN =

# set this from ENV to enable notarization of signed PKG on OSX
#APPLE_ID           = someone@somewhere.com
#APPLE_TEAM_ID      = see https://developer.apple.com/account/#!/membership/
#APPLE_APPSPEC_PASS = app-specific-password-for someone@somwhere.com
#APPLE_DIST_STORE   = true if building packages for macOS store
#APPLE_UPLOAD_STORE = true if package should be uploaded to macOS store

# default key if not specified
ifeq ($(SIGN_PFX_FILE),)
SIGN_PFX_FILE = ../../certs/DevCert.pfx
ifeq ($(SIGN_PFX_PASS),)
SIGN_PFX_PASS = CppCore
endif
endif

# extract version
include platforms/extract-version.mk

##############################################################################################################
# WINDOWS
##############################################################################################################

ifeq ($(TARGET_OS),win)
SCRIPTSFILE=Scripts.ps1
PUBLISHERID = $(shell powershell -command "& {\
  Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass;\
  . $(DISTDIR)/$(SCRIPTSFILE);\
  Get-PublisherHash '$(PUBLISHER)'; }")
ZIPPER   = $(DISTDIR)/7za.exe a -y -aoa -mx6 -bd -bb0
dist-prep:
	echo [VER] $(VERSION4)
	echo [CPG] CodePage 1252
	chcp 1252
	echo [PUB] $(PUBLISHER)
	echo [PFX] $(SIGN_PFX_FILE)
	echo [RMD] $(DISTDIR)/$(NAME)
	-$(call rmdir,$(DISTDIR)/$(NAME))
	-$(call deletefiles,$(DISTDIR),$(NAME)*.zip)
	-$(call deletefiles,$(DISTDIR),$(NAME)*.appx)
	-$(call deletefiles,$(DISTDIR),$(NAME)*.appxbundle)
	-$(call deletefiles,$(DISTDIR),$(NAME)*.appxupload)
	echo [MKD] $(DISTDIR)/$(NAME)
	-$(call mkdir,$(DISTDIR)/$(NAME))
	-$(call mkdir,$(DISTDIR)/$(NAME)/resources)
	-$(call mkdir,$(DISTDIR)/$(NAME)/upload)
	-$(call mkdir,$(DISTDIR)/$(NAME)/x64)
	-$(call mkdir,$(DISTDIR)/$(NAME)/x86)
	-$(call mkdir,$(DISTDIR)/$(NAME)/arm64)
	$(call copyfiles,$(DISTDIR)/$(NAME).appxmanifest,$(DISTDIR)/$(NAME)/AppxManifest.xml)
	$(call replace,$(DISTDIR)/$(NAME)/AppxManifest.xml,{PUBLISHER},$(PUBLISHER),$(DISTDIR)/$(NAME)/AppxManifest.xml)
	$(call replace,$(DISTDIR)/$(NAME)/AppxManifest.xml,{PUBLISHERID},$(PUBLISHERID),$(DISTDIR)/$(NAME)/AppxManifest.xml)
	$(call replace,$(DISTDIR)/$(NAME)/AppxManifest.xml,{VERSION},$(VERSION4),$(DISTDIR)/$(NAME)/AppxManifest.xml)
	$(call replace,$(DISTDIR)/$(NAME)/AppxManifest.xml,{DISPLAYNAME},$(APPNAME),$(DISTDIR)/$(NAME)/AppxManifest.xml)
	$(call copyfiles,$(DISTDIR)/$(NAME).layout,$(DISTDIR)/$(NAME)/Layout.xml)
	$(call replace,$(DISTDIR)/$(NAME)/Layout.xml,{VERSION},$(VERSION3),$(DISTDIR)/$(NAME)/Layout.xml)
	echo [CPY] Icons
	$(call copyfiles,$(SRCDIR)/Resources/app-44x44.png,$(DISTDIR)/$(NAME)/resources/app-44x44.png)
	$(call copyfiles,$(SRCDIR)/Resources/app-50x50.png,$(DISTDIR)/$(NAME)/resources/app-50x50.png)
	$(call copyfiles,$(SRCDIR)/Resources/app-150x150.png,$(DISTDIR)/$(NAME)/resources/app-150x150.png)
dist-%: dist-prep
	echo [MKD] $(DISTDIR)/$(NAME)/$*
	$(call rmdir,$(DISTDIR)/$(NAME)/$*)
	$(call mkdir,$(DISTDIR)/$(NAME)/$*)
	$(call copyfiles,./bin/win-$*/$(NAME)$(EXTBIN),$(DISTDIR)/$(NAME)/$*/$(NAME)$(EXTBIN))
	$(call copyfiles,./bin/win-$*/$(NAME)$(EXTPDB),$(DISTDIR)/$(NAME)/$*/$(NAME)$(EXTPDB))
	echo [STR] $(DISTDIR)/$(NAME)/$*/$(NAME)$(EXTBIN)
	$(STRIP) $(STRIPFLAGS) $(DISTDIR)/$(NAME)/$*/$(NAME)$(EXTBIN)
	echo [SIG] $(DISTDIR)/$(NAME)/$*/$(NAME)$(EXTBIN)
ifeq ($(SIGN_PFX_PASS),)
	$(call sign,$(DISTDIR)/$(NAME)/$*/$(NAME)$(EXTBIN),$(SIGN_PFX_FILE))
else
	$(call signp,$(DISTDIR)/$(NAME)/$*/$(NAME)$(EXTBIN),$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
endif
	echo [SYM] $(DISTDIR)/$(NAME)/upload/$(NAME)-$*.appxsym
	$(ZIPPER) $(DISTDIR)/$(NAME)/upload/$(NAME)-$*.appxsym.zip $(DISTDIR)/$(NAME)/$*/$(NAME)$(EXTPDB)	
	$(call move,$(DISTDIR)/$(NAME)/upload/$(NAME)-$*.appxsym.zip,$(DISTDIR)/$(NAME)/upload/$(NAME)-$*.appxsym)
dist: dist-prep dist-x64 dist-x86 dist-arm64
	echo [BDL] $(DISTDIR)/$(NAME)-$(VERSION3)-win-10.appxbundle
	$(call makepkg,$(DISTDIR)/$(NAME)/Layout.xml,$(DISTDIR))
	echo [SIG] $(DISTDIR)/$(NAME)-$(VERSION3)-win-10.appxbundle
ifeq ($(SIGN_PFX_PASS),)
	$(call sign,$(DISTDIR)/$(NAME).appxbundle,$(SIGN_PFX_FILE))
	$(call sign,$(DISTDIR)/$(NAME)-x64.appx,$(SIGN_PFX_FILE))
	$(call sign,$(DISTDIR)/$(NAME)-x86.appx,$(SIGN_PFX_FILE))
	$(call sign,$(DISTDIR)/$(NAME)-arm64.appx,$(SIGN_PFX_FILE))
	$(call sign,$(DISTDIR)/$(NAME)-res.appx,$(SIGN_PFX_FILE))
else
	$(call signp,$(DISTDIR)/$(NAME).appxbundle,$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
	$(call signp,$(DISTDIR)/$(NAME)-x64.appx,$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
	$(call signp,$(DISTDIR)/$(NAME)-x86.appx,$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
	$(call signp,$(DISTDIR)/$(NAME)-arm64.appx,$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
	$(call signp,$(DISTDIR)/$(NAME)-res.appx,$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
endif
	echo [APU] $(DISTDIR)/$(NAME)-$(VERSION3)-win-10.appxupload
	$(call copyfiles,$(DISTDIR)/$(NAME).appxbundle,$(DISTDIR)/$(NAME)/upload/$(NAME).appxbundle)
	$(ZIPPER) $(DISTDIR)/$(NAME).appxupload.zip $(DISTDIR)/$(NAME)/upload/*
	$(call move,$(DISTDIR)/$(NAME).appxupload.zip,$(DISTDIR)/$(NAME)-$(VERSION3)-win-10.appxupload)	
	$(call move,$(DISTDIR)/$(NAME).appxbundle,$(DISTDIR)/$(NAME)-$(VERSION3)-win-10.appxbundle)
lib-dist-prep:
	echo [VER] $(VERSION4)
	echo [CPG] CodePage 1252
	chcp 1252
	echo [PUB] $(PUBLISHER)
	echo [PFX] $(SIGN_PFX_FILE)
	echo [RMD] $(DISTDIR)/$(NAME)
	-$(call rmdir,$(DISTDIR)/$(NAME))
	-$(call deletefiles,$(DISTDIR),$(NAME)*.zip)
	echo [MKD] $(DISTDIR)/$(NAME)
	$(call mkdir,$(DISTDIR)/$(NAME))
	$(call copyfiles,$(INCDIR)/$(NAME)/*.h,$(DISTDIR)/$(NAME)/)
lib-dist-%: lib-dist-prep
	echo [MKD] $(DISTDIR)/$(NAME)/$*
	$(call mkdir,$(DISTDIR)/$(NAME)/$*)
	$(call copyfiles,./lib/win-$*/$(LIBNAME)$(EXTDLL),$(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTDLL))
	$(call copyfiles,./lib/win-$*/$(LIBNAME)$(EXTLIB),$(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTLIB))
	$(call copyfiles,./lib/win-$*/$(LIBNAME)$(EXTPDB),$(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTPDB))
	echo [STR] $(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTDLL)
	$(STRIP) $(STRIPFLAGS) $(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTDLL)
	echo [SIG] $(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTDLL)
ifeq ($(SIGN_PFX_PASS),)
	$(call sign,$(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTDLL),$(SIGN_PFX_FILE))
else
	$(call signp,$(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTDLL),$(SIGN_PFX_FILE),$(SIGN_PFX_PASS))
endif
lib-dist: lib-dist-prep lib-dist-x64 lib-dist-x86 lib-dist-arm64
	echo [ZIP] $(DISTDIR)/$(NAME)-$(VERSION3)-win-10.zip
	$(ZIPPER) $(DISTDIR)/$(NAME)-$(VERSION3)-win-10.zip $(DISTDIR)/$(NAME)/*
endif

##############################################################################################################
# OSX
##############################################################################################################

ifeq ($(TARGET_OS),osx)
KEYCHAIN     = sign-$(NAME).keychain-db
DISTDIRAPP   = "$(DISTDIR)/$(NAME)/$(APPNAME).app"
OSXVER       = $(shell sw_vers -productVersion)
OSXBUILDV    = $(shell sw_vers -buildVersion)
OSXSDKVER    = $(shell xcrun --show-sdk-version)
OSXSDKBUILDV = $(shell xcrun --show-sdk-build-version)
XCODEVER     = $(shell xcodebuild -version | grep -E -m1 'Xcode' | sed 's/Xcode //g')
XCODEBUILDV  = $(shell xcodebuild -version | grep -E -m1 'Build version' | sed 's/Build version //g')
PKGSIGNED    = $(NAME)-$(VERSION3)-macOS-10.15-universal.pkg
PKGUNSIGNED  = $(NAME)-$(VERSION3)-macOS-10.15-universal-unsigned.pkg
TARNAME      = $(NAME)-$(VERSION3)-macOS-10.15-universal.tar.gz
dist-prep:
	@echo [VER] $(VERSION3)
	@echo [OSX] $(OSXVER) - ${OSXBUILDV}
	@echo [SDK] $(OSXSDKVER) - ${OSXSDKBUILDV}
	@echo [XCO] $(XCODEVER) - ${XCODEBUILDV}
	@echo [KCH] $(KEYCHAIN)
	@-rm -rf $(DISTDIR)/$(NAME)
	@-rm -rf $(DISTDIR)/$(NAME).dSYM
	@-rm -rf $(DISTDIR)/$(NAME).symbols
	@-rm -rf $(DISTDIR)/$(NAME)*.pkg
	@-security delete-keychain $(KEYCHAIN)
	@security create-keychain -p "$(SIGN_PFX_PASS)" $(KEYCHAIN)
	@security set-keychain-settings -lut 21600 $(KEYCHAIN)
	@security unlock-keychain -p "$(SIGN_PFX_PASS)" $(KEYCHAIN)
	@echo [IMP] $(SIGN_PFX_FILE)
	@security import $(SIGN_PFX_FILE) \
		-P $(SIGN_PFX_PASS) \
		-f pkcs12 \
		-k $(KEYCHAIN) \
		-T /usr/bin/codesign \
		-T /usr/bin/productsign
	@echo [KPL] $(KEYCHAIN)
	@security set-key-partition-list \
		-S apple-tool:,apple:,codesign: \
		-s -k $(SIGN_PFX_PASS) $(KEYCHAIN)
	@echo [LST] $(KEYCHAIN)
	@security list-keychain -d user -s $(KEYCHAIN)
	@echo [INF] $(KEYCHAIN)
	@security show-keychain-info $(KEYCHAIN)
dist-%: dist-prep
	@echo [DST] $(NAME)-$*
dist: dist-prep dist-x64 dist-arm64
	@echo [MKD] $(APPNAME).app/Contents/MacOS
	@mkdir -p $(DISTDIRAPP)/Contents/MacOS
	@echo [LIP] $(NAME)$(EXTBIN)
	@lipo -create -output $(DISTDIRAPP)/Contents/MacOS/$(NAME) \
	  ./bin/osx-x64/$(NAME)$(EXTBIN) \
	  ./bin/osx-arm64/$(NAME)$(EXTBIN)
	@echo [SYM] $(NAME).dSYM
	@dsymutil \
	  -out $(DISTDIR)/$(NAME).dSYM \
	  $(DISTDIRAPP)/Contents/MacOS/$(NAME)
	@echo [INF] $(NAME).dSYM
	@dwarfdump --uuid $(DISTDIR)/$(NAME).dSYM
#	@echo [VFY] $(NAME).dSYM
#	@dwarfdump --verify $(DISTDIR)/$(NAME).dSYM
	@mkdir -p $(DISTDIR)/$(NAME).symbols
	@xcrun symbols -noTextInSOD -noDaemon -arch all \
	  -symbolsPackageDir $(DISTDIR)/$(NAME).symbols \
	  $(DISTDIR)/$(NAME).dSYM
	@echo [STR] $(APPNAME).app/Contents/MacOS/$(NAME)
	@$(STRIP) $(STRIPFLAGS) $(DISTDIRAPP)/Contents/MacOS/$(NAME)
	@chmod +x $(DISTDIRAPP)/Contents/MacOS/$(NAME)
	@echo [MKD] $(APPNAME).app/Contents/Resources
	@mkdir -p $(DISTDIRAPP)/Contents/Resources
	@echo [ICO] $(NAME).icns
	@cp $(SRCDIR)/Resources/app.icns $(DISTDIRAPP)/Contents/Resources/Icon.icns
	@cp $(DISTDIR)/$(NAME).Info.plist $(DISTDIRAPP)/Contents/Info.plist
	@cp $(DISTDIR)/$(NAME).provisionprofile $(DISTDIRAPP)/Contents/embedded.provisionprofile
	@sed -i'.orig' -e 's/{VERSION}/${VERSION3}/g' $(DISTDIRAPP)/Contents/Info.plist
	@sed -i'.orig' -e 's/{DISPLAYNAME}/${APPNAME}/g' $(DISTDIRAPP)/Contents/Info.plist
	@sed -i'.orig' -e 's/{OSXSDKVER}/${OSXSDKVER}/g' $(DISTDIRAPP)/Contents/Info.plist
	@sed -i'.orig' -e 's/{OSXSDKBUILDV}/${OSXSDKBUILDV}/g' $(DISTDIRAPP)/Contents/Info.plist
	@sed -i'.orig' -e 's/{OSXBUILDV}/${OSXBUILDV}/g' $(DISTDIRAPP)/Contents/Info.plist
	@sed -i'.orig' -e 's/{XCODEBUILDV}/${XCODEBUILDV}/g' $(DISTDIRAPP)/Contents/Info.plist
	@rm $(DISTDIRAPP)/Contents/Info.plist.orig
ifeq ($(APPLE_DIST_STORE),true)
	@echo [SIG] $(NAME).app
	@codesign --verbose \
	  --sign "$(PUBLISHERCN)" \
	  --keychain $(KEYCHAIN) \
	  --timestamp \
	  --options runtime \
	  --entitlements $(DISTDIR)/$(NAME).Entitlements.Store.plist \
	  $(DISTDIRAPP)
	@echo [VFY] $(APPNAME).app
	@codesign --verify -vvvd $(DISTDIRAPP)
	@echo [PKG] $(PKGUNSIGNED)
	@productbuild \
	  --version $(VERSION3) \
	  --symbolication $(DISTDIR)/$(NAME).symbols \
	  --component $(DISTDIRAPP) /Applications \
	  $(DISTDIR)/$(PKGUNSIGNED)
else
	@echo [SIG] $(APPNAME).app
	@codesign --verbose \
	  --sign "$(PUBLISHERCN)" \
	  --keychain $(KEYCHAIN) \
	  --timestamp \
	  --options runtime \
	  --entitlements $(DISTDIR)/$(NAME).Entitlements.Local.plist \
	  $(DISTDIRAPP)
	@echo [VFY] $(APPNAME).app
	@codesign --verify -vvvd $(DISTDIRAPP)
	@echo [PKG] $(PKGUNSIGNED)
	@pkgbuild \
	  --version $(VERSION3) \
	  --root $(DISTDIR)/$(NAME) \
	  --install-location /Applications \
	  --component-plist $(DISTDIR)/$(NAME).Component.plist \
	  $(DISTDIR)/$(PKGUNSIGNED)
endif
	@echo [FIL] $(PKGUNSIGNED)
	@pkgutil --payload-files $(DISTDIR)/$(PKGUNSIGNED)
ifneq ($(PRODUCTSIGNCN),)
	@echo [SIG] $(PKGSIGNED)
	@productsign \
	  --sign "$(PRODUCTSIGNCN)" \
	  --keychain $(KEYCHAIN) \
	  --timestamp \
	  $(DISTDIR)/$(PKGUNSIGNED) \
	  $(DISTDIR)/$(PKGSIGNED)
	@echo [VFY] $(PKGSIGNED)
	@pkgutil --check-signature $(DISTDIR)/$(PKGSIGNED)
ifneq ($(APPLE_ID),)
ifeq ($(APPLE_DIST_STORE),true)
	@echo [VAL] $(PKGSIGNED)
	@xcrun altool --validate-app \
	  -f $(DISTDIR)/$(PKGSIGNED) \
	  -t macOS \
	  -u $(APPLE_ID) \
	  -p $(APPLE_APPSPEC_PASS)
ifeq ($(APPLE_UPLOAD_STORE),true)
	@echo [UPL] $(PKGSIGNED)
	@xcrun altool --upload-app \
	  -f $(DISTDIR)/$(PKGSIGNED) \
	  -t macOS \
	  -u $(APPLE_ID) \
	  -p $(APPLE_APPSPEC_PASS)
endif
else
	@echo [VAL] $(PKGSIGNED)
	@xcrun notarytool submit $(DISTDIR)/$(PKGSIGNED) \
	  --apple-id=$(APPLE_ID) \
	  --team-id=$(APPLE_TEAM_ID) \
	  --password=$(APPLE_APPSPEC_PASS) \
	  --wait | tee $(DISTDIR)/$(NAME).notary.log
	@cat $(DISTDIR)/$(NAME).notary.log | \
	  grep -E -o -m1 'id: .{36}' | \
	  sed 's/id: //g' > $(DISTDIR)/$(NAME).notary.id
	@bash -c "\
	  export NOTARYID=\$$(cat $(DISTDIR)/$(NAME).notary.id);\
	  xcrun notarytool log \$$NOTARYID \
	    --apple-id=$(APPLE_ID) \
	    --team-id=$(APPLE_TEAM_ID) \
	    --password=$(APPLE_APPSPEC_PASS)"
endif
endif
endif
lib-dist-%: dist-prep
	@echo [DST] $(NAME)-$*
lib-dist: dist-prep lib-dist-x64 lib-dist-arm64
	@echo [MKD] $(LIBNAME)
	@mkdir -p $(DISTDIR)/$(NAME)/
	@echo [LIP] $(LIBNAME)$(EXTDLL)
	@lipo -create -output $(DISTDIR)/$(NAME)/$(LIBNAME)$(EXTDLL) \
	  ./lib/osx-x64/$(LIBNAME)$(EXTDLL) \
	  ./lib/osx-arm64/$(LIBNAME)$(EXTDLL)
	@echo [SYM] $(LIBNAME).dSYM
	@dsymutil \
	  -out $(DISTDIR)/$(NAME)/$(LIBNAME).dSYM \
	  $(DISTDIR)/$(NAME)/$(LIBNAME)$(EXTDLL)
	@echo [INF] $(LIBNAME).dSYM
	@dwarfdump --uuid $(DISTDIR)/$(NAME)/$(LIBNAME).dSYM
	@echo [STR] $(LIBNAME)$(EXTDLL)
	@$(STRIP) $(STRIPFLAGS) $(DISTDIR)/$(NAME)/$(LIBNAME)$(EXTDLL)
	@echo [SIG] $(LIBNAME)$(EXTDLL)
	@codesign --verbose \
	  --sign "$(PUBLISHERCN)" \
	  --keychain $(KEYCHAIN) \
	  --timestamp \
	  --options runtime \
	  $(DISTDIR)/$(NAME)/$(LIBNAME)$(EXTDLL)
	@echo [VFY] $(LIBNAME)$(EXTDLL)
	@codesign --verify -vvvd $(DISTDIR)/$(NAME)/$(LIBNAME)$(EXTDLL)
	@cp $(INCDIR)/$(NAME)/*.h $(DISTDIR)/$(NAME)/
	@echo [TAR] $(TARNAME) 
	@tar -f $(DISTDIR)/$(TARNAME) -C $(DISTDIR)/$(NAME) -c .
endif

##############################################################################################################
# LINUX
##############################################################################################################

ifeq ($(TARGET_OS),linux)
dist-prep:
	echo [VER] $(VERSION3)
	echo [DEB] $(NAME).Resources-$(VERSION3)-ubuntu-$(LSBREL)-all.deb
	mkdir -p $(DISTDIR)/$(NAME).Resources/DEBIAN
	mkdir -p $(DISTDIR)/$(NAME).Resources/usr/share/$(NAME)
	cp $(DISTDIR)/$(NAME).Resources.control $(DISTDIR)/$(NAME).Resources/DEBIAN/control
	sed -i 's/{VERSION}/${VERSION3}/g' $(DISTDIR)/$(NAME).Resources/DEBIAN/control
	cp -r ../../resources/* $(DISTDIR)/$(NAME).Resources/usr/share/$(NAME)
	dpkg-deb --build $(DISTDIR)/$(NAME).Resources \
	  $(DISTDIR)/$(NAME).Resources-$(VERSION3)-ubuntu-$(LSBREL)-all.deb > /dev/null 2>&1
dist-%: dist-prep
	echo [DST] $(NAME)-$*
	$(eval DISTDEBARCH:=$(shell \
	  case $* in \
	    (x64)   echo amd64;; \
		(x86)   echo i386;; \
		(arm64) echo arm64;; \
		(arm)   echo armhf;; \
	  esac))
	$(eval DEBFILE=$(NAME)-$(VERSION3)-ubuntu-$(LSBREL)-$(DISTDEBARCH).deb)
	echo [DEB] $(DEBFILE)
	mkdir -p $(DISTDIR)/$(NAME)-$*/DEBIAN
	mkdir -p $(DISTDIR)/$(NAME)-$*/usr/bin
	mkdir -p $(DISTDIR)/$(NAME)-$*/usr/lib
	mkdir -p $(DISTDIR)/$(NAME)-$*/usr/share/applications
	mkdir -p $(DISTDIR)/$(NAME)-$*/usr/share/pixmaps	
	cp $(DISTDIR)/$(NAME).control $(DISTDIR)/$(NAME)-$*/DEBIAN/control
	sed -i 's/{VERSION}/${VERSION3}/g' $(DISTDIR)/$(NAME)-$*/DEBIAN/control
	sed -i 's/{ARCH}/${DEBARCH}/g' $(DISTDIR)/$(NAME)-$*/DEBIAN/control
	cp $(SRCDIR)/Resources/app-256x256.png $(DISTDIR)/$(NAME)-$*/usr/share/pixmaps/$(NAME).png
	cp $(DISTDIR)/$(NAME).desktop $(DISTDIR)/$(NAME)-$*/usr/share/applications/$(NAME).desktop
	sed -i 's/{DISPLAYNAME}/${APPNAME}/g' $(DISTDIR)/$(NAME)-$*/usr/share/applications/$(NAME).desktop
	cp ./bin/linux-$*/$(NAME)$(EXTBIN) $(DISTDIR)/$(NAME)-$*/usr/bin/$(NAME)$(EXTBIN)
	chmod +x $(DISTDIR)/$(NAME)-$*/usr/bin/$(NAME)$(EXTBIN)
	dpkg-deb --build $(DISTDIR)/$(NAME)-$* $(DISTDIR)/$(DEBFILE) > /dev/null 2>&1
dist: dist-prep dist-$(TARGET_ARCH)
lib-dist-prep:
	echo [VER] $(VERSION3)
lib-dist-%: lib-dist-prep
	echo [DST] $(NAME)-$*
	$(eval DISTDEBARCH:=$(shell \
	  case $* in \
	    (x64)   echo amd64;; \
		(x86)   echo i386;; \
		(arm64) echo arm64;; \
		(arm)   echo armhf;; \
	  esac))
	$(eval DEBFILE=$(NAME)-$(VERSION3)-ubuntu-$(LSBREL)-$(DISTDEBARCH).deb)
	echo [DEB] $(DEBFILE)
	mkdir -p $(DISTDIR)/$(NAME)-$*/DEBIAN
	mkdir -p $(DISTDIR)/$(NAME)-$*/usr/include
	mkdir -p $(DISTDIR)/$(NAME)-$*/usr/lib
	cp $(DISTDIR)/$(NAME).control $(DISTDIR)/$(NAME)-$*/DEBIAN/control
	sed -i 's/{VERSION}/${VERSION3}/g' $(DISTDIR)/$(NAME)-$*/DEBIAN/control
	sed -i 's/{ARCH}/${DEBARCH}/g' $(DISTDIR)/$(NAME)-$*/DEBIAN/control
	cp $(INCDIR)/$(NAME)/*.h $(DISTDIR)/$(NAME)-$*/usr/include
	cp ./lib/linux-$*/$(LIBNAME)$(EXTDLL) $(DISTDIR)/$(NAME)-$*/usr/lib/$(LIBNAME)$(EXTDLL)
	dpkg-deb --build $(DISTDIR)/$(NAME)-$* $(DISTDIR)/$(DEBFILE) > /dev/null 2>&1
lib-dist: lib-dist-prep lib-dist-$(TARGET_ARCH)
endif

##############################################################################################################
# ANDROID
##############################################################################################################

ifeq ($(TARGET_OS),android)
dist-%:
	echo [DST] $(NAME)-$*
dist: dist-x64 dist-x86 dist-arm64 dist-arm
endif

##############################################################################################################
# WASI
##############################################################################################################

ifeq ($(TARGET_OS),wasi)
dist-%:
	echo [DST] $(NAME)-$*
dist: dist-wasm32
lib-dist-%:
	echo [DST] $(NAME)-$*
	-$(call rmdir,$(DISTDIR)/$(NAME)/$*)
	$(call mkdir,$(DISTDIR)/$(NAME)/$*)
	$(call copyfiles,$(LIBDIR)/$(LIBNAME)$(EXTDLL),$(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTDLL))
	$(STRIP) $(DISTDIR)/$(NAME)/$*/$(LIBNAME)$(EXTDLL)
lib-dist: lib-dist-wasm32
endif
