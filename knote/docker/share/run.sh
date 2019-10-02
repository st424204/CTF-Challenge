#!/bin/bash

exec timeout 300 qemu-system-x86_64 \
    -m 256M \
    -nographic \
    -kernel /home/knote/bzImage \
    -append 'console=ttyS0 loglevel=3 oops=panic panic=1 kaslr' \
    -monitor /dev/null \
    -initrd /home/knote/initramfs.cpio.gz  \
    -smp cores=4,threads=4 \
    -cpu kvm64,smep,smap
