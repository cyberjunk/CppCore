# File Operations on Host OS

# Delete Files in Folder by Pattern
define deletefiles
	find $(1) -type f -name '$(2)' -delete
endef

# Delete Folder and Subfolders
define rmdir
	rm -rf $(1)
endef

# Create Folder
define mkdir
	mkdir $(1)
endef

# Copy Files between Folders by Pattern
define copyfiles
	cp $(1) $(2)
endef
