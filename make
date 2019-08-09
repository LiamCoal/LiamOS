#!/bin/bash

make $*
EXITCODE=$?

# This file only exists so the img folder gets umounted automaticly
if [[ $EXITCODE != 0 ]]; then sudo umount img; fi
