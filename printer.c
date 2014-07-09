#include "printer.h"
#include <stdio.h>
#define LOG2(X) ((unsigned) (8*sizeof(uint64_t) - __builtin_clzll((X)) - 1))
void print_elf(ELF* elf){
	printf("Elf Header\n");
	printf("File Version            0x%02x\n", elf->e_ident[6]);
	printf("Type                    0x%04x\n", elf->e_type);
	printf("Machine Type            0x%04x\n", elf->e_machine);
	printf("Version                 0x%08x\n", elf->e_version);
	printf("Entry Point Address     0x%016lx\n", elf->e_entry);
	printf("Program Header Offset   0x%016lx\n", elf->e_phoff);
	printf("Section Header Offset   0x%016lx\n", elf->e_shoff);
	printf("Flag                    0x%04x\n", elf->e_flags);
	printf("ELF Header Size         0x%08x (%u Bytes)\n", elf->e_ehsize, elf->e_ehsize);
	printf("Size Progr Hdr Entry    0x%04x (%u Bytes)\n", elf->e_phentsize, elf->e_phentsize);
	printf("Number Progr Entries    0x%04x (%u)\n", elf->e_phnum, elf->e_phnum);
	printf("Size Sect  Hdr Entry    0x%04x (%u Bytes)\n", elf->e_shentsize, elf->e_shentsize);
	printf("Number Sect Entries     0x%04x (%u)\n", elf->e_shnum, elf->e_shnum);
	printf("Section String Table    0x%04x\n", elf->e_shstrndx);

}

void print_phdr(PHDR* ph, uint16_t i){
	if(i==0)
		printf( "\nProgram\n"
			"type       | attributes | file offset        | virtual address    | phisical address   | "
			"file segment size  | mem segment size   | align\n");
	printf("0x%08x | ", ph->p_type);
	printf("0x%08x | ", ph->p_flags);
	printf("0x%016lx | ", ph->p_offset);
	printf("0x%016lx | ", ph->p_vaddr);
	printf("0x%016lx | ", ph->p_paddr);
	printf("0x%016lx | ", ph->p_filesz);
	printf("0x%016lx | ", ph->p_memsz);
	printf("0x%03u\n", LOG2(ph->p_align));
}

void print_shdr(SHDR* sh, uint16_t i){
	if(i==0)
		printf( "\nSections\n"
			"name       | type       | section attributes | virtual address    | offset in file     | "
			"size of section    | link       | misc       | address align      | entries size\n");
	printf("0x%08x | ", sh->sh_name);                 /* section name */
	printf("0x%08x | ", sh->sh_type);                 /* section type */
	printf("0x%016lx | ", sh->sh_flags);                /* section attributes */
	printf("0x%016lx | ", sh->sh_addr);                 /* virtual address in memory */
	printf("0x%016lx | ", sh->sh_offset);               /* offset in file */
	printf("0x%016lx | ", sh->sh_size);                 /* size of section */
	printf("0x%08x | ", sh->sh_link);                 /* link to other section */
	printf("0x%08x | ", sh->sh_info);                 /* miscellaneous information */
	printf("0x%016lx | ", sh->sh_addralign);            /* address alignment boundary */
	printf("0x%016lx", sh->sh_entsize);              /* size of entries, if section has table */

	for(i=0; i<sizeof(special_section)-1; i++){
		if(special_section[i].type == sh->sh_type && special_section[i].flags == sh->sh_flags){
			printf(" | %s\n", special_section[i].name);
			break;
		}
	}
	if(i > sizeof(special_section))
			printf(" | unknown\n");
}

