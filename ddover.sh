#!/bin/bash
# Simple script for dding LIAMOS1.img to a drive

DEVICE=$1

if [[ ! -e $DEVICE ]]; then
    echo -e "\e[31;1mFile $DEVICE does not exist.\e[0m"
    exit 1
fi

if [[ "$2" == "upgrade" ]]; then
    echo -e "\e[32;1mMaking upgrade objects\e[0m"
    make clean upgrade-objects
    echo -e "\e[32;1mMounting device \e[0m(\e[33;1mrequires sudo\e[0m)"
    if [[ ! -d img ]]; then
        mkdir img
    fi
    sudo mount $DEVICE img
    echo -e "\e[32;1mCleaning device\e[0m(\e[33;1mrequires sudo\e[0m"
    echo -e "\e[32;1mFiles to be deleted:\e[31;1m"
    sudo find img
    sudo find img -delete
    echo -e "\e[32;1mCopying files \e[0m(\e[33;1mrequires sudo\e[0m)"
    FILES=$(find out -type f)
    echo -e "\e[32;1mFiles to copy:\n\e[34;1m$FILES\e[0m"
    sudo cp -rf out/* img
    echo -e "\e[32;1mUnmounting device \e[0m(\e[33;1mrequires sudo\e[0m)"
    sudo umount $DEVICE
    echo -e "\e[34;1mDone.\e[0m"
    exit 1
fi

echo -e "\e[32;1mMaking LIAMOS1.img\e[0m"
make clean all
echo -e "\e[32;1mWriting to $DEVICE\e[0m"
sudo dd if=LIAMOS1.img of=$DEVICE bs=512 status=progress
echo -e "\e[34;1mDone.\e[0m"
