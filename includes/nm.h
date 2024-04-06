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

#define ELF32 (1 << 0)
#define ELF64 (1 << 1)
#define L_ENDIAN (1 << 2)
#define B_ENDIAN (1 << 3)

typedef int typesElf;
typedef int typesEndian;

typedef struct s_flag {
  int8_t a;
  int8_t g;
  int8_t u;
  int8_t p;
  int8_t e;
  int8_t D;
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
  typesEndian endian;
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

SymbolNode *AddNode(SymbolNode **head, unsigned long address, char type,
                    const char *name);
SymbolNode *getMajList(SymbolNode *head);
SymbolNode *reverse_list(SymbolNode *head);
char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr, char *name);
char get_symbol_type_32(Elf32_Sym *sym, Elf32_Shdr *shdr, char *name);
int get_format(void *map);
int parse_flags(int ac, char **argv);
t_nm *get_nm(t_nm *nm);
t_nm *init_nm(void);
uint64_t swap_uint64(uint64_t val);
void InitElf(void *map);
void ParseTable32();
void ParseTable64();
void PrintNm(SymbolNode *head, t_flag flag);
void PrintNoSymbol(const char *prog);
void Sort(SymbolNode **head, t_flag flag);
void free_symbol_list(SymbolNode *head);
void list_symbols(void *map);
void print_prg(const char *prg, const char *prefix, const char *error);
void set_elf();
#endif
