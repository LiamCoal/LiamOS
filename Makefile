.PHONY : all clean rebuild mkdirs src.tar.xz

all: LIAMOS1.img
pkg: LIAMOS1.zip.xz src.tar.xz

mkdirs:
	mkdir -p out/boot/syslinux

clean:
	rm -rf LIAMOS1.* out *.o *.elf *.bin

rebuild: clean all

LIAMOS1.img: mkdirs boot.cfg kernel.bin
	mkdosfs -n LIAMOS -C LIAMOS1.img 2000
	syslinux LIAMOS1.img
	
	cp boot.cfg out/boot/syslinux/syslinux.cfg

	$(eval tmpdir := $(shell mktemp -d))
	sudo mount LIAMOS1.img $(tmpdir)
	sudo cp -r out/** $(tmpdir)
	sudo umount $(tmpdir)

%.zip: %.img
	zip -9 $@ $<

%.zip.xz: %.zip
	xz $<

src.tar.xz:
	tar -Jcf src.tar.xz Makefile LICENSE boot.cfg src/** run.sh

run32: LIAMOS1.img
	./run.sh x86_32
	rm LIAMOS1.img # For space reasons

kernel.bin: src/kernel.c
	clang -Wl,--oformat=binary,-Ttext,0x7C00,-Tdata,0x7E00,-Tbss,0x7E00 -nostdlib -nostartfiles -nodefaultlibs -m16 -Os -o out/boot/kernel.bin src/kernel.c
