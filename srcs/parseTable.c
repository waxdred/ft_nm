#include "../includes/nm.h"

void ParseTable32() {
  t_nm *nm = get_nm(NULL);
  void *map = get_nm(NULL)->map;
  t_elf32 elf = get_nm(NULL)->elf32;
  Elf32_Ehdr *ehdr = (Elf32_Ehdr *)map;
  Elf32_Shdr *shdr = (Elf32_Shdr *)(map + ehdr->e_shoff);
  Elf32_Shdr *sh_strtab = &shdr[ehdr->e_shstrndx];
  const char *const sh_strtab_p = map + sh_strtab->sh_offset;
  unsigned long i, j;
  for (i = 0; i < elf.hdr->e_shnum; i++) {
    if (elf.shdr[i].sh_type == SHT_SYMTAB) {
      elf.symtab = (Elf32_Sym *)((char *)map + elf.shdr[i].sh_offset);
      elf.symstrtab = (char *)map + elf.shdr[elf.shdr[i].sh_link].sh_offset;
      for (j = 0; j < (elf.shdr[i].sh_size / sizeof(Elf32_Sym)); j++) {
        if (elf.symtab[j].st_name != 0) {
          uint64_t st_value = elf.symtab[j].st_value;
          if (nm->endian == B_ENDIAN) {
            st_value = swap_uint64(st_value);
          }
          uint64_t st_name_offset = elf.symtab[j].st_name;
          if (nm->endian == B_ENDIAN) {
            st_name_offset = swap_uint64(st_name_offset);
          }
          char type = get_symbol_type_32(
              &elf.symtab[j], elf.shdr, &elf.symstrtab[st_name_offset],
              (char *)(sh_strtab_p + shdr[i].sh_name));
          AddNode(&nm->head, st_value, type, &elf.symstrtab[st_name_offset]);
        }
      }
    }
  }
}

void ParseTable64() {
  t_nm *nm = get_nm(NULL);
  void *map = get_nm(NULL)->map;
  t_elf64 elf = get_nm(NULL)->elf64;
  Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
  Elf64_Shdr *shdr = (Elf64_Shdr *)(map + ehdr->e_shoff);
  Elf64_Shdr *sh_strtab = &shdr[ehdr->e_shstrndx];
  const char *const sh_strtab_p = map + sh_strtab->sh_offset;
  unsigned long i, j;
  for (i = 0; i < elf.hdr->e_shnum; i++) {
    if (elf.shdr[i].sh_type == SHT_SYMTAB) {
      elf.symtab = (Elf64_Sym *)((char *)map + elf.shdr[i].sh_offset);
      elf.symstrtab = (char *)map + elf.shdr[elf.shdr[i].sh_link].sh_offset;
      for (j = 0; j < (elf.shdr[i].sh_size / sizeof(Elf64_Sym)); j++) {
        if (elf.symtab[j].st_name != 0) {
          uint64_t st_value = elf.symtab[j].st_value;
          if (nm->endian == B_ENDIAN) {
            st_value = swap_uint64(st_value);
          }
          uint64_t st_name_offset = elf.symtab[j].st_name;
          if (nm->endian == B_ENDIAN) {
            st_name_offset = swap_uint64(st_name_offset);
          }
          char type = get_symbol_type(&elf.symtab[j], elf.shdr,
                                      &elf.symstrtab[st_name_offset],
                                      (char *)(sh_strtab_p + shdr[i].sh_name));
          AddNode(&nm->head, st_value, type, &elf.symstrtab[st_name_offset]);
        }
      }
    }
  }
}
