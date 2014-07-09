#ifndef __DISSASSEBLE_PPC64_ELF_H__
#define __DISSASSEBLE_PPC64_ELF_H__
#include <inttypes.h>
#include "little_endian.h"
/* ELF Flags */

#define ELF_MAGIC	0x464c457f // LE: 0x7f454c46u

#define EM_PPC		20	// 32-bit PowerPC
#define EM_PPC64 	21	// 64-bit PowerPC

typedef struct _ELF{
	uint8_t e_ident[16];              /* ELF identification */
	uint16_t e_type;                  /* object file type */
	uint16_t e_machine;               /* machine type */
	uint32_t e_version;               /* object file version */
	uint64_t e_entry;                 /* entry point address */
	uint64_t e_phoff;                 /* program header offset */
	uint64_t e_shoff;                 /* section header offset */
	uint16_t e_flags;                 /* processor-specific flags */
	uint32_t e_ehsize;                /* ELF header size */
	uint16_t e_phentsize;             /* size of program header entry */
	uint16_t e_phnum;                 /* number of program header entries */
	uint16_t e_shentsize;             /* size of section header entry */
	uint16_t e_shnum;                 /* number of section header entries */
	uint16_t e_shstrndx;              /* section name string table index */
} __attribute__((packed)) ELF;

typedef struct _PHDR{
	uint32_t p_type;                  /* type of segment */
	uint32_t p_flags;                 /* segment attributes */
	uint64_t p_offset;                /* offset in file */
	uint64_t p_vaddr;                 /* virtual address in memory */
	uint64_t p_paddr;                 /* reserved */
	uint64_t p_filesz;                /* size of segment in file */
	uint64_t p_memsz;                 /* size of segment in memory */
	uint64_t p_align;                 /* alignment of segment */
} __attribute__((packed)) PHDR;

/* Section Flags */
/* sh_type */
#define SHT_NULL 		0
#define SHT_PROGBITS 		1
#define SHT_SYMTAB 		2
#define SHT_STRTAB 		3
#define SHT_RELA 		4
#define SHT_HASH 		5
#define SHT_DYNAMIC	 	6
#define SHT_NOTE 		7
#define SHT_NOBITS	 	8
#define SHT_REL 		9
#define SHT_SHLIB 		10
#define SHT_DYNSYM 		11
#define SHT_INIT_ARRAY 		14
#define SHT_FINI_ARRAY	 	15
#define SHT_PREINIT_ARRAY 	16
#define SHT_GROUP 		17
#define SHT_SYMTAB_SHNDX 	18
#define SHT_LOOS 		0x60000000
#define SHT_HIOS 		0x6fffffff
#define SHT_LOPROC 		0x70000000
#define SHT_HIPROC 		0x7fffffff
#define SHT_LOUSER 		0x80000000
#define SHT_HIUSER 		0xffffffff
/* sh_flags */

#define SHF_WRITE 		0x1
#define SHF_ALLOC 		0x2
#define SHF_EXECINSTR 		0x4
#define SHF_MERGE 		0x10
#define SHF_STRINGS 		0x20
#define SHF_INFO_LINK 		0x40
#define SHF_LINK_ORDER 		0x80
#define SHF_OS_NONCONFORMING 	0x100
#define SHF_GROUP 		0x200
#define SHF_TLS 		0x400
#define SHF_COMPRESSED 		0x800
#define SHF_MASKOS 		0x0ff00000
#define SHF_MASKPROC 		0xf0000000
#define SHF_NOT_DEFINED		0xffffffff/* This is for the missing section */


typedef struct _SHDR{
	uint32_t sh_name;                 /* section name */
	uint32_t sh_type;                 /* section type */
	uint64_t sh_flags;                /* section attributes */
	uint64_t sh_addr;                 /* virtual address in memory */
	uint64_t sh_offset;               /* offset in file */
	uint64_t sh_size;                 /* size of section */
	uint32_t sh_link;                 /* link to other section */
	uint32_t sh_info;                 /* miscellaneous information */
	uint64_t sh_addralign;            /* address alignment boundary */
	uint64_t sh_entsize;              /* size of entries, if section has table */
} __attribute__((packed)) SHDR;

typedef struct _Sections{
	const char*    name;
	const uint32_t type;
	const uint32_t flags;
	uint16_t       used;
} Sections;


static Sections special_section [] = {
	{".bss",		SHT_NOBITS,		SHF_ALLOC+SHF_WRITE,			0},
	{".comment",		SHT_PROGBITS,		0,					0},
	{".data",		SHT_PROGBITS,		SHF_ALLOC+SHF_WRITE,			0},
	{".data1",		SHT_PROGBITS,		SHF_ALLOC+SHF_WRITE,			0},
	{".debug",		SHT_PROGBITS,		0,					0},
	{".dynamic",		SHT_DYNAMIC,		SHF_NOT_DEFINED,			0},
	{".dynstr",		SHT_STRTAB,		SHF_ALLOC,				0},
	{".dynsym",		SHT_DYNSYM,		SHF_ALLOC,				0},
	{".fini",		SHT_PROGBITS,		SHF_ALLOC+SHF_EXECINSTR,		0},
	{".fini_array",		SHT_FINI_ARRAY,		SHF_ALLOC+SHF_WRITE,			0},
	{".got",		SHT_PROGBITS,		SHF_NOT_DEFINED,			0},
	{".hash",		SHT_HASH,		SHF_ALLOC,				0},
	{".init",		SHT_PROGBITS,		SHF_ALLOC+SHF_EXECINSTR,		0},
	{".init_array",		SHT_INIT_ARRAY,		SHF_ALLOC+SHF_WRITE,			0},
	{".interp",		SHT_PROGBITS,		SHF_NOT_DEFINED,			0},
	{".line",		SHT_PROGBITS,		0,					0},
	{".note",		SHT_NOTE,		0,					0},
	{".plt",		SHT_PROGBITS,		SHF_NOT_DEFINED,			0},
	{".preinit_array",	SHT_PREINIT_ARRAY,	SHF_ALLOC+SHF_WRITE,			0},
	{".relname",		SHT_REL,		SHF_NOT_DEFINED,			0},
	{".relaname",		SHT_RELA,		SHF_NOT_DEFINED,			0},
	{".rodata",		SHT_PROGBITS,		SHF_ALLOC,				0},
	{".rodata1",		SHT_PROGBITS,		SHF_ALLOC,				0},
	{".shstrtab",		SHT_STRTAB,		0,					0},
	{".strtab",		SHT_STRTAB,		SHF_NOT_DEFINED,			0},
	{".symtab",		SHT_SYMTAB,		SHF_NOT_DEFINED,			0},
	{".symtab_shndx",	SHT_SYMTAB_SHNDX,	SHF_NOT_DEFINED,			0},
	{".tbss",		SHT_NOBITS,		SHF_ALLOC+SHF_WRITE+SHF_TLS,		0},
	{".tdata",		SHT_PROGBITS,		SHF_ALLOC+SHF_WRITE+SHF_TLS,		0},
	{".tdata1",		SHT_PROGBITS,		SHF_ALLOC+SHF_WRITE+SHF_TLS,		0},
	{".text",		SHT_PROGBITS,		SHF_ALLOC+SHF_EXECINSTR+SHF_WRITE,	0},
	{0, 			0, 			0,					0}
};

#endif
