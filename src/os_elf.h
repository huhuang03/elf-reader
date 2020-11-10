//
// Created by huhua on 2020/9/17.
//

#ifndef ELF_READER_ELF_H
#define ELF_READER_ELF_H

#include <cstdint>

/* Myself define */
typedef uint32_t __u32;
typedef uint8_t __u16;
typedef int32_t  __s32;
typedef uint64_t __u64;
typedef int16_t __s16;
typedef int64_t __s64;

/* 32-bit ELF base types. */
typedef __u32	Elf32_Addr;
typedef __u16	Elf32_Half;
typedef __u32	Elf32_Off;
typedef __s32	Elf32_Sword;
typedef __u32	Elf32_Word;

/* 64-bit ELF base types. */
typedef __u64	Elf64_Addr;
typedef __u16	Elf64_Half;
typedef __s16	Elf64_SHalf;
typedef __u64	Elf64_Off;
typedef __s32	Elf64_Sword;
typedef __u32	Elf64_Word;
typedef __u64	Elf64_Xword;
typedef __s64	Elf64_Sxword;

/* These constants are for the segment types stored in the image headers */
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_TLS     7               /* Thread local storage segment */
#define PT_LOOS    0x60000000      /* OS-specific */
#define PT_HIOS    0x6fffffff      /* OS-specific */
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff
#define PT_GNU_EH_FRAME		0x6474e550
#define PT_GNU_PROPERTY		0x6474e553

#define PT_GNU_STACK	(PT_LOOS + 0x474e551)

#define EI_NIDENT	16

typedef struct elf32_hdr {
    unsigned char	e_ident[EI_NIDENT];
    Elf32_Half	e_type;
    Elf32_Half	e_machine;
    Elf32_Word	e_version;
    Elf32_Addr	e_entry;  /* Entry point */
    Elf32_Off	e_phoff;
    Elf32_Off	e_shoff;
    Elf32_Word	e_flags;
    Elf32_Half	e_ehsize;
    Elf32_Half	e_phentsize;
    Elf32_Half	e_phnum;
    Elf32_Half	e_shentsize;
    Elf32_Half	e_shnum;
    Elf32_Half	e_shstrndx;
} Elf32_Ehdr;

typedef struct elf64_hdr {
    unsigned char	e_ident[EI_NIDENT];	/* ELF "magic number" */
    Elf64_Half e_type;
    Elf64_Half e_machine;
    Elf64_Word e_version;
    Elf64_Addr e_entry;		/* Entry point virtual address */
    Elf64_Off e_phoff;		/* Program header table file offset */
    Elf64_Off e_shoff;		/* Section header table file offset */
    Elf64_Word e_flags;
    Elf64_Half e_ehsize;
    Elf64_Half e_phentsize;
    Elf64_Half e_phnum;
    Elf64_Half e_shentsize;
    Elf64_Half e_shnum;
    Elf64_Half e_shstrndx;
} Elf64_Ehdr;

typedef struct elf32_shdr {
    Elf32_Word	sh_name;
    Elf32_Word	sh_type;
    Elf32_Word	sh_flags;
    Elf32_Addr	sh_addr;
    Elf32_Off	sh_offset;
    Elf32_Word	sh_size;
    Elf32_Word	sh_link;
    Elf32_Word	sh_info;
    Elf32_Word	sh_addralign;
    Elf32_Word	sh_entsize;
} Elf32_Shdr;

typedef struct elf64_shdr {
    Elf64_Word sh_name;		/* Section name, index in string tbl */
    Elf64_Word sh_type;		/* Type of section */
    Elf64_Xword sh_flags;		/* Miscellaneous section attributes */
    Elf64_Addr sh_addr;		/* Section virtual addr at execution */
    Elf64_Off sh_offset;		/* Section file offset */
    Elf64_Xword sh_size;		/* Size of section in bytes */
    Elf64_Word sh_link;		/* Index of another section */
    Elf64_Word sh_info;		/* Additional section information */
    Elf64_Xword sh_addralign;	/* Section alignment */
    Elf64_Xword sh_entsize;	/* Entry size if section holds table */
} Elf64_Shdr;

#endif //ELF_READER_ELF_H
