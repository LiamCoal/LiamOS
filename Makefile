all:
	./losapi-opt
	clang -Wl,--oformat=binary -nostdlib -fomit-frame-pointer -fno-builtin -nostartfiles -nodefaultlibs -Wl,-e,0x7c00 -Wl,-Tbss,0x7c00 -Wl,-Tdata,0x7c00 -Wl,-Ttext,0x7c00 -Oz -m16 start.c -o start.bin
