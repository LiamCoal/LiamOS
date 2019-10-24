#!/bin/bash
# Simple script for dding LIAMOS1.img to a drive

DEVICE=$1

if [[ ! -e $DEVICE ]]; then
    echo -e "\e[31;1mFile $DEVICE does not exist.\e[0m"
    exit 1
fi

echo -e "\e[32;1mMaking LIAMOS1.img\e[0m" &&
make clean all &&
echo -e "\e[32;1mWriting to $DEVICE\e[0m" &&
sudo dd if=LIAMOS1.img of=$DEVICE bs=512 status=progress &&
echo -e "\e[34;1mDone.\e[0m"
