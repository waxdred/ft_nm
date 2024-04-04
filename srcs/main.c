#include "../includes/nm.h"
#include <stdio.h>

int main(int argc, char **argv) {
  t_nm *nm = init_nm();

  if (nm == NULL) {
    return -1;
  }

  if (parse_flags(argc, argv, &nm->flags) != 0) {
    return 1;
  }

  if (argc < 2) {
    print_prg(argv[0], NULL, ERR_NO_PRG);
    return 1;
  }

  int fd = open(nm->flags.file, O_RDONLY);
  if (fd == -1) {
    print_prg(nm->flags.file, NULL, NULL);
    return 1;
  }

  struct stat my_stat;
  if (stat(nm->flags.file, &my_stat) != 0) {
    print_prg(argv[0], "stat", NULL);
    close(fd);
    return 1;
  }

  void *map = mmap(NULL, my_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (map == (void *)-1) {
    print_prg(nm->flags.file, "mmap", NULL);
    close(fd);
    return 1;
  }

  nm->flags.elf = get_format(map);
  if (nm->flags.elf == -1) {
    print_prg(nm->flags.file, "Erreur", "Format ELF inconnu");
    munmap(map, my_stat.st_size);
    close(fd);
    return 1;
  }
  nm->Set_Elf(nm->flags.elf);
  nm->List_symbols(map);

  munmap(map, my_stat.st_size);
  close(fd);

  return 0;
}
