#include "../includes/nm.h"

void list_symbols(void *map) {
  t_nm *nm = get_nm(NULL);
  nm->InitElf(map);

  nm->ParseTable();

  if (nm->head == NULL) {
    ft_putstr_fd("ft_nm: ", STDERR_FILENO);
    ft_putstr_fd(nm->flags.file, STDERR_FILENO);
    ft_putstr_fd(": aucun symbole\n", STDERR_FILENO);
  } else if (nm->flags.p) {
    PrintNm(nm->head, nm->flags);
  } else {
    Sort(&nm->head);
    PrintNm(nm->head, nm->flags);
  }
  nm->Free_list(nm->head);
}
