#!/bin/bash

sudo apt install qemu
if [[ "$1" == "x86_32" ]]
then 
    qemu-system-i386 -hda LIAMOS1.img
    exit 0
fi
if [[ "$1" == "x86_64" ]]
then
    echo "WARNING: Attempting to start in 64bit mode."
    echo "         If your device is not 64bit, use run32 or exec (run32 alias)"
    qemu-system-x86_64 -hda LIAMOS1.img
    exit 0
fi

echo "ERROR: Specify either 'x86_32' or 'x86_64'"