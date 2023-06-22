# APrip GNUMakefile by Alex Free
CC=gcc
CFLAGS=-Wall -Werror -Ofast
VER=1.0.3

aprip: clean
	$(CC) $(CFLAGS) aprip.c -o aprip

clean:
	rm -rf aprip.exe aprip

linux-x86:
	make aprip CFLAGS="-m32 -static -Wall -Werror -Ofast"

linux-x86_64:
	make aprip CFLAGS="-static -Wall -Werror -Ofast"

windows-x86:
	make aprip CC="i686-w64-mingw32-gcc"

windows-x86_64:
	make aprip CC="x86_64-w64-mingw32-gcc"

linux-release:
	rm -rf aprip-$(VER)-$(PLATFORM) aprip-$(VER)-$(PLATFORM).zip
	mkdir aprip-$(VER)-$(PLATFORM)
	cp -rv aprip images readme.md cd-command-logger.sh ap-type-checker.sh license.txt aprip-$(VER)-$(PLATFORM)
	chmod -R 777 aprip-$(VER)-$(PLATFORM)
	zip -r aprip-$(VER)-$(PLATFORM).zip aprip-$(VER)-$(PLATFORM)
	rm -rf aprip-$(VER)-$(PLATFORM)

windows-release:
	rm -rf aprip-$(VER)-$(PLATFORM) aprip-$(VER)-$(PLATFORM).zip
	mkdir aprip-$(VER)-$(PLATFORM)
	cp -rv aprip.exe images readme.md cd-command-logger.bat ap-type-checker.bat license.txt aprip-$(VER)-$(PLATFORM)
	chmod -R 777 aprip-$(VER)-$(PLATFORM)
	zip -r aprip-$(VER)-$(PLATFORM).zip aprip-$(VER)-$(PLATFORM)
	rm -rf aprip-$(VER)-$(PLATFORM)

linux-x86-release: linux-x86
	make linux-release PLATFORM=linux_x86_static

linux-x86_64-release: linux-x86_64
	make linux-release PLATFORM=linux_x86_64_static

windows-x86-release: windows-x86
	make windows-release PLATFORM=windows_x86

windows-x86_64-release: windows-x86_64
	make windows-release PLATFORM=windows_x86_64

clean-zip: clean
	rm -rf *.zip

all: linux-x86-release linux-x86_64-release windows-x86-release windows-x86_64-release
