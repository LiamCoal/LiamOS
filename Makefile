all:
	sudo rm -rf img LIAMOS1.img temp out
	mkdir out
	sudo apt install syslinux clang
	sudo echo -n
	mkdir -p img
	mkdosfs -n LIAMOS -C LIAMOS1.img 2000000
	syslinux LIAMOS1.img
	sudo mount LIAMOS1.img img
	sudo mkdir -p img/boot/syslinux
	mkdir out/boot
	@# Make executables
	nasm -o out/boot/kernel.bin src/kernel/kernel.s

	@# Finish up
	sudo cp boot.cfg img/boot/syslinux/syslinux.cfg
	sudo cp -r out/** img
	sleep 1
	sudo umount img
	sudo rm -fr temp *.elf *.bin *.xz
	zip -9 LIAMOS1.zip LIAMOS1.img
	rm LIAMOS1.img # For storage space reasons
	xz LIAMOS1.zip

all0:
	sudo rm -rf img LIAMOS1.img temp out
	mkdir out
	sudo apt install syslinux clang
	sudo echo -n
	mkdir -p img
	mkdosfs -n LIAMOS -C LIAMOS1.img 2000000
	syslinux LIAMOS1.img
	sudo mount LIAMOS1.img img
	sudo mkdir -p img/boot/syslinux
	mkdir out/boot
	@# Make executables
	nasm -o out/boot/kernel.bin src/kernel/kernel.s

	@# Finish up
	sudo cp boot.cfg img/boot/syslinux/syslinux.cfg
	sudo cp -r out/** img
	sleep 1
	sudo umount img
	sudo rm -fr temp *.elf *.bin
	# zip -9 LIAMOS1.zip LIAMOS1.img
	# rm LIAMOS1.img # For storage space reasons
	# xz LIAMOS1.zip

run32: all0 # all0 dosent remove LIAMOS1.img
	./run.sh x86_32
	rm LIAMOS1.img # For space reasons

exec: run32

run64: all
	./run.sh x86_64

todo:
	@head /dev/urandom | tr -dc a-z0-9 | head -c 7

gettodo:
	@git grep -n TODO src

.PHONY: todo