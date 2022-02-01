# cOS, an OS made in C

## Dependencies


### make
Make is used to automate the build process. It is used to compile the kernel, and to build the bootloader.

### nasm
Compiles assembly code into machine code.

### mtools
A collection of utilities for manipulating MS-DOS filesystems.


## Installation

### Install on Manjaro / Arch	
```
sudo pacman -S make nasm mtools
```

### Install on Ubuntu
```
sudo apt-get install make nasm mtools
```

### Install on Fedora / CentOS
```
sudo dnf install make nasm mtools
```

## Repository structure
```
.
├── Docs
│   ├── assets
│   │   └── drive.png
│   ├── build.md
│   ├── Links.md
│   ├── schematics.drawio
│   └── TODO.md
├── LICENSE
├── README.md
└── src
    └── bootloader
        ├── Makefile
        ├── stage1
        │   └── bootsector.asm
        └── stage2
            └── stage2.asm
```