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

#define SPECIAL_CHARS "_.-@#!&$%*"

// Section Header Table

#define ELF32 (1 << 0)
#define ELF64 (1 << 1)
#define L_ENDIAN (1 << 2)
#define B_ENDIAN (1 << 3)

// #define NO_UNDER_SCORE 0
// #define UNDER_SCORE 1
// #define DOUBLE_UNDER_SCORE 2
// #define TRIPLE_UNDER_SCORE 3
// #define DOT 4

typedef int typeUnscore;

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
  // typeUnscore unscore;
  struct SymbolNode *next;
  struct SymbolNode *prev;
  struct SymbolNode *duplicate;
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
char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr, char *name,
                     char *section_name);

char get_symbol_type_32(Elf32_Sym *sym, Elf32_Shdr *shdr, char *name,
                        char *section_name);
int get_format(void *map);
int parse_flags(int ac, char **argv);
t_nm *get_nm(t_nm *nm);
t_nm *init_nm(void);
uint64_t swap_uint64(uint64_t val);
void InitElf(void *map);
void ParseTable32();
void ParseTable64();
void PrintNm(SymbolNode *head, t_flag flag);
char *ft_strchr(const char *str, int c);
void ft_bzero(void *s, size_t n);
void PrintNoSymbol(const char *prog);
int ft_strcmp(const char *s1, const char *s2);
int ft_strcasecmp(const char *s1, const char *s2);
void Sort(SymbolNode **head);
void free_symbol_list(SymbolNode *head);
void list_symbols(void *map);
void print_prg(const char *prg, const char *prefix, const char *error);
void set_elf();
char *ft_strcpy(char *dst, const char *src);
char *ft_strScpy(char *dst, const char *src, int start);
char *ft_strdup(const char *s);
#endif
