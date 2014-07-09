#include "disassemble_tools.h"
#include "error.h"

void disassemble(csh handle, cs_insn *insn, uint8_t *data, size_t size, uint64_t addr){
	size_t count = cs_disasm_ex(handle, data, size, addr, 0, &insn);
	if (count > 0) {
		size_t j;
		for (j = 0; j < count; j++)
			printf("0x%016lX:\t%s\t\t%s\n", (uint64_t)insn[j].address, insn[j].mnemonic, insn[j].op_str);
		cs_free(insn, count);
	}
	else
		printf("ERROR: Failed to disassemble given code! (%s)\n", get_err(&handle));
}

void disassemble_data(SHDR* sh, uint8_t* data, size_t size, uint64_t offset){
	if(data == NULL)
		return;
	size_t i;
	for(i=0; i<sizeof(special_section)-1; i++){
		if(special_section[i].type == sh->sh_type && special_section[i].flags == sh->sh_flags){
			printf("0x%016lX:#####################################################\n0x%016lX:\t.section %s\n", offset, offset, special_section[i].name);
			break;
		}
	}
	
	if(i > sizeof(special_section)-1)
		printf("0x%016lX:#####################################################\n0x%016lX:\t.section unknown\n", offset, offset);
	
	if(!(special_section[8].type != sh->sh_type && special_section[8].flags != sh->sh_flags) && 
	   !(special_section[30].type == sh->sh_type && special_section[30].flags == sh->sh_flags)){
		for(i=0; i<size; i++, offset+=0x08)
			printf("0x%016lX:\t.byte 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
				offset, data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7]);
	}
}

void revert_elf(ELF* elf){
	elf->e_type 	= le16((uint8_t*)&elf->e_type);
	elf->e_machine	= le16((uint8_t*)&elf->e_machine);
	elf->e_version	= le32((uint8_t*)&elf->e_version);
	elf->e_entry	= le64((uint8_t*)&elf->e_entry);
	elf->e_phoff	= le64((uint8_t*)&elf->e_phoff);
	elf->e_shoff	= le64((uint8_t*)&elf->e_shoff);
	elf->e_flags	= le16((uint8_t*)&elf->e_flags);
	elf->e_ehsize	= le32((uint8_t*)&elf->e_ehsize);
	elf->e_phentsize = le16((uint8_t*)&elf->e_phentsize);
	elf->e_phnum	= le16((uint8_t*)&elf->e_phnum);
	elf->e_shentsize = le16((uint8_t*)&elf->e_shentsize);
	elf->e_shnum	= le16((uint8_t*)&elf->e_shnum);
	elf->e_shstrndx = le16((uint8_t*)&elf->e_shstrndx);
}

void revert_phdr(PHDR* ph){
	ph->p_type	= le64((uint8_t*)& ph->p_type);
	ph->p_flags	= le64((uint8_t*)& ph->p_flags);
	ph->p_offset	= le64((uint8_t*)& ph->p_offset);
	ph->p_vaddr	= le64((uint8_t*)& ph->p_vaddr);
	ph->p_paddr	= le64((uint8_t*)& ph->p_paddr);
	ph->p_filesz	= le64((uint8_t*)& ph->p_filesz);
	ph->p_memsz	= le64((uint8_t*)& ph->p_memsz);
	ph->p_align	= le64((uint8_t*)& ph->p_align);
}

void revert_shdr(SHDR* sh){
	sh->sh_name	= le32((uint8_t*)& sh->sh_name);
	sh->sh_type	= le32((uint8_t*)& sh->sh_type);
	sh->sh_flags	= le64((uint8_t*)& sh->sh_flags);
	sh->sh_addr	= le64((uint8_t*)& sh->sh_addr);
	sh->sh_offset	= le64((uint8_t*)& sh->sh_offset);
	sh->sh_size	= le64((uint8_t*)& sh->sh_size);
	sh->sh_link	= le32((uint8_t*)& sh->sh_link);
	sh->sh_info	= le32((uint8_t*)& sh->sh_info);
	sh->sh_addralign= le64((uint8_t*)& sh->sh_addralign);
	sh->sh_entsize	= le64((uint8_t*)& sh->sh_entsize);
}
