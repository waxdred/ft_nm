#include "../includes/nm.h"
#include <stdio.h>

#define DEBUG 0

#define NAME "environ"

char get_symbol_type_32(Elf32_Sym *sym, Elf32_Shdr *shdr, char *name,
                        char *section_name) {
  int TEST = ft_strcmp(name, NAME) == 0 ? 1 : 0;
  static int i = 0;
  char type = ' ';
  unsigned char bind = ELF32_ST_BIND(sym->st_info);

  if (TEST && DEBUG) {
    printf("32\n");
    printf("sh_name: %s\n", name);
    printf("i = %d\n", i);
    printf("sym->st_shndx: %d, bind = %d\n", sym->st_shndx, bind);
    printf("shdr[sym->st_shndx].sh_type: %d\n", shdr[sym->st_shndx].sh_type);
    printf("shdr[sym->st_shndx].sh_flags: %d\n", shdr[sym->st_shndx].sh_flags);
    printf("sym->st_value: %d\n", sym->st_value);
    // print section name
    printf("section_name: %s\n", section_name);
    sleep(1);
  }
  if (sym->st_shndx == SHN_UNDEF) {
    if (bind == STB_WEAK) {
      type = 'w';
    } else {
      type = 'U';
    }
  } else if (sym->st_shndx == SHN_ABS) {
    type = 'A'; // absolute symbol
  } else if (sym->st_shndx == SHN_COMMON) {
    type = 'C'; // common symbol
  } else {
    switch (shdr[sym->st_shndx].sh_type) {
    case SHT_PREINIT_ARRAY:
      type = 'D'; // read-only
      break;
    case SHT_NOTE:
      type = 'r'; // read-only data
      break;
    case SHT_FINI_ARRAY:
      type = 'd'; // writable data
      break;
    case SHT_INIT_ARRAY:
      type = 'd'; // writable data
      break;
    case SHT_PROGBITS:
      if (shdr[sym->st_shndx].sh_flags & SHF_WRITE) {
        if (bind == STB_WEAK)
          type = 'V';
        else
          type = 'D'; // writable data
      } else if (shdr[sym->st_shndx].sh_flags & SHF_EXECINSTR) {
        type = 'T'; // Executable Code
      } else {
        type = 'R'; // Read-only Data
      }
      break;
    case SHT_NOBITS:
      if (shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) {
        if (bind == STB_LOCAL || bind == STB_GLOBAL)
          type = 'B';
        if (bind == STB_WEAK)
          type = 'V'; // uninitialized data
      } else if (shdr[sym->st_shndx].sh_flags & SHF_WRITE) {
        type = 'B'; // uninitialized data
      } else {
        type = 'R'; // Read-only Data
      }
      break;
    case SHT_DYNAMIC:
      type = 'D'; // writable data
      break;
    }

    if (shdr[sym->st_shndx].sh_flags & SHF_EXECINSTR) {
      type = 'T'; // Code(text)object
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
  if (TEST && DEBUG) {
    printf("type = %c\n", type);
  }
  return type;
}

char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr, char *name,
                     char *section_name) {
  int TEST = ft_strcmp(name, NAME) == 0 ? 1 : 0;
  static int i = 0;
  char type = ' ';
  unsigned char bind = ELF64_ST_BIND(sym->st_info);

  // TODO found 'r' and 'd'
  //
  if (TEST && DEBUG) {
    // print name of the section
    printf("sh_name: %s\n", name);
    printf("i = %d\n", i);
    printf("sym->st_shndx: %d, bind = %c\n", sym->st_shndx, bind);
    printf("shdr[sym->st_shndx].sh_type: %d\n", shdr[sym->st_shndx].sh_type);
    printf("section_name: %s\n", section_name);
    sleep(1);
  }

  if (sym->st_shndx == SHN_UNDEF) {
    if (bind == STB_WEAK) {
      type = 'w';
    } else {
      type = 'U';
    }
  } else if (sym->st_shndx == SHN_ABS) {
    type = 'A'; // absolute symbol
  } else if (sym->st_shndx == SHN_COMMON) {
    type = 'C'; // common symbol
  } else {
    switch (shdr[sym->st_shndx].sh_type) {
    case SHT_NOTE:
      type = 'r'; // read-only data
      break;
    case SHT_FINI_ARRAY:
      type = 'd'; // writable data
      break;
    case SHT_INIT_ARRAY:
      type = 'd'; // writable data
      break;
    case SHT_PROGBITS:
      if (shdr[sym->st_shndx].sh_flags & SHF_WRITE) {
        type = 'D'; // writable data
      } else if (shdr[sym->st_shndx].sh_flags & SHF_EXECINSTR) {
        type = 'T'; // Executable Code
      } else {
        type = 'R'; // Read-only Data
      }
      break;
    case SHT_NOBITS:
      if (shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) {
        type = 'V'; // uninitialized data
      } else if (shdr[sym->st_shndx].sh_flags & SHF_WRITE) {
        type = 'B'; // uninitialized data
      } else {
        type = 'R'; // Read-only Data
      }
      break;
    case SHT_DYNAMIC:
      type = 'D'; // writable data
      break;
    case SHT_PREINIT_ARRAY:
      type = 'D'; // read-only
      break;
    }

    if (shdr[sym->st_shndx].sh_flags & SHF_EXECINSTR) {
      type = 'T'; // Code(text)object
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
  i++;
  return type;
}
