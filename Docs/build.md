# Build process

## Generating the disk

A FAT32 formated disk is generated using `dd` and `mkfs.fat`. 

## Bootloader

Once the disk is generated, the second stage is copied at the root of the newly created disk, while the first stage is being written on the first sector of the disk.

<img src="assets/drive.png" width="300">
