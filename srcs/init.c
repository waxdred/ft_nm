#include "../includes/nm.h"

t_nm *get_nm(t_nm *nm) {
  static t_nm *save;
  if (nm != NULL) {
    save = nm;
  }
  return save;
}

t_nm *init_nm(void) {
  t_nm *nm = (t_nm *)malloc(sizeof(t_nm));
  if (nm == NULL) {
    return NULL;
  }
  bzero(nm, sizeof(t_nm));
  nm->Set_Elf = &set_elf;
  get_nm(nm);
  return nm;
}

void set_elf() {
  t_nm *nm = get_nm(NULL);
  nm->AddNode = &AddNode;
  nm->InitElf = &InitElf;
  nm->Free_list = &free_symbol_list;
  nm->List_symbols = &list_symbols;
}

void InitElf(void *map) {
  t_nm *nm = get_nm(NULL);
  nm->map = map;
  if (nm->flags.elf & ELF32) {
    nm->elf32.hdr = (Elf32_Ehdr *)map;
    nm->elf32.shdr = (Elf32_Shdr *)((char *)map + nm->elf32.hdr->e_shoff);
    nm->ParseTable = &ParseTable32;
  } else if (nm->flags.elf & ELF64) {
    nm->elf64.hdr = (Elf64_Ehdr *)map;
    nm->elf64.shdr = (Elf64_Shdr *)((char *)map + nm->elf64.hdr->e_shoff);
    nm->ParseTable = &ParseTable64;
  } else {
    printf("Erreur\n");
    return;
  }
  if (nm->flags.elf & B_ENDIAN) {
    nm->endian = B_ENDIAN;
  } else {
    nm->endian = L_ENDIAN;
  }
}
