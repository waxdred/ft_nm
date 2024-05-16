#include "../includes/nm.h"
#include <stdio.h>

int main(int argc, char **argv) {
  t_nm *nm = init_nm();
  nm->Set_Elf();

  if (nm == NULL) {
    return -1;
  }

  if (parse_flags(argc, argv) != 0) {
    free(nm);
    return 1;
  }

  if (argc < 2) {
    print_prg(argv[0], NULL, ERR_NO_PRG);
    free(nm);
    return 1;
  }

  Input *input = nm->flags.input;
  while (input != NULL) {
    int fd = open(input->name, O_RDONLY);
    if (fd == -1) {
      print_prg(input->name, NULL, NULL);
      break;
    }
    struct stat my_stat;
    if (stat(input->name, &my_stat) != 0) {
      print_prg(argv[0], "stat", NULL);
      close(fd);
      break;
    }
    nm->flags.file = input->name;
    if (nm->flags.nb_file > 1) {
      ft_putstr("\n");
      ft_putstr(input->name);
      ft_putstr(":");
      ft_putstr("\n");
    }
    nm->map = mmap(NULL, my_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (nm->map == MAP_FAILED) {
      print_prg(input->name, "mmap", NULL);
      close(fd);
      break;
    }
    nm->flags.elf = get_format(nm->map);
    if (nm->flags.elf == 0) {
      ft_putstr_fd("ft_nm: ", STDERR_FILENO);
      ft_putstr_fd(nm->flags.file, STDERR_FILENO);
      ft_putstr_fd(": file format not recognized\n", STDERR_FILENO);
      munmap(nm->map, my_stat.st_size);
      close(fd);
      break;
    }
    nm->List_symbols();
    munmap(nm->map, my_stat.st_size);
    close(fd);
    input = input->next;
  }
  free_input_list(nm->flags.input);
  free(nm);
  return 0;
}
