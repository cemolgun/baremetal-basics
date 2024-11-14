# Compilation

Compilation is translation of code written in high level languages such as C to
binary formats that machine can execute. 4 main steps of compilation are:

1. Preprocessing:
   Process the preprocessor directives such as `#pragma` `#ifdef` and output the
   intermediate file.

2. Compiling:
   Translate and produce an assembly from the intermediate file.

3. Assembling:
   Generate the objects from the mnemonic machine language. These are binary
   files with relocatable adresses that will be adjusted in the linking process.

4. Linking: Combine the object files together into a single binary, adjust the
   adresses (and add extra code for OS).

Compiler is the program that do the compilation. Modern compilers perform all
these steps. Gcc, clang and msvc are some widely used C compilers.

When a compiler is called without any option, it outputs only the final binary.
The discarded intermediate (\*.i), assembly (\*.s) and object (\*.o) files can
be outputted using `-save-temps` option when using gcc compilers.

```
$ gcc -save-temps main.c -o main && ls
main  main.c  main.i  main.o  main.s
```

## Cross Compilation

Cross compilation is the process of compiling for a platform other than the host
machine that creates the binaries. Platform is the combination of operating
system and cpu architecture. For example, compiling for a RISCV MCU without OS
on a x86-64 Linux macine is cross compilation. Compiling for an ARM macOS on an
ARM macOS machine is native compilation.

Cross compilation is essential for baremetal programming since the source code
will be written and compiled on a PC and then the firmware will be uploaded to
target device (which are different platforms most of the time).

| Compiler              | Architecture | Target OS |
| --------------------- | ------------ | --------- |
| arm-none-eabi-gcc     | ARM          | -         |
| riscv64-linux-gnu-gcc | RISC-V       | Linux     |
| avr-gcc               | AVR          | -         |

For more information about gcc check out `$ man gcc`

## Objdump

Objdump is a program that displays information about binary files.
It has many capabilities such as showing the disassembly, displaying contents of
sections and providing information about file headers, symbols and relocation.

### Displaying Section Headers

```
$ arm-none-eabi-objdump -h main.o

main.o:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000520  00000000  00000000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000001  00000000  00000000  00000554  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000054  00000000  00000000  00000558  2**2
                  ALLOC
  3 .rodata       000000c9  00000000  00000000  00000558  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .comment      00000027  00000000  00000000  00000621  2**0
                  CONTENTS, READONLY
  5 .ARM.attributes 0000002e  00000000  00000000  00000648  2**0
                  CONTENTS, READONLY
```

Size: Size of section in bytes.  
LMA: Load memory adress, adress of the section when the program is loaded.  
VMA: Virtual memory adress, adress of the section while program is running.  
File off: Position of the beginning of the section  
Algn: Byte alignment, 2\*\*2 = $2^2$: Aligned to 4 bytes  

| Section         | Content                 |
| --------------- | ----------------------- |
| .text           | Program code            |
| .data           | Initialized variables   |
| .bss            | Uninitialized variables |
| .rodata         | Read only data          |
| .comment        | Info added by compiler  |
| .ARM.attributes | ARM metadata            |

### Disassemble

```
$ arm-none-eabi-objdump -d main.o

main.o:     file format elf32-littlearm

Disassembly of section .text:

00000000 <main>:
   0:	b580      	push	{r7, lr}
   2:	af00      	add	r7, sp, #0
   ...
```

### Display Full Content

```
$ arm-none-eabi-objdump -s main.o

main.o:     file format elf32-littlearm

Contents of section .text:
 0000 80b500af fff7feff fff7feff 0948fff7  .............H..
 0010 feff0948 fff7feff fff7feff fff7feff  ...H............
 ...
 ...
 Contents of section .comment:
  0000 00474343 3a202831 353a3133 2e322e72  .GCC: (15:13.2.r
  0010 656c312d 32292031 332e322e 31203230  el1-2) 13.2.1 20
  0020 32333130 303900                      231009.
 Contents of section .ARM.attributes:
  0000 412d0000 00616561 62690001 23000000  A-...aeabi..#...
  0010 0537452d 4d00060d 074d0902 12041401  .7E-M....M......
  0020 15011703 18011901 1a011e06 2201      ............".
```

For more information about objdump check out `$ man objdump`

## Linker Script

Linker script is the file that provides linker information about how to link
objects into single binary. Linker script is supplied to gcc with `-T` option.

### Syntax

`xyz = 0x123;`: create symbol xyz with value 0x123.

`ENTRY( xxx )`: specify the entry point of program. Not necessary for program to
work but necessary for debugging.

`MEMORY { ... }`: define the memory regions.

```ld
MEMORY
{
  NAME1(attribute): ORIGIN =0x123, LENGTH =321
  NAME2(attribute): ORIGIN =0x123, LENGTH =321
  ...
}
```

| Memory Attribute | Explanation    |
| ---------------- | -------------- |
| r                | Read Only      |
| w                | Read, Write    |
| a                | Allocatable    |
| x                | Executable     |
| i, l             | Initialized    |
| !                | Negate meaning |

`SECTIONS{ ... }`: organize / combine input sections and create output sections.

```ld
SECTIONS
{
    .sect1 0x123 :     /* .sect1 starts at 0x123 */
    {
      file1.o          /* file1.o and .sect1 of file3.o is included */
      file3.o(.sect1)
    }
    
    .sect2 :
    {
      *(.sect2)        /* Wildcard, all files with .sect2 */
    }
    
    .sect3 :
    {
        _ssect3 = .;   /* . can be used to create symbol of a location (vma) */
        *(.sect3)
        ALIGN(4)       /* 4 byte alignment */
        _esect3 = .;
    } >vma AT>lma      /* Load section at lma, run from vma */
}
```

Symbols are references to memory locations and are resolved in linking stage. 
Symbols that are defined in linker script can be accessed within code using 
`extern` keyword in C.

For more information about linking check out `$ man ld`


# Flashing

..

