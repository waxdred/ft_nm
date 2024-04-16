#include "../includes/nm.h"

void print_prg(const char *prg, const char *prefix, const char *error) {
  if (prefix) {
    ft_putstr_fd(prefix, STDERR_FILENO);
    ft_putstr_fd(" - ", STDERR_FILENO);
  }
  if (error) {
    ft_putstr_fd(prg, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd(error, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
  }
}
