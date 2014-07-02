PKG_NAME=OpenOffice_Register.pkg

PKG_MAKER=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker
CC=gcc

PROCESSOR = $(shell uname -p)

all: postflight PKG_NAME

postflight: postflight.c
	$(CC) -arch x86_64 -arch i386 postflight.c -o postflight

PKG_NAME:
	cp postflight resources/
	- test -d $(PKG_NAME) && rm -rf $(PKG_NAME)
	- mkdir -p empty
	$(PKG_MAKER) -build -p $(PKG_NAME) -f empty -ds -i Info.plist \
		 -d Description.plist -r resources  -v
