# LiamOS

**Readme is very likely outdated:**
Last update: 10/22/2019  
LiamOS Version: 0.0.2a (ALPHA)

## Dependencies

```shell
sudo apt update
sudo apt install qemu syslinux
```

## I'm sorry, but whats a LiamOS

LiamOS is a really badly written operating system that is an experiment.

## Files and what they are for

### At all times

Makefile: Allows you to use make to build the project  
README.md: What you're reading right now  
run.sh: Runs LiamOS in an emulator. Prefer not to run it directly, use make run32.
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

If you want to package LIAMOS into a .xz file (**super** _compressed_), use

```shell
make clean LIAMOS1.xz
```

## Installing

### The easy way. (compiles for you)

Replace sdX with your drives device name (see below)

```shell
./ddover.sh /dev/sdX
```

### The trickier way (does not compile for you)

First, compile like above, then replace sdX with your drive's device name (see below).

```shell
sudo dd if=LIAMOS1.img of=/dev/sdX bs=512 status=progress
```

#### Quick checking the device number

```shell
# Remove all drives
ls /dev/sd*
# => /dev/sda /dev/sda...

# Insert your drive that you want to write LiamOS to and wait about 15 seconds for linux to notice
# OR if you have a read/write light on your drive, wait until the second read/write is done
# It should be there
ls /dev/sd*
# => [sda stuff] + /dev/sdb or /dev/sdc etc.
# What you should know is that it should have just appeared. Not have been there before
# The one that just appeared is your USB drive, use it in the above installs
```

## Some quick warning(s)

* qemu is really slow on my computer. Maybe soon it will change but rn, theres a makefile rule to build a VirtualBox image. (booting from floppy is not syslinux approved) I would recomend using real hardware instead of VM, but its there just in case. ALSO, keep in mind that some code that works on VM, might not work on real hardware. Please test both before creating a pull request or issue.

* This is for x86/x86_64 only. Using any other arcitecture with LiamOS won't work.

* LiamOS will not compile on macOS without extreme hackery, due to stupidity with clang.
