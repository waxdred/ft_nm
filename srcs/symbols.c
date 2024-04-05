#include "../includes/nm.h"

void list_symbols(void *map) {
  t_nm *nm = get_nm(NULL);
  SymbolNode *symbol_list = NULL;
  nm->InitElf(map);

  nm->ParseTable();

  SymbolNode *current = symbol_list;
  printf("\n\n\nListe des symboles sort:\n");
  if (nm->flags.p) {
    PrintNm(current, nm->flags);
  } else {
    Sort(&current, nm->flags);
  }
  nm->Free_list(symbol_list);
}
