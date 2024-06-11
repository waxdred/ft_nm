#include "nm.h"

int isPrt(char c) {
  char *str = "RrDTW";
  while (*str) {
    if (*str == c)
      return 1;
    str++;
  }
  return 0;
}

void printFlaga(t_flag flag) {
  if (flag.a && !flag.j) {
    ft_putstr(get_nm(NULL)->flags.file);
    ft_putstr(": ");
  }
}

void printNode(SymbolNode *current, t_flag flag, t_nm *nm) {
  if (current) {
    if (current->type == 'A' && current->address != ULONG_MAX) {
      printFlaga(flag);
      Print_Line_Addr(current->address, current->type, current->name, nm->type,
                      PRINT_ADDR_SYMBOL);
    } else if (current->type == 'w') {
      printFlaga(flag);
      Print_Line_Addr(current->address, current->type, current->name, nm->type,
                      PRINT_SYMBOL);
    } else if (current->type == 'U') {
      printFlaga(flag);
      Print_Line_Addr(current->address, current->type, current->name, nm->type,
                      PRINT_SYMBOL);
    } else if (current->type != 'A') {
      if (current->address != ULONG_MAX) {
        printFlaga(flag);
        if (nm->type == ELF64) {
          if (flag.g && isupper(current->type)) {
            Print_Line_Addr(current->address, current->type, current->name,
                            nm->type, PRINT_ADDR_SYMBOL);
          } else if (!flag.g) {
            Print_Line_Addr(current->address, current->type, current->name,
                            nm->type, PRINT_ADDR_SYMBOL);
          }
        } else if (nm->type == ELF32) {
          if (flag.g && isupper(current->type)) {
            Print_Line_Addr(current->address, current->type, current->name,
                            nm->type, PRINT_ADDR_SYMBOL);
          } else if (!flag.g) {
            Print_Line_Addr(current->address, current->type, current->name,
                            nm->type, PRINT_ADDR_SYMBOL);
          }
        }
      } else {
        if (flag.g && isupper(current->type)) {
          printFlaga(flag);
          Print_Line_Addr(current->address, current->type, current->name,
                          nm->type, PRINT_SYMBOL);
        } else if (isPrt(current->type)) {
          printFlaga(flag);
          Print_Line_Addr(current->address, current->type, current->name,
                          nm->type, PRINT_NO_ADDR_SYMBOL);
        } else if (!flag.g) {
          printFlaga(flag);
          if (current->type == 'n' || current->type == 't' ||
              current->type == 'b') {
            Print_Line_Addr(current->address, current->type, current->name,
                            nm->type, PRINT_NO_ADDR_SYMBOL);
          } else {
            Print_Line_Addr(current->address, current->type, current->name,
                            nm->type, PRINT_SYMBOL);
          }
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
      tmp = tmp->next;
    }
    current = current->next;
  }
}
