#include "include.h"
#include <ctype.h>
#include <string.h>

void sorted_insert_by_name(SymbolNode **head_ref, SymbolNode *new_node) {
  SymbolNode *current;
  if (!*head_ref || strcmp(new_node->name, (*head_ref)->name) < 0) {
    new_node->next = *head_ref;
    *head_ref = new_node;
  } else {
    current = *head_ref;
    while (current->next && strcmp(current->next->name, new_node->name) < 0) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}

void sort_list_by_name(SymbolNode **head_ref) {
  SymbolNode *sorted = NULL;
  SymbolNode *current = *head_ref;
  while (current) {
    SymbolNode *next = current->next;
    sorted_insert_by_name(&sorted, current);
    current = next;
  }
  *head_ref = sorted;
}

SymbolNode *create_new_node_from_current(SymbolNode *current) {
  SymbolNode *newNode = malloc(sizeof(SymbolNode));
  if (!newNode) {
    perror("malloc");
    exit(1);
  }
  *newNode = *current;
  newNode->next = NULL;
  return newNode;
}

SymbolNode *get_filtered_list(SymbolNode *head,
                              int (*filter_func)(const char *)) {
  SymbolNode *List = NULL;
  SymbolNode *current = head;

  while (current) {
    if (filter_func(current->name)) {
      SymbolNode *newNode = create_new_node_from_current(current);
      if (!List) {
        List = newNode;
      } else {
        SymbolNode *tmp = List;
        while (tmp->next) {
          tmp = tmp->next;
        }
        tmp->next = newNode;
      }
    }
    current = current->next;
  }

  sort_list_by_name(&List);
  return List;
}

int filter_maj(const char *name) { return isupper(name[0]); }
int filter_min(const char *name) { return islower(name[0]); }

int filter_double_underscore_maj(const char *name) {
  return strlen(name) > 2 && name[0] == '_' && name[1] == '_' &&
         isupper(name[2]);
}

int filter_double_underscore_min(const char *name) {
  return strlen(name) > 2 && name[0] == '_' && name[1] == '_' &&
         islower(name[2]);
}

int filter_single_underscore_maj(const char *name) {
  return name[0] == '_' && isupper(name[1]);
}
int filter_single_underscore_min(const char *name) {
  return name[0] == '_' && islower(name[1]);
}

void Sort(SymbolNode **head, t_flag flags) {
  SymbolNode *List = get_filtered_list(*head, filter_maj);
  SymbolNode *tmp = List;

  while (tmp && tmp->next) {
    tmp = tmp->next;
  }

  tmp->next = get_filtered_list(*head, filter_single_underscore_maj);
  while (tmp && tmp->next) {
    tmp = tmp->next;
  }

  tmp->next = get_filtered_list(*head, filter_double_underscore_maj);
  while (tmp && tmp->next) {
    tmp = tmp->next;
  }

  tmp->next = get_filtered_list(*head, filter_double_underscore_min);
  while (tmp && tmp->next) {
    tmp = tmp->next;
  }
  tmp->next = get_filtered_list(*head, filter_single_underscore_min);
  while (tmp && tmp->next) {
    tmp = tmp->next;
  }

  tmp->next = get_filtered_list(*head, filter_min);
  while (tmp && tmp->next) {
    tmp = tmp->next;
  }
  PrintNm64(List, flags);

  free_symbol_list(List);
}
