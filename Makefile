.PHONY : all clean rebuild mkdirs src.tar.xz

all: LIAMOS1.img
pkg: LIAMOS1.zip.xz src.tar.xz

mkdirs:
	mkdir -p out/boot/syslinux

clean:
	rm -rf LIAMOS1.* out *.o *.elf *.bin

rebuild: clean all

LIAMOS1.img: mkdirs boot.cfg kernel.bin
	mkdosfs -h 0 -R 1 -F 16 -n LIAMOS -C LIAMOS1.img 10000
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

run64: LIAMOS1.img
	./run.sh x86_64

LIAMOS1.vdi: LIAMOS1.img
	vbox-img convert --srcfilename LIAMOS1.img --dstfilename LIAMOS1.vdi --srcformat RAW --dstformat VDI --variant Standard # WARNING!!! VirtualBox runs into checksum issues.

%.bin: src/%.c
	clang -fasm-blocks -masm=intel -Wl,--oformat=binary,-Ttext,0x1000,-Trodata,0x0000,-Tdata,0x0A00,-Tbss,0x0A00 -nostdlib -nostartfiles -nodefaultlibs -m16 -Os -o out/$@ $<

kernel.bin: src/kernel.c src/kitten_desktop.h src/kernel.h src/kitten_desktop.c
	clang -fasm-blocks -masm=intel -Wl,--oformat=binary,-Ttext,0x7C00,-Trodata,0xA000,-Tdata,0x9000,-Tbss,0x9000 -nostdlib -nostartfiles -nodefaultlibs -m16 -Os -o out/boot/kernel.bin src/kernel.c src/kitten_desktop.c