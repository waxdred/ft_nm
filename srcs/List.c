#include "../includes/nm.h"

int is_Double_under_score(const char *name) {
  return name[0] == '_' && name[1] == '_';
}

int is_Under_score(const char *name) { return name[0] == '_'; }

SymbolNode *AddNode(SymbolNode **head, unsigned long address, char type,
                    const char *name) {
  SymbolNode *new_node = malloc(sizeof(SymbolNode));
  if (!new_node) {
    perror("malloc");
    exit(1);
  }
  if (is_Double_under_score(name)) {
    new_node->unscore = DOUBLE_UNDER_SCORE;
  } else if (is_Under_score(name)) {
    new_node->unscore = UNDER_SCORE;
  } else {
    new_node->unscore = NO_UNDER_SCORE;
  }
  new_node->address = (address == 0) ? LONG_MAX : address;
  new_node->next = NULL;
  new_node->prev = NULL;
  if (address == 0)
    new_node->address = ULONG_MAX;
  else
    new_node->address = address;
  new_node->type = type;
  ft_strcpy(new_node->name, name + new_node->unscore);
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
    current->prev = current;
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
