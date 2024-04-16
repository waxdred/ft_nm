#include "../includes/nm.h"

static void printHelpCmd() {
  ft_putstr_fd("Usage: nm [option(s)] [fichier(s)]\n", STDERR_FILENO);
  ft_putstr_fd("Les options sont :\n\t-A,\tAfficher le nom du fichier d'entrée "
               "avant chaque symbole\n",
               STDERR_FILENO);
  ft_putstr_fd("\t-p, \tNe pas trier les symboles\n", STDERR_FILENO);
  ft_putstr_fd("\t-j, \tUn synonyme pour --format=just-symbols\n",
               STDERR_FILENO);
  ft_putstr_fd("\t-e, \t(ignoré)\n", STDERR_FILENO);
  ft_putstr_fd("\t-g, \tAfficher uniquement les symboles externes\n",
               STDERR_FILENO);
}

static void ft_getopt(char *av, char *flag, int *opt) {
  const char *optchar;

  if (av[0] != '-') {
    *opt = -1;
    return;
  } else if (av[0] == '-' && av[2] != '\0') {
    *opt = -2;
    ft_putstr_fd("ft_nm: invalid option -- '", STDERR_FILENO);
    return;
  }
  *opt = av[1];
  optchar = ft_strchr(flag, *opt);
  if (optchar == NULL) {
    *opt = '?';
    return;
  }
}

static int ft_check(t_nm *nm, char opt) {
  switch (opt) {
  case '?':
    printHelpCmd();
    return EXIT_FAILURE;
  case 'h':
    printHelpCmd();
    return EXIT_FAILURE;
  case 'A':
    nm->flags.a = 1;
    break;
  case 'p':
    nm->flags.p = 1;
    break;
  case 'j':
    nm->flags.j = 1;
    break;
  case 'e':
    nm->flags.e = 1;
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
    ft_getopt(argv[i], "?hApegj", &opt);
    if (opt == -2) {
      return EXIT_FAILURE;
    }
    if (ft_check(nm, opt) == EXIT_FAILURE) {
      return EXIT_FAILURE;
    } else if (opt == -1) {
      AddInput(&nm->flags.input, argv[i]);
      nm->flags.nb_file++;
    }
    ++i;
  }
  return EXIT_SUCCESS;
}
