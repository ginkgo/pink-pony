DESTDIR ?= /

PREFIXBIN=$(DESTDIR)/usr/bin
PREFIXETC=$(DESTDIR)/etc
PREFIXSHARE=$(DESTDIR)/usr/share/pink-pony
PREFIXAPPS=$(DESTDIR)/usr/share/applications
PREFIXPIXMAPS=$(DESTDIR)/usr/share/pixmaps
PREFIXLIB=$(DESTIDIR)/usr/lib/

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
	install -m 644 -o root  README resources/GLSL resources/fonts resources/levels resources/models resources/music resources/textures pony.options resources/levels.xml $(PREFIXSHARE)
	install -m 644 -o root install/pink-pony.desktop $(PREFIXAPPS)
	install -m 644 -o root install/pink-pony.png $(PREFIXPIXMAPS)

uninstall:
	rm $(PREFIXBIN)/pink-pony
	rm -Rf $(PREFIXSHARE)
	rm -Rf $(PREFIXLIB)/Pony
	rm $(PREFIXAPPS)/pink-pony.desktop
	rm $(PREFIXPIXMAPS)/pink-pony.png
	rm $(PREFIXETC)/pony.options
