#include "../includes/nm.h"

void sorted_insert_by_name(SymbolNode **head_ref, SymbolNode *new_node) {
  SymbolNode *current;
  if (!*head_ref || strcmp(new_node->name, (*head_ref)->name) < 0 ||
      (strcmp(new_node->name, (*head_ref)->name) == 0 &&
       new_node->address < (*head_ref)->address)) {
    new_node->next = *head_ref;
    *head_ref = new_node;
  } else {
    current = *head_ref;
    while (current->next && strcmp(current->next->name, new_node->name) < 0) {
      current = current->next;
    }
    while (current->next && strcmp(current->next->name, new_node->name) == 0 &&
           current->next->address < new_node->address) {
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

// TODO check list return position Start sort
int *sortStart(SymbolNode **head, int *info) {
  SymbolNode *tmp = *head;

  while (tmp->next) {
    if (filter_maj(tmp->name))
      info[0] = 1;
    else if (filter_single_underscore_maj(tmp->name))
      info[1] = 1;
    else if (filter_double_underscore_maj(tmp->name))
      info[2] = 1;
    else if (filter_double_underscore_min(tmp->name))
      info[3] = 1;
    else if (filter_single_underscore_min(tmp->name))
      info[4] = 1;
    else if (filter_min(tmp->name))
      info[5] = 1;
    tmp = tmp->next;
  }
  for (int i = 0; i < 6; i++) {
    if (info[i] == 1) {
      info[6] = i;
      break;
    }
  }
  return info;
}

void Sort(SymbolNode **head, t_flag flags) {
  SymbolNode *List = NULL;
  int info[] = {0, 0, 0, 0, 0, 0, 0};
  int *d;
  d = sortStart(head, info);
  int start = d[6];

  switch (start) {
  case 0:
    List = get_filtered_list(*head, filter_maj);
    start++;
    break;
  case 1:
    List = get_filtered_list(*head, filter_single_underscore_maj);
    start++;
    break;
  case 2:
    List = get_filtered_list(*head, filter_double_underscore_maj);
    start++;
    break;
  case 3:
    List = get_filtered_list(*head, filter_double_underscore_min);
    start++;
    break;
  case 4:
    List = get_filtered_list(*head, filter_single_underscore_min);
    start++;
    break;
  case 5:
    List = get_filtered_list(*head, filter_min);
    start++;
    break;
  default:
    return;
  }
  SymbolNode *tmp = List;
  // let's crete while and increment start for add filter
  while (start < 6) {
    while (tmp && tmp->next) {
      tmp = tmp->next;
    }
    switch (start) {
    case 0:
      tmp->next = get_filtered_list(*head, filter_maj);
      break;
    case 1:
      tmp->next = get_filtered_list(*head, filter_single_underscore_maj);
      break;
    case 2:
      tmp->next = get_filtered_list(*head, filter_double_underscore_maj);
      break;
    case 3:
      tmp->next = get_filtered_list(*head, filter_double_underscore_min);
      break;
    case 4:
      tmp->next = get_filtered_list(*head, filter_single_underscore_min);
      break;
    case 5:
      tmp->next = get_filtered_list(*head, filter_min);
      break;
    }
    start++;
  }

  PrintNm(List, flags);
  t_nm *nm = get_nm(NULL);
  nm->Free_list(List);
}
