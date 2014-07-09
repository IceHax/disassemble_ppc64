disassembler for PPC64 ELFs
===========================

This is a simple program that disassemble PPC64.
It uses capstone (https://github.com/aquynh/capstone) to 
disassemble the PPC64 code, i just implemented a parser to
load the ELFs into the disassembler.


Authors:
--------

* Giovanni Dante Grazioli (aka Wargio/Deroad)

Compile:
--------

`make`

How to use it:
--------------

`./disassemble_ppc64 my_ppc64.elf >> output.txt`

