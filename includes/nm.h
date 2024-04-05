#ifndef FT_NM_H
#define FT_NM_H
#include <ctype.h>
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

#define ELF32 32
#define ELF64 64

typedef int typesElf;

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

typedef struct s_elf32 {
  Elf32_Ehdr *hdr;
  Elf32_Shdr *shdr;
  Elf32_Sym *symtab;
  char *symstrtab;
} t_elf32;

typedef struct s_elf64 {
  Elf64_Ehdr *hdr;
  Elf64_Shdr *shdr;
  Elf64_Sym *symtab;
  char *symstrtab;
} t_elf64;

typedef struct s_nm {
  typesElf type;
  t_flag flags;
  SymbolNode *head;
  t_elf32 elf32;
  t_elf64 elf64;
  void *map;

  // interface
  void (*InitElf)(void *map);
  void (*ParseTable)();
  void (*List_symbols)(void *map);
  void (*Set_Elf)();
  void (*Free_list)(SymbolNode *head);
  SymbolNode *(*AddNode)(SymbolNode **head, unsigned long address, char type,
                         const char *name);

} t_nm;

void InitElf(void *map);
void ParseTable64();
void ParseTable32();
void Sort(SymbolNode **head, t_flag flag);
void set_elf();
t_nm *get_nm(t_nm *nm);
t_nm *init_nm(void);
SymbolNode *getMajList(SymbolNode *head);
SymbolNode *reverse_list(SymbolNode *head);
void free_symbol_list(SymbolNode *head);
char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr, char *name);
char get_symbol_type_32(Elf32_Sym *sym, Elf32_Shdr *shdr);
int parse_flags(int argc, char **argv, t_flag *flags);
void print_prg(const char *prg, const char *prefix, const char *error);
void list_symbols(void *map);
int get_format(void *map);
void PrintNm(SymbolNode *head, t_flag flag);
void PrintNoSymbol(const char *prog);
SymbolNode *AddNode(SymbolNode **head, unsigned long address, char type,
                    const char *name);
#endif
