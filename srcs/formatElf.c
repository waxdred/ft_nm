#include "../includes/nm.h"

int get_format(void *map) {
  Elf32_Ehdr *elf_hdr = (Elf32_Ehdr *)map;
  char c = elf_hdr->e_ident[EI_CLASS];
  int flags = 0;
  if (elf_hdr->e_ident[EI_MAG0] != ELFMAG0 ||
      elf_hdr->e_ident[EI_MAG1] != ELFMAG1 ||
      elf_hdr->e_ident[EI_MAG2] != ELFMAG2 ||
      elf_hdr->e_ident[EI_MAG3] != ELFMAG3) {
    // La séquence magique ELF n'est pas présente, fichier invalide
    return 0;
  }
  if (c == ELFCLASS32 && sizeof(map) < sizeof(Elf32_Ehdr)) {
    flags = ELF32;
    if (elf_hdr->e_ident[EI_DATA] == ELFDATA2LSB) {
      // Little-endian
      flags |= L_ENDIAN;
    } else if (elf_hdr->e_ident[EI_DATA] == ELFDATA2MSB) {
      // Big-endian
      flags |= B_ENDIAN;
    }
  } else if (c == ELFCLASS64 && sizeof(map) < sizeof(Elf64_Ehdr)) {
    flags = ELF64;
    if (elf_hdr->e_ident[EI_DATA] == ELFDATA2LSB) {
      // Little-endian
      flags |= L_ENDIAN;
    } else if (elf_hdr->e_ident[EI_DATA] == ELFDATA2MSB) {
      // Big-endian
      flags |= B_ENDIAN;
    }
  }
  return flags;
}
