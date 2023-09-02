#include "../include.h"

void list_symbols_64(void *map, t_flag flag) {
  SymbolNode *symbol_list = NULL;
  Elf64_Ehdr *hdr = (Elf64_Ehdr *)map;
  Elf64_Shdr *shdr = (Elf64_Shdr *)((char *)map + hdr->e_shoff);
  char *strtab = (char *)map + shdr[hdr->e_shstrndx].sh_offset;
  Elf64_Sym *symtab;
  char *symstrtab;
  int i, j;

  // Parcourir la table des sections pour trouver la table des symboles
  for (i = 0; i < hdr->e_shnum; i++) {
    if (shdr[i].sh_type == SHT_SYMTAB) {
      symtab = (Elf64_Sym *)((char *)map + shdr[i].sh_offset);
      symstrtab = (char *)map + shdr[shdr[i].sh_link].sh_offset;
      for (j = 0; j < (shdr[i].sh_size / sizeof(Elf64_Sym)); j++) {
        if (symtab[j].st_name != 0) {
          char type = get_symbol_type(&symtab[j], shdr);
          AddNode(&symbol_list, symtab[j].st_value, type,
                  &symstrtab[symtab[j].st_name]);
        }
      }
    }
  }

  SymbolNode *current = symbol_list;
  printf("\n\n\nListe des symboles sort:\n");
  if (flag.p) {
    PrintNm64(current, flag);
  } else {
    Sort(&current, flag);
  }

  free_symbol_list(symbol_list);
}
