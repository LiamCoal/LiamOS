all:
	gsettings set org.gnome.desktop.media-handling automount-open false
	rm -rf img `cat FNAME.txt` temp
	sudo apt install syslinux
	sudo echo -n
	mkdir -p img
	mkdosfs -n LIAMOS -C `cat FNAME.txt` 2000
	syslinux `cat FNAME.txt`
	sudo mount `cat FNAME.txt` img
	mkdir -p img/boot/syslinux
	clang -Wl,--oformat=binary -nostdlib -fomit-frame-pointer -fno-builtin -nostartfiles -nodefaultlibs -Wl,-e,0x7C00 -Wl,-Tbss,0x7C00 -Wl,-Tdata,0x7C00 -Wl,-Ttext,0x7C00 -m16 start.c -o img/boot/start.bss
	cp boot.cfg img/boot/syslinux/syslinux.cfg
	sleep 1
	sudo umount img
	sudo rm -fr temp
	gsettings set org.gnome.desktop.media-handling automount-open true