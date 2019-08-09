all:
	sudo rm -rf img LIAMOS1.img temp out
	mkdir out
	sudo apt install syslinux clang
	sudo echo -n
	mkdir -p img
	mkdosfs -n LIAMOS -C LIAMOS1.img 20000
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

run32: all
	./run.sh x86_32

exec: run32

run64: all
	./run.sh x86_64