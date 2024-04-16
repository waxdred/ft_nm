#include "../includes/nm.h"

int is_Double_under_score(const char *name) {
  return name[0] == '_' && name[1] == '_';
}

int is_Under_score(const char *name) { return name[0] == '_'; }

int is_Triple_Unscore(const char *name) {
  return name[0] == '_' && name[1] == '_' && name[2] == '_';
}

int is_Dot(const char *name) { return name[0] == '.'; }

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

SymbolNode *AddNode(SymbolNode **head, unsigned long address, char type,
                    const char *name) {
  SymbolNode *duplicate = NULL;
  SymbolNode *new_node = malloc(sizeof(SymbolNode));
  if (!new_node) {
    perror("malloc");
    exit(1);
  }
  ft_bzero(new_node, sizeof(SymbolNode));
  if (is_Double_under_score(name)) {
    new_node->unscore = DOUBLE_UNDER_SCORE;
    if (is_Triple_Unscore(name)) {
      new_node->unscore = TRIPLE_UNDER_SCORE;
    }
  } else if (is_Under_score(name)) {
    new_node->unscore = UNDER_SCORE;
  } else if (is_Dot(name)) {
    new_node->unscore = DOT;
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
  ft_strcpy(new_node->name,
            name + (new_node->unscore == DOT ? 1 : new_node->unscore));
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
