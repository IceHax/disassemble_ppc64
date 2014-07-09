#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <capstone/capstone.h>

#include "error.h"
#include "elf.h"
#include "disassemble_tools.h"
#include "printer.h"

static FILE *fp;


void exec(){
	uint16_t i, j;
	uint64_t addr;
	csh handle;
	cs_insn *insn;
	PHDR ph;
	ELF elf;
	SHDR sh;
	uint8_t *data = NULL;
	va_tbl* TBL = NULL;
	
	
	if (cs_open(CS_ARCH_PPC, CS_MODE_64+CS_MODE_BIG_ENDIAN, &handle) != CS_ERR_OK){
		printf("ERROR:%s\n", get_err(&handle));
		goto end;
	}
	cs_option(handle, CS_OPT_SKIPDATA, CS_OPT_ON);
	
	fseek(fp, 0, SEEK_SET);
	fread((void*) &elf, sizeof(ELF), 1, fp);
	revert_elf(&elf); // because it BE on LE machine
	
	if(ELF_MAGIC != *((uint32_t*)&elf.e_ident)){
		printf("Wrong ELF_MAGIC (0x%08x)\n", *((uint32_t*)&elf.e_ident));
		goto end;
	}
	
	if(elf.e_machine != EM_PPC64){
		printf("e_machine (%x) != EM_PPC64\n", elf.e_machine);
		goto end;
	}
	
	TBL = (va_tbl*) malloc(elf.e_shnum*sizeof(va_tbl));
	
	print_elf(&elf);
	
	addr = elf.e_phoff;
	for(i=0; i<elf.e_phnum; i++, addr+=sizeof(PHDR)){
		memset((void*)&ph, 0, sizeof(PHDR));

		fseek(fp, addr, SEEK_SET);
		fread((void*) &ph, sizeof(PHDR), 1, fp);
		revert_phdr(&ph);
		print_phdr(&ph, i);
	}

	addr = elf.e_shoff;
	for(i=0; i<elf.e_shnum; i++, addr+=sizeof(SHDR)){
		memset((void*)&sh, 0, sizeof(SHDR));

		fseek(fp, addr, SEEK_SET);
		fread((void*) &sh, sizeof(SHDR), 1, fp);
		revert_shdr(&sh);
		print_shdr(&sh, i);
		TBL[i].off = addr;
		TBL[i].va  = sh.sh_addr;
		TBL[i].used= 0;
	}

	printf("\n\n#### Disassemble ####\n");
	addr = elf.e_phoff;
	for(i=0; i<elf.e_phnum; i++, addr+=sizeof(PHDR)){
		memset((void*)&ph, 0, sizeof(PHDR));
		fseek(fp, addr, SEEK_SET);
		fread((void*) &ph, sizeof(PHDR), 1, fp);
		revert_phdr(&ph);

		for(j=0;j<elf.e_shnum-1;j++){
			if(TBL[j].used == 0 && TBL[j].va <= ph.p_vaddr){
				TBL[j].used++;
				fseek(fp, TBL[j].off, SEEK_SET);
				fread((void*) &sh, sizeof(SHDR), 1, fp);
				revert_shdr(&sh);
				if(sh.sh_size != 0)
					data = (uint8_t*) malloc(sh.sh_size);
				else
					data = NULL;
				disassemble_data(&sh, data, sh.sh_size, TBL[j].va);
				if(sh.sh_size != 0)
					free(data);
				
			}
		}
		data = (uint8_t*) malloc(ph.p_filesz);
		if(data == NULL){
			printf("Could not alloc %lu bytes\n", ph.p_filesz);
			break;
		}
		fseek(fp, ph.p_offset, SEEK_SET);
		fread((void*) data, ph.p_filesz, 1, fp);
		disassemble(handle, insn, data, ph.p_filesz, ph.p_vaddr);
		free(data);

	}
	for(j=0;j<elf.e_shnum-1;j++){
		if(TBL[j].used == 0){
			TBL[j].used++;
			fseek(fp, TBL[j].off, SEEK_SET);
			fread((void*) &sh, sizeof(SHDR), 1, fp);
			revert_shdr(&sh);
			if(sh.sh_size != 0)
				data = (uint8_t*) malloc(sh.sh_size);
			else
				data = NULL;
			disassemble_data(&sh, data, sh.sh_size, TBL[j].va);
			if(sh.sh_size != 0)
				free(data);
			
		}
	}

end:
	if(TBL)
		free(TBL);
	cs_close(&handle);
}

int main(int argc, char** argv){
	if(argc == 2){
		fp = fopen(argv[1], "rb");
		if(!fp){
			printf("Could not open '%s'\n", argv[0]);
			return 1;
		}
		exec();
		fclose(fp);
	}else {
		printf("usage: %s file.elf\n", argv[0]);
		return 1;
	}

	return 0;
}
