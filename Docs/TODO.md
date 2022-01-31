# TODO for the os

- [ ] Complete the TODO list 
- [ ] Write the bootloader
  - [ ] Write the 1st stage
  - [ ] Write the 2nd stage
- [ ] Write the kernel


---

## Bootloader

### 1st Stage
The first stage will be used to load the second stage. The first stage is limited in size, because he must be inside the first sector of the disk. Using a 2 stage bootloader lets us bypass this size limit.

### 2nd Stage
The second stage will have to do all the following stuff : 

- [ ] Set up a stable environment
- [ ] Do Protected Mode readying stuff (GDT, IDT, A20 gate, etc.)
- [ ] Enter Protected Mode (or skip this step and enter long mode - directly)
- [ ] Set up Long Mode readying stuff (PAE, PML4, etc.) - Remember - to set up the higher-half addressing!
- [ ] Enter Long Mode by far jump to the kernel entry point in (virtual) memory 

[Source - osdev wiki](https://wiki.osdev.org/Creating_a_64-bit_kernel#With_your_own_boot_loader)

## Kernel