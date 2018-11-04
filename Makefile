DESTDIR ?= /

PREFIXBIN=$(DESTDIR)/usr/bin
PREFIXETC=$(DESTDIR)/etc
PREFIXSHARE=$(DESTDIR)/usr/share/pink-pony
PREFIXAPPS=$(DESTDIR)/usr/share/applications
PREFIXPIXMAPS=$(DESTDIR)/usr/share/pixmaps
PREFIXLIB=$(DESTDIR)/usr/lib/

.PHONY: install 

compile:
	scons
install:
	install -o root -d $(PREFIXBIN)
	install -o root -d $(PREFIXETC)
	install -o root -d $(PREFIXSHARE)
	install -o root -d $(PREFIXAPPS)
	install -o root -d $(PREFIXPIXMAPS)
	install -o root -d $(PREFIXLIB)
	install -m 755 -o root install/pink-pony $(PREFIXBIN)
	install -m 644 -o root pony.options $(PREFIXETC)
	install -m 755 -o root Pony $(PREFIXLIB)
	install -m 644 -o root  README pony.options
	rsync -r --chown root:root --chmod D755,F664  resources $(PREFIXSHARE) --delete-after
	install -m 644 -o root install/pink-pony.desktop $(PREFIXAPPS)
	install -m 644 -o root install/pink-pony.png $(PREFIXPIXMAPS)

uninstall:
	rm $(PREFIXBIN)/pink-pony
	rm -Rf $(PREFIXSHARE)
	rm -Rf $(PREFIXLIB)/Pony
	rm $(PREFIXAPPS)/pink-pony.desktop
	rm $(PREFIXPIXMAPS)/pink-pony.png
	rm $(PREFIXETC)/pony.options
