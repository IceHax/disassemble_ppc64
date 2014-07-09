#ifndef __DISSASSEBLE_PPC64_PRINTER_H__
#define __DISSASSEBLE_PPC64_PRINTER_H__

#include <inttypes.h>
#include "elf.h"

void print_elf(ELF* elf);
void print_phdr(PHDR* ph, uint16_t i);
void print_shdr(SHDR* sh, uint16_t i);
#endif
