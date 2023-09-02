
#include "../include.h"

SymbolNode *AddNode(SymbolNode **head, Elf64_Addr address, char type,
                    const char *name) {
  SymbolNode *new_node = malloc(sizeof(SymbolNode));
  if (!new_node) {
    perror("malloc");
    exit(1);
  }
  new_node->address = (address == 0) ? ULONG_MAX : address;
  new_node->next = NULL;
  if (address == 0)
    new_node->address = ULONG_MAX;
  else
    new_node->address = address;
  new_node->type = type;
  strncpy(new_node->name, name, sizeof(new_node->name) - 1);
  if (!*head) {
    new_node->next = *head;
    *head = new_node;
  } else {
    SymbolNode *current = *head;
    while (current->next) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }

  return new_node;
}

void free_symbol_list(SymbolNode *head) {
  while (head) {
    SymbolNode *tmp = head;
    head = head->next;
    free(tmp);
  }
}
