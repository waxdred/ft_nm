#include "../includes/nm.h"

int parse_flags(int argc, char **argv, t_flag *flags) {
  int opt;
  while ((opt = getopt(argc, argv, "agupr")) != -1) {
    switch (opt) {
    case 'a':
      flags->a = 1;
      break;
    case 'g':
      flags->g = 1;
      break;
    case 'u':
      flags->u = 1;
      break;
    case 'p':
      flags->p = 1;
      break;
    case 'r':
      flags->r = 1;
      break;
    default:
      fprintf(stderr, "Usage: %s [-a] [-g] [-u] [-p] [-r]\n", argv[0]);
      return -1;
    }
  }
  if (optind < argc) {
    flags->file = argv[optind];
  } else {
    fprintf(stderr, "Expected filename after options\n");
    return -1;
  }
  return 0;
}
