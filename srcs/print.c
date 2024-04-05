#include "../includes/nm.h"

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
          printf("%016lx %c %s\n", current->address, current->type,
                 current->name);

        } else if (!flag.g)
          printf("%016lx %c %s\n", current->address, current->type,
                 current->name);
      } else {
        if (flag.g && isupper(current->type))
          printf("                 %c %s\n", current->type, current->name);
        else if (isPrt(current->type)) {
          printf("0000000000000000 %c %s\n", current->type, current->name);
        } else if (!flag.g)
          printf("                 %c %s\n", current->type, current->name);
      }
      current = current->next;
    }
  }
}
