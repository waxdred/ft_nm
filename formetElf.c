#include "include.h"

int get_format(void *map) {
  Elf32_Ehdr *elf_hdr = (Elf32_Ehdr *)map;
  char c = elf_hdr->e_ident[EI_CLASS];
  if (c == ELFCLASS32)
    return 32;
  else if (c == ELFCLASS64)
    return 64;
  else
    return -1;
}
