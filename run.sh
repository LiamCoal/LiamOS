#!/bin/bash

ninja liamos.efi
dd if=/dev/zero of=liamos.img bs=512 count=93750
uefi-run -b /usr/share/OVMF/OVMF_CODE.fd -q /usr/bin/qemu-system-x86_64 liamos.efi
