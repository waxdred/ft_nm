#include "include.h"

void print_prg(const char *prg, const char *prefix, const char *error) {
  if (prefix) {
    write(2, prefix, strlen(prefix));
    write(2, " - ", 3);
  }
  if (error) {
    write(2, prg, strlen(prg));
    write(2, ": ", 2);
    write(2, error, strlen(error));
    write(2, "\n", 1);
  } else {
    perror(prg);
  }
}
