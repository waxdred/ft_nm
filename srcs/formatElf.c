#include "../includes/nm.h"

int get_format(void *map) {
  Elf32_Ehdr *elf_hdr = (Elf32_Ehdr *)map;
  char c = elf_hdr->e_ident[EI_CLASS];
  int flags = 0;
  if (c == ELFCLASS32) {
    flags = ELF32;
    if (elf_hdr->e_ident[EI_DATA] == ELFDATA2LSB) {
      // Little-endian
      flags |= L_ENDIAN;
    } else if (elf_hdr->e_ident[EI_DATA] == ELFDATA2MSB) {
      // Big-endian
      flags |= B_ENDIAN;
    }
  } else if (c == ELFCLASS64) {
    flags = ELF64;
    if (elf_hdr->e_ident[EI_DATA] == ELFDATA2LSB) {
      printf("Little-endian\n");
      // Little-endian
      flags |= L_ENDIAN;
    } else if (elf_hdr->e_ident[EI_DATA] == ELFDATA2MSB) {
      // Big-endian
      printf("Big-endian\n");
      flags |= B_ENDIAN;
    }
  }
  return flags;
}
