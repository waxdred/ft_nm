#include "../include.h"

void list_symbols_32(void *map, t_flag flag) {
  SymbolNode *symbol_list = NULL;
  Elf32_Ehdr *hdr = (Elf32_Ehdr *)map;
  Elf32_Shdr *shdr = (Elf32_Shdr *)((char *)map + hdr->e_shoff);
  char *strtab = (char *)map + shdr[hdr->e_shstrndx].sh_offset;
  Elf32_Sym *symtab;
  char *symstrtab;
  int i, j;

  // Parcourir la table des sections pour trouver la table des symboles
  for (i = 0; i < hdr->e_shnum; i++) {
    if (shdr[i].sh_type == SHT_SYMTAB) {
      symtab = (Elf32_Sym *)((char *)map + shdr[i].sh_offset);
      symstrtab = (char *)map + shdr[shdr[i].sh_link].sh_offset;
      for (j = 0; j < (shdr[i].sh_size / sizeof(Elf32_Sym)); j++) {
        if (symtab[j].st_name != 0) {
          char type = get_symbol_type_32(&symtab[j], shdr);
          AddNode32(&symbol_list, symtab[j].st_value, type,
                    &symstrtab[symtab[j].st_name]);
        }
      }
    }
  }

  SymbolNode *current = symbol_list;
  printf("\n\n\nListe des symboles sort:\n");
  if (flag.p) {
    PrintNm32(current, flag);
  } else {
    Sort(&current, flag);
  }

  free_symbol_list(symbol_list);
}
