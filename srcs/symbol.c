#include "../includes/nm.h"

char get_symbol_type_32(Elf32_Sym *sym, Elf32_Shdr *shdr) {
  char type = ' ';
  unsigned char bind = ELF32_ST_BIND(sym->st_info);

  if (sym->st_shndx == SHN_UNDEF) {
    if (bind == STB_WEAK) {
      type = 'W';
    } else {
      type = 'U';
    }
  } else if (sym->st_shndx == SHN_ABS) {
    type = 'A';
  } else if (sym->st_shndx == SHN_COMMON) {
    type = 'C';
  } else {
    switch (shdr[sym->st_shndx].sh_type) {
    case SHT_PROGBITS:
      if (shdr[sym->st_shndx].sh_flags & SHF_WRITE) {
        type = 'D';
      } else {
        type = 'R';
      }
      break;
    case SHT_NOBITS:
      type = 'B';
      break;
    case SHT_DYNAMIC:
      type = 'D';
      break;
    }

    if (shdr[sym->st_shndx].sh_flags & SHF_EXECINSTR) {
      type = 'T';
    }

    if (bind == STB_WEAK) {
      if (type == 'D') {
        type = 'W';
      } else if (type == 'T') {
        type = 't';
      }
    }
    if (bind == STB_LOCAL) {
      if (type >= 'A' && type <= 'Z')
        type += 32;
    }
  }
  return type;
}

char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr) {
  char type = ' ';
  unsigned char bind = ELF64_ST_BIND(sym->st_info);

  if (sym->st_shndx == SHN_UNDEF) {
    if (bind == STB_WEAK) {
      type = 'W';
    } else {
      type = 'U';
    }
  } else if (sym->st_shndx == SHN_ABS) {
    type = 'A';
  } else if (sym->st_shndx == SHN_COMMON) {
    type = 'C';
  } else {
    switch (shdr[sym->st_shndx].sh_type) {
    case SHT_PROGBITS:
      if (shdr[sym->st_shndx].sh_flags & SHF_WRITE) {
        type = 'D';
      } else {
        type = 'R';
      }
      break;
    case SHT_NOBITS:
      type = 'B';
      break;
    case SHT_DYNAMIC:
      type = 'D';
      break;
    }

    if (shdr[sym->st_shndx].sh_flags & SHF_EXECINSTR) {
      type = 'T';
    }

    if (bind == STB_WEAK) {
      if (type == 'D') {
        type = 'W';
      } else if (type == 'T') {
        type = 't';
      }
    }
    if (bind == STB_LOCAL) {
      if (type >= 'A' && type <= 'Z')
        type += 32;
    }
  }
  return type;
}
