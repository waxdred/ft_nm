#include "../includes/nm.h"

SymbolNode *GetDuplicate(SymbolNode *head, const char *str) {
  SymbolNode *current = head;
  while (current) {
    if (ft_strcmp(current->name, str) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

Input *AddInput(Input **head, const char *name) {
  Input *new_node = malloc(sizeof(Input));
  if (!new_node) {
    perror("malloc");
    exit(1);
  }
  ft_bzero(new_node, sizeof(Input));
  ft_strcpy(new_node->name, name);
  if (!*head) {
    new_node->next = *head;
    *head = new_node;
  } else {
    Input *current = *head;
    while (current->next) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
  return new_node;
}

SymbolNode *AddNode(SymbolNode **head, unsigned long address, char type,
                    const char *name) {
  SymbolNode *duplicate = NULL;
  SymbolNode *new_node = malloc(sizeof(SymbolNode));
  if (!new_node) {
    perror("malloc");
    exit(1);
  }
  ft_bzero(new_node, sizeof(SymbolNode));
  new_node->address = (address == 0) ? LONG_MAX : address;
  new_node->next = NULL;
  new_node->prev = NULL;
  if (address == 0)
    new_node->address = ULONG_MAX;
  else
    new_node->address = address;
  new_node->type = type;
  ft_strcpy(new_node->name, name);
  duplicate = GetDuplicate(*head, new_node->name);
  if (duplicate) {
    SymbolNode *tmp = duplicate;
    while (tmp->duplicate != NULL) {
      tmp = tmp->duplicate;
    }
    tmp->duplicate = new_node;
  } else if (!*head) {
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

void free_nm() {
  t_nm *nm = get_nm(NULL);
  if (nm->head) {
    free_symbol_list(nm->head);
  }
  if (nm->flags.input) {
    free_input_list(nm->flags.input);
  }
  free(nm);
}

void free_input_list(Input *head) {
  while (head) {
    Input *tmp = head;
    head = head->next;
    free(tmp);
  }
}

void free_symbol_list(SymbolNode *head) {
  while (head) {
    SymbolNode *tmp = head;
    if (head->duplicate) {
      free_symbol_list(head->duplicate);
    }
    head = head->next;
    free(tmp);
  }
}
