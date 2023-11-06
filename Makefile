# aprip GNUMakefile by Alex Free
PROGRAM=aprip
CC=gcc
C_FLAGS=-Wall -Werror -Ofast -static
VER=1.0.6
RELEASE_FILES=images readme.md changelog.md license.txt

$(PROGRAM): clean
	$(CC) $(C_FLAGS) $(PROGRAM).c -o $(PROGRAM)

clean:
	rm -rf $(PROGRAM).exe $(PROGRAM)

linux-x86:
	make $(PROGRAM) C_FLAGS="-m32 $(C_FLAGS)"

linux-x86_64:
	make $(PROGRAM)

windows-x86:
	make $(PROGRAM) CC="i686-w64-mingw32-gcc"

windows-x86_64:
	make $(PROGRAM) CC="x86_64-w64-mingw32-gcc"

linux-release:
	rm -rf $(PROGRAM)-v$(VER)-$(PLATFORM) $(PROGRAM)-v$(VER)-$(PLATFORM).zip
	mkdir $(PROGRAM)-v$(VER)-$(PLATFORM)
	cp -rv $(PROGRAM) cd-command-logger.sh ap-type-checker.sh $(RELEASE_FILES) $(PROGRAM)-v$(VER)-$(PLATFORM)
	chmod -R 777 $(PROGRAM)-v$(VER)-$(PLATFORM)
	zip -r $(PROGRAM)-v$(VER)-$(PLATFORM).zip $(PROGRAM)-v$(VER)-$(PLATFORM)
	rm -rf $(PROGRAM)-v$(VER)-$(PLATFORM)

windows-release:
	rm -rf $(PROGRAM)-v$(VER)-$(PLATFORM) $(PROGRAM)-v$(VER)-$(PLATFORM).zip
	mkdir $(PROGRAM)-v$(VER)-$(PLATFORM)
	cp -rv $(PROGRAM).exe cd-command-logger.bat ap-type-checker.bat $(RELEASE_FILES) $(PROGRAM)-v$(VER)-$(PLATFORM)
	chmod -R 777 $(PROGRAM)-v$(VER)-$(PLATFORM)
	zip -r $(PROGRAM)-v$(VER)-$(PLATFORM).zip $(PROGRAM)-v$(VER)-$(PLATFORM)
	rm -rf $(PROGRAM)-v$(VER)-$(PLATFORM)

linux-x86-release: linux-x86
	make linux-release PLATFORM=linux-x86_static

linux-x86_64-release: linux-x86_64
	make linux-release PLATFORM=linux-x86_64_static

windows-x86-release: windows-x86
	make windows-release PLATFORM=windows-x86

windows-x86_64-release: windows-x86_64
	make windows-release PLATFORM=windows-x86_64

clean-zip: clean
	rm -rf *.zip

all: linux-x86-release linux-x86_64-release windows-x86-release windows-x86_64-release
