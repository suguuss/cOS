# cOS, an OS made in C
---

  * [The Operating System](#the-operating-system)
    + [:minidisc: Bootloader](#-minidisc--bootloader)
      - [Legacy booting](#legacy-booting)
      - [:floppy_disk: FAT32](#-floppy-disk--fat32)
      - [:dvd: Reading sectors from the 'disk'](#-dvd--reading-sectors-from-the--disk-)
      - [:page_with_curl: GDT - Global Desriptor Table](#-page-with-curl--gdt---global-desriptor-table)
      - [:lock: Protected Mode](#-lock--protected-mode)
    + [:desktop_computer: Kernel](#-desktop-computer--kernel)
      - [:electric_plug: Ports](#-electric-plug--ports)
      - [:stopwatch: Interrupts](#-stopwatch--interrupts)
        * [:scroll: IDT - Interrupt Descriptor Table](#-scroll--idt---interrupt-descriptor-table)
      - [:keyboard: Keyboard](#-keyboard--keyboard)
      - [:hourglass: Timer / PIC - Programmable Interrupt Controller](#-hourglass--timer---pic---programmable-interrupt-controller)
      - [:desktop_computer: Screen](#-desktop-computer--screen)
        * [Cursor](#cursor)
        * [Color](#color)
        * [Printing](#printing)
        * [Scrolling](#scrolling)
      - [:cd: Disk I/O](#-cd--disk-i-o)
        * [Read / Write](#read---write)
  * [:rocket: Dependencies](#-rocket--dependencies)
    + [make](#make)
    + [nasm](#nasm)
    + [mtools](#mtools)
    + [Install on Manjaro / Arch](#install-on-manjaro---arch)
    + [Install on Ubuntu](#install-on-ubuntu)
    + [Install on Fedora / CentOS](#install-on-fedora---centos)
    + [Building the cross compiler](#building-the-cross-compiler)
  * [Repository structure](#repository-structure)
- [Links](#links)

<small><i><a href='http://ecotrust-canada.github.io/markdown-toc/'>Table of contents generated with markdown-toc</a></i></small>


## The Operating System

### :minidisc: Bootloader
#### Legacy booting
The bios loads the first sector of the bottable device and look for the magic number (0xAA55, chosen number to represent a bootable signature). If the number is found, the bios jumps to the first instructions in the sector.

#### :floppy_disk: FAT32
#### :dvd: Reading sectors from the 'disk'
#### :page_with_curl: GDT - Global Desriptor Table

#### :lock: Protected Mode

### :desktop_computer: Kernel
#### :electric_plug: Ports
#### :stopwatch: Interrupts

##### :scroll: IDT - Interrupt Descriptor Table
#### :keyboard: Keyboard
#### :hourglass: Timer / PIC - Programmable Interrupt Controller
#### :desktop_computer: Screen
##### Cursor
##### Color
##### Printing
##### Scrolling

#### :cd: Disk I/O
##### Read / Write



---
## :rocket: Dependencies

### make
Make is used to automate the build process. It is used to compile the kernel, and to build the bootloader.

### nasm
Compiles assembly code into machine code.

### mtools
A collection of utilities for manipulating MS-DOS filesystems.

### Install on Manjaro / Arch	
```
sudo pacman -S make nasm qemu mtools
```

### Install on Ubuntu
```
sudo apt-get install make nasm qemu mtools 
```

### Install on Fedora / CentOS
```
sudo dnf install make nasm qemu mtools
```

### Building the cross compiler

To build the cross compiler, you can use a script inside the `scripts` folder. The credit for the script goes to [mell-o-tron](https://github.com/mell-o-tron). If no script are available for your distro, you can refer to [this table](https://wiki.osdev.org/GCC_Cross-Compiler#Installing_Dependencies) from the osdev wiki and install the dependencies yourself.

---
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
├── Makefile
├── README.md
├── scripts
│   ├── setup-gcc-arch.sh
│   └── setup-gcc-ubuntu.sh
└── src
    ├── bootloader
    │   ├── bootsector.asm
    │   └── Makefile
    └── kernel
        ├── drivers
        │   ├── disk
        │   │   ├── ata
        │   │   │   ├── ata.c
        │   │   │   └── ata.h
        │   │   └── fat32
        │   │       ├── fat32.c
        │   │       └── fat32.h
        │   ├── keyboard
        │   │   ├── ch-fr_keymap.h
        │   │   ├── keyboard.c
        │   │   └── keyboard.h
        │   ├── ports
        │   │   ├── ports.c
        │   │   └── ports.h
        │   └── screen
        │       ├── color
        │       │   ├── color.c
        │       │   └── color.h
        │       ├── cursor
        │       │   ├── cursor.c
        │       │   └── cursor.h
        │       └── print
        │           ├── print.c
        │           └── print.h
        ├── interrupts
        │   ├── interrupts.c
        │   └── interrupts.h
        ├── kernel.c
        ├── kernel_entry.asm
        ├── Makefile
        └── stdlibs
            ├── stdlib.c
            ├── stdlib.h
            ├── string.c
            └── string.h
```

# Links
https://ecotrust-canada.github.io/markdown-toc/