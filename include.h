#ifndef FT_NM_H
#define FT_NM_H
#include <elf.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define ERR_NO_PRG "« a.out »: pas de tel fichier"

typedef struct s_flag {
  int8_t a;
  int8_t g;
  int8_t u;
  int8_t p;
  int8_t r;
  int8_t elf;
  char *file;
} t_flag;

typedef struct SymbolNode {
  unsigned long address;
  char type;
  char name[256];
  struct SymbolNode *next;
} SymbolNode;

void Sort(SymbolNode **head, t_flag flag);
SymbolNode *getMajList(SymbolNode *head);
SymbolNode *reverse_list(SymbolNode *head);
void free_symbol_list(SymbolNode *head);
char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr);
char get_symbol_type_32(Elf32_Sym *sym, Elf32_Shdr *shdr);
int parse_flags(int argc, char **argv, t_flag *flags);
void print_prg(const char *prg, const char *prefix, const char *error);
void list_symbols_64(void *map, t_flag flags);
void list_symbols_32(void *map, t_flag flag);
int get_format(void *map);
void PrintNm64(SymbolNode *head, t_flag flag);
void PrintNm32(SymbolNode *head, t_flag flag);
SymbolNode *AddNode32(SymbolNode **head, Elf32_Addr address, char type,
                      const char *name);
SymbolNode *AddNode(SymbolNode **head, Elf64_Addr address, char type,
                    const char *name);

#endif
