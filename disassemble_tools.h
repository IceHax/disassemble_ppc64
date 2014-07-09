#ifndef __DISSASSEBLE_PPC64_TOOLS_H__
#define __DISSASSEBLE_PPC64_TOOLS_H__
#include <stdio.h>
#include <inttypes.h>
#include <capstone/capstone.h>
#include "elf.h"

typedef struct _va_tbl{
	uint64_t va;	/* sh virtual addr */
	uint64_t off;   /* file offset of shdr struct */
	uint32_t used;
} va_tbl;

void disassemble(csh handle, cs_insn *insn, uint8_t *data, size_t size, uint64_t addr);
void disassemble_data(SHDR* sh, uint8_t* data, size_t size, uint64_t offset);

void revert_elf(ELF* elf);
void revert_phdr(PHDR* ph);
void revert_shdr(SHDR* sh);

#endif
