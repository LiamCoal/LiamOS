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
src/kernel.c: Main kernel file  
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

## Some quick warning(s)

qemu is really slow on my computer. Maybe soon it will change but rn, theres a makefile rule to build a VirtualBox image. (booting from floppy is not syslinux approved) I would recomend using real hardware instead of VM, but its there just in case. ALSO, keep in mind that some code that works on VM, might not work on real hardware. Please test both before creating a pull request or issue.
