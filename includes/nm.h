#ifndef FT_NM_H
#define FT_NM_H
#include <ctype.h>
#include <elf.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
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

// Define Print
#define PRINT_SYMBOL 0
#define PRINT_ADDR_SYMBOL 1
#define PRINT_NO_ADDR_SYMBOL 2

// Section Header Table
#define ELF32 (1 << 0)
#define ELF64 (1 << 1)
#define L_ENDIAN (1 << 2)
#define B_ENDIAN (1 << 3)

typedef int typesElf;
typedef int typesEndian;

typedef struct Input {
  char name[256];
  struct Input *next;
} Input;

typedef struct s_flag {
  int8_t a;
  int8_t g;
  int8_t u;
  int8_t p;
  int8_t e;
  int8_t j;
  int8_t r;
  int8_t elf;
  Input *input;
  char *file;
  int nb_file;
} t_flag;

typedef struct SymbolNode {
  unsigned long address;
  char type;
  char name[256];

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
  void (*InitElf)();
  void (*free_nm)();
  void (*ParseTable)();
  void (*List_symbols)();
  void (*Set_Elf)();
  void (*Free_list)(SymbolNode *head);
  void (*Free_input)(Input *head);
  SymbolNode *(*AddNode)(SymbolNode **head, unsigned long address, char type,
                         const char *name);
} t_nm;

char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr);
char get_symbol_type_32(Elf32_Sym *sym, Elf32_Shdr *shdr);
char *ft_strScpy(char *dst, const char *src, int start);
char *ft_strchr(const char *str, int c);
char *ft_strcpy(char *dst, const char *src);
char *ft_strdup(const char *s);
int ft_strcasecmp(const char *s1, const char *s2);
int ft_strcmp(const char *s1, const char *s2);
int get_format(void *map);
void free_nm();
void Print_Line_Addr(unsigned long addr, char type, char *name, typesElf is,
                     int isAddr);
int parse_flags(int ac, char **argv);
int ft_putstr_fd(const char *str, int fd);
t_nm *get_nm(t_nm *nm);
t_nm *init_nm(void);
uint64_t swap_uint64(uint64_t val);
void free_input_list(Input *head);
void InitElf();
void ParseTable32();
void ParseTable64();
void PrintNm(SymbolNode *head, t_flag flag);
void PrintNoSymbol(const char *prog);
void Sort(SymbolNode **head);
void free_symbol_list(SymbolNode *head);
void ft_bzero(void *s, size_t n);
void list_symbols();
int ft_putstr(char *str);
Input *AddInput(Input **head, const char *name);
SymbolNode *AddNode(SymbolNode **head, unsigned long address, char type,
                    const char *name);
SymbolNode *getMajList(SymbolNode *head);
SymbolNode *reverse_list(SymbolNode *head);
void print_prg(const char *prg, const char *prefix, const char *error);
void set_elf();
#endif
