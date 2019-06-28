#!/usr/bin/env bash -x

all:
	rm -rf img `cat FNAME.txt` temp
	sudo apt install syslinux
	sudo echo -n
	mkdir -p temp
	git clone https://github.com/LiamCoal/losapi.git temp
	./losapi-opt -a
	mkdir -p img
	mkdosfs -n LIAMOS -C `cat FNAME.txt` 2000
	syslinux `cat FNAME.txt`
	sudo mount `cat FNAME.txt` img
	clang -Wl,--oformat=binary -nostdlib -fomit-frame-pointer -fno-builtin -nostartfiles -nodefaultlibs -Wl,-e,0x7c00 -Wl,-Tbss,0x7c00 -Wl,-Tdata,0x7c00 -Wl,-Ttext,0x7c00 -Os -m16 start.c -o img/start.bin
	cp -r temp img/losapi
	sudo umount img
	sudo rm -fr temp