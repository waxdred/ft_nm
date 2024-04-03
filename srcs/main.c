#include "../includes/nm.h"
#include <stdio.h>

int main(int argc, char **argv) {
  t_flag flag;

  bzero(&flag, sizeof(t_flag));
  if (parse_flags(argc, argv, &flag) != 0) {
    return 1;
  }
  printf("flag.a = %s\n", flag.file);

  if (argc < 2) {
    print_prg(argv[0], NULL, ERR_NO_PRG);
    return 1;
  }

  int fd = open(flag.file, O_RDONLY);
  if (fd == -1) {
    print_prg(flag.file, NULL, NULL);
    return 1;
  }

  struct stat my_stat;
  if (stat(flag.file, &my_stat) != 0) {
    print_prg(argv[0], "stat", NULL);
    close(fd);
    return 1;
  }

  void *map = mmap(NULL, my_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (map == (void *)-1) {
    print_prg(flag.file, "mmap", NULL);
    close(fd);
    return 1;
  }

  flag.elf = get_format(map);
  if (flag.elf == -1) {
    print_prg(flag.file, "Erreur", "Format ELF inconnu");
    munmap(map, my_stat.st_size);
    close(fd);
    return 1;
  } else if (flag.elf == 64) {
    list_symbols_64(map, flag);
  } else if (flag.elf == 32) {
    list_symbols_32(map, flag);
  }

  munmap(map, my_stat.st_size);
  close(fd);

  return 0;
}
