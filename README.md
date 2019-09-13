# LiamOS

## Dependencies

```shell
sudo apt update
sudo apt install qemu syslinux
```

## I'm sorry, but whats a LiamOS

LiamOS is a really badly written operating system that is an experiment.
I mean, it boots and does nothing...

## Files and what they are for

### At all times

Makefile: Allows you to use make to build the project

README.md: What you're reading right now  

run.sh: Runs LiamOS in an emulator. Prefer not to run it directly, use make exec.

boot.cfg: Syslinux config file. [see Syslinux](syslinux.org).  

src/kernel/kernel.s: Main kernel file  

.gitignore: Git, ignore these files  

### Only after compiling

out/: Directory where all of the files end up before they are copyed to img  

img/: Mount dir of LIAMOS1.img.

## How to compile

```shell
make clean all
```

is all it takes to build LiamOS.

```shell
make clean run32
```

runs LiamOS in qemu after build.

If you want to package LIAMOS into a .tar.xz file, use

```shell
make clean LIAMOS1.tar.xz
```
