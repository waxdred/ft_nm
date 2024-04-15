#include "../includes/nm.h"
#include <stdio.h>

int isPrt(char c) {
  char *str = "RrDTW";
  while (*str) {
    if (*str == c)
      return 1;
    str++;
  }
  return 0;
}

char *getPrefix(int prefix) {
  switch (prefix) {
  case NO_UNDER_SCORE:
    return "";
  case UNDER_SCORE:
    return "_";
  case DOUBLE_UNDER_SCORE:
    return "__";
  case TRIPLE_UNDER_SCORE:
    return "___";
  case DOT:
    return ".";
  }
  return "";
}

void printFlaga(t_flag flag) {
  if (flag.a) {
    printf("%s:\n", get_nm(NULL)->flags.file);
  }
}

void printNode(SymbolNode *current, t_flag flag, t_nm *nm) {
  if (current) {
    if (flag.u) {
    } else if (current->type == 'A' && current->address != ULONG_MAX) {
      printFlaga(flag);
      if (nm->type == ELF64)
        printf("%016lx %c %s%s\n", current->address, current->type,
               getPrefix(current->unscore), current->name);
      else if (nm->type == ELF32)
        printf("%08lx %c %s%s\n",
               (unsigned long)(current->address & 0xFFFFFFFF), current->type,
               getPrefix(current->unscore), current->name);

    } else if (current->type != 'A') {
      if (current->address != ULONG_MAX) {
        printFlaga(flag);
        if (nm->type == ELF64) {
          if (flag.g && isupper(current->type)) {
            printf("%016lx %c %s%s\n", current->address, current->type,
                   getPrefix(current->unscore), current->name);
          } else if (!flag.g) {
            printf("%016lx %c %s%s\n", current->address, current->type,
                   getPrefix(current->unscore), current->name);
          }
        } else if (nm->type == ELF32) {
          if (flag.g && isupper(current->type)) {
            printf("%08lx %c %s%s\n",
                   (unsigned long)(current->address & 0xFFFFFFFF),
                   current->type, getPrefix(current->unscore), current->name);
          } else if (!flag.g) {
            printf("%08lx %c %s%s\n",
                   (unsigned long)(current->address & 0xFFFFFFFF),
                   current->type, getPrefix(current->unscore), current->name);
          }
        }
      } else {
        if (flag.g && isupper(current->type)) {
          printFlaga(flag);
          if (nm->type == ELF64) {
            printf("                 %c %s%s\n", current->type,
                   getPrefix(current->unscore), current->name);
          } else if (nm->type == ELF32) {
            printf("         %c %s\n", current->type, current->name);
          }
        } else if (isPrt(current->type)) {
          printFlaga(flag);
          if (nm->type == ELF64)
            printf("0000000000000000 %c %s%s\n", current->type,
                   getPrefix(current->unscore), current->name);
          else if (nm->type == ELF32)
            printf("00000000 %c %s%s\n", current->type,
                   getPrefix(current->unscore), current->name);
        } else if (!flag.g) {
          printFlaga(flag);
          if (nm->type == ELF64)
            printf("                 %c %s%s\n", current->type,
                   getPrefix(current->unscore), current->name);
          else if (nm->type == ELF32)
            printf("         %c %s%s\n", current->type,
                   getPrefix(current->unscore), current->name);
        }
      }
    }
  }
}

void PrintNm(SymbolNode *head, t_flag flag) {
  SymbolNode *current = head;
  t_nm *nm = get_nm(NULL);
  while (current) {
    printNode(current, flag, nm);
    SymbolNode *tmp = current->duplicate;
    while (tmp) {
      printNode(tmp, flag, nm);
      tmp = tmp->duplicate;
    }
    current = current->next;
  }
}
