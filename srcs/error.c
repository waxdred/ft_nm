#include "../includes/nm.h"

void print_prg(const char *prg, const char *prefix, const char *error) {
  if (prefix) {
    dprintf(2, "%s", prefix);
    dprintf(2, " - ");
  }
  if (error) {
    dprintf(2, "%s", prg);
    dprintf(2, ": ");
    dprintf(2, "%s", error);
    dprintf(2, "\n");
  } else {
    perror(prg);
  }
}
