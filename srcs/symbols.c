#include "../includes/nm.h"

void list_symbols(void *map) {
  t_nm *nm = get_nm(NULL);
  nm->InitElf(map);

  nm->ParseTable();

  if (nm->head == NULL) {
    printf("No symbols\n");
  } else if (nm->flags.p) {
    PrintNm(nm->head, nm->flags);
  } else {
    Sort(&nm->head);
    PrintNm(nm->head, nm->flags);
  }
  nm->Free_list(nm->head);
}
