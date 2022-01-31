# cOS, an OS made in C



## Dependencies

```
make nasm mtools
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
        ├── build
        │   ├── bootsector.bin
        │   ├── os.bin
        │   └── stage2.bin
        ├── Makefile
        ├── stage1
        │   └── bootsector.asm
        └── stage2
            └── stage2.asm
```