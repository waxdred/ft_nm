#include "../includes/nm.h"

static void ft_getopt(char *av, char *flag, int *opt) {
  const char *optchar;

  if (av[0] != '-') {
    *opt = -1;
    return;
  } else if (av[0] == '-' && av[2] != '\0') {
    *opt = -2;
    fprintf(stderr, "ft_ping: invalid arguments: '%s'\n", av);
    return;
  }
  *opt = av[1];
  optchar = strchr(flag, *opt);
  if (optchar == NULL) {
    *opt = '?';
    return;
  }
}

static int ft_check(t_nm *nm, char opt) {
  switch (opt) {
  case '?':
    exit(0);
  case 'h':
    exit(0);
  case 'A':
    nm->flags.a = 1;
    break;
  case 'p':
    nm->flags.p = 1;
    break;
  case 'e':
    nm->flags.e = 1;
    break;
  case 'D':
    nm->flags.D = 1;
    break;
  case 'g':
    nm->flags.g = 1;
    break;
  }
  return EXIT_SUCCESS;
}

int parse_flags(int ac, char **argv) {
  t_nm *nm = get_nm(NULL);
  int opt;
  int i;

  opt = 0;
  i = 1;
  while (i < ac) {
    ft_getopt(argv[i], "?hApeDg", &opt);
    if (opt == -2) {
      return EXIT_FAILURE;
    }
    if (ft_check(nm, opt) == EXIT_FAILURE) {
      return EXIT_FAILURE;
    } else if (opt == -1) {
      if (nm->flags.file == NULL) {
        nm->flags.file = argv[i];
      }
    }
    ++i;
  }
  return EXIT_SUCCESS;
}
