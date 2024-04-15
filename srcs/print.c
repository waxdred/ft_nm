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

void PrintNm(SymbolNode *head, t_flag flag) {
  SymbolNode *current = head;
  t_nm *nm = get_nm(NULL);
  while (current) {
    if (flag.u) {
      if (flag.a) {
        printf("%s:", nm->flags.file);
      }
      if (current->address == ULONG_MAX && current->type != 'A') {
        if (nm->type == ELF64)
          printf("                 %c %s%s\n", current->type,
                 current->unscore == NO_UNDER_SCORE ? ""
                 : current->unscore == UNDER_SCORE  ? "_"
                                                    : "__",
                 current->name);
        else if (nm->type == ELF32)
          printf("         %c %s%s\n", current->type,
                 current->unscore == NO_UNDER_SCORE ? ""
                 : current->unscore == UNDER_SCORE  ? "_"
                                                    : "__",
                 current->name);
      }
    } else if (current->type != 'A') {
      if (current->address != ULONG_MAX) {
        if (flag.a) {
          printf("%s:", nm->flags.file);
        }
        if (nm->type == ELF64) {
          if (flag.g && isupper(current->type)) {
            printf("%016lx %c %s%s\n", current->address, current->type,
                   current->unscore == NO_UNDER_SCORE ? ""
                   : current->unscore == UNDER_SCORE  ? "_"
                                                      : "__",
                   current->name);
          } else if (!flag.g) {
            printf("%016lx %c %s%s\n", current->address, current->type,
                   current->unscore == NO_UNDER_SCORE ? ""
                   : current->unscore == UNDER_SCORE  ? "_"
                                                      : "__",
                   current->name);
          }
        } else if (nm->type == ELF32) {
          if (flag.g && isupper(current->type)) {
            printf("%08lx %c %s%s\n",
                   (unsigned long)(current->address & 0xFFFFFFFF),
                   current->type,
                   current->unscore == NO_UNDER_SCORE ? ""
                   : current->unscore == UNDER_SCORE  ? "_"
                                                      : "__",
                   current->name);
          } else if (!flag.g) {
            printf("%08lx %c %s%s\n",
                   (unsigned long)(current->address & 0xFFFFFFFF),
                   current->type,
                   current->unscore == NO_UNDER_SCORE ? ""
                   : current->unscore == UNDER_SCORE  ? "_"
                                                      : "__",
                   current->name);
          }
        }
      } else {
        if (flag.g && isupper(current->type)) {
          if (flag.a) {
            printf("%s:", nm->flags.file);
          }
          if (nm->type == ELF64) {
            printf("                 %c %s%s\n", current->type,
                   current->unscore == NO_UNDER_SCORE ? ""
                   : current->unscore == UNDER_SCORE  ? "_"
                                                      : "__",
                   current->name);
          } else if (nm->type == ELF32) {
            printf("         %c %s\n", current->type, current->name);
          }
        } else if (isPrt(current->type)) {
          if (flag.a) {
            printf("%s:", nm->flags.file);
          }
          if (nm->type == ELF64)
            printf("0000000000000000 %c %s%s\n", current->type,
                   current->unscore == NO_UNDER_SCORE ? ""
                   : current->unscore == UNDER_SCORE  ? "_"
                                                      : "__",
                   current->name);
          else if (nm->type == ELF32)
            printf("00000000 %c %s%s\n", current->type,
                   current->unscore == NO_UNDER_SCORE ? ""
                   : current->unscore == UNDER_SCORE  ? "_"
                                                      : "__",
                   current->name);
        } else if (!flag.g) {
          if (flag.a) {
            printf("%s:", nm->flags.file);
          }
          if (nm->type == ELF64)
            printf("                 %c %s%s\n", current->type,
                   current->unscore == NO_UNDER_SCORE ? ""
                   : current->unscore == UNDER_SCORE  ? "_"
                                                      : "__",
                   current->name);
          else if (nm->type == ELF32)
            printf("         %c %s%s\n", current->type,
                   current->unscore == NO_UNDER_SCORE ? ""
                   : current->unscore == UNDER_SCORE  ? "_"
                                                      : "__",
                   current->name);
        }
      }
    }
    current = current->next;
  }
}
