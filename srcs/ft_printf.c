#include "../includes/nm.h"

static size_t ft_strlen(const char *str) {
  size_t i;

  i = 0;
  if (!str)
    return (0);
  while (str[i])
    i++;
  return (i);
}

static int ft_sort_int_tab(char *str) {
  int i;
  int m;

  i = 0;
  while (str[i]) {
    m = i + 1;
    while (str[m]) {
      if (str[i] == str[m])
        return (0);
      ++m;
    }
    ++i;
  }
  return (1);
}

int ft_putchar(int c) { return (write(1, &c, 1)); }

int ft_putstr_fd(const char *str, int fd) {
  size_t res;

  if (!str)
    return (0);
  res = 0;
  while (*str) {
    res += write(fd, str, 1);
    str++;
  }
  return (res);
}

int ft_putstr(char *str) {
  size_t res;

  if (!str)
    return (0);
  res = 0;
  while (*str) {
    res += ft_putchar(*str);
    str++;
  }
  return (res);
}

void ft_putnbr_base(int nbr, char *base) {
  unsigned int lnbr;
  unsigned int size;

  lnbr = nbr;
  size = ft_strlen(base);
  if (size <= 1)
    return;
  if (!ft_sort_int_tab(base))
    return;
  if (nbr < 0) {
    ft_putchar('-');
    lnbr *= -1;
  }
  if (lnbr / size) {
    ft_putnbr_base(lnbr / size, base);
    ft_putchar(base[lnbr % size]);
  } else
    ft_putchar(base[lnbr % size]);
}

int ft_putnbr_base_len(unsigned long nbr, char *base) {
  int len = 0;
  unsigned int size = ft_strlen(base);

  if (size <= 1)
    return (0);
  if (!ft_sort_int_tab(base))
    return (0);

  if (nbr == 0)
    return (1);

  while (nbr) {
    len++;
    nbr /= size;
  }

  return (len);
}

int GetSizeAddr(typesElf is) {
  if (is == ELF64)
    return 16;
  else
    return 8;
}

void PrintChar(int c, int size) {
  for (int i = 0; i < size; i++)
    ft_putchar(c);
}

void Print_Line_Addr(unsigned long addr, char type, char *name, typesElf is,
                     int isAddr) {
  int len =
      GetSizeAddr(is) - ft_putnbr_base_len((unsigned long)(addr & 0xFFFFFFFF),
                                           "0123456789abcdef");
  switch (isAddr) {
  case PRINT_SYMBOL:
    PrintChar(' ', GetSizeAddr(is));
    break;
  case PRINT_ADDR_SYMBOL:
    PrintChar('0', len);
    ft_putnbr_base((unsigned long)(addr & 0xFFFFFFFF), "0123456789abcdef");
    break;
  case PRINT_NO_ADDR_SYMBOL:
    PrintChar('0', GetSizeAddr(is));
    break;
  }
  ft_putchar(' ');
  ft_putchar(type);
  ft_putchar(' ');
  ft_putstr(name);
  ft_putchar('\n');
}
