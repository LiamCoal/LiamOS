.PHONY : seeallrewrite all clean rebuild mkdirs

all: LIAMOS1.img

mkdirs:
	mkdir -p out/boot/syslinux

clean:
	rm -rf LIAMOS1.img out

rebuild: clean all

seeallrewrite:
	@git grep -n "rewrite pls" src

LIAMOS1.img: mkdirs boot.cfg kernel.bin
	mkdosfs -n LIAMOS -C LIAMOS1.img 2000000
	syslinux LIAMOS1.img
	
	cp boot.cfg out/boot/syslinux/syslinux.cfg

	$(eval tmpdir := $(shell mktemp -d))
	sudo mount LIAMOS1.img $(tmpdir)
	sudo cp -r out/** $(tmpdir)
	sudo umount $(tmpdir)

LIAMOS1.zip: LIAMOS1.img
	zip -9 LIAMOS1.zip LIAMOS1.img

LIAMOS1.zip.xz: LIAMOS1.zip
	xz LIAMOS1.zip

run32: LIAMOS1.img
	./run.sh x86_32
	rm LIAMOS1.img # For space reasons

exec: run32

kernel.bin: src/kernel/kernel.s
	nasm -o out/boot/kernel.bin src/kernel/kernel.s