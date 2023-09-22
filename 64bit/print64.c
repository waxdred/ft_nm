#include "../include.h"
#include <ctype.h>
#include <stdio.h>

void PrintNm32(SymbolNode *head, t_flag flag) {
  SymbolNode *current = head;
  if (flag.r) {
    SymbolNode *reversed = reverse_list(head);
    current = reversed;
  }
  while (current) {
    if (flag.u) {
      if (current->address == ULONG_MAX && current->type != 'A')
        printf("                 %c %s\n", current->type, current->name);
    } else if (current->type != 'A') {
      if (current->address != ULONG_MAX) {
        if (flag.g && isupper(current->type)) {
          printf("%08lx %c %s\n", current->address, current->type,
                 current->name);

        } else if (!flag.g)
          printf("%08lx %c %s\n", current->address, current->type,
                 current->name);
      } else {
        if (flag.g && isupper(current->type))
          printf("         %c %s\n", current->type, current->name);
        else if (!flag.g)
          printf("         %c %s\n", current->type, current->name);
      }
    } else if (current->type == 'A' && flag.a) {
      printf("00000000 %c %s\n", tolower(current->type), current->name);
    }
    current = current->next;
  }
}

void PrintNoSymbol(const char *prog) { printf("nm: %s: no symbols\n", prog); }
