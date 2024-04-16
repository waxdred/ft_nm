#include "../includes/nm.h"

char *TrimSpecialChars(char *name) {
  int i = 0;
  int k = 0;
  int check = 0;
  char *str = ft_strdup(name);
  while (name[i]) {
    check = 0;
    for (int j = 0; SPECIAL_CHARS[j]; j++) {
      if (str[i] == SPECIAL_CHARS[j]) {
        check = 1;
        break;
      }
    }
    if (check == 0) {
      str[k] = name[i];
      k++;
    }
    i++;
  }
  str[k] = '\0';
  return str;
}

int compareNames(SymbolNode *a, SymbolNode *b) {
  char *nameA = TrimSpecialChars(a->name);
  char *nameB = TrimSpecialChars(b->name);
  int result = ft_strcasecmp(nameA, nameB);
  if (result == 0) {
    if (ft_strcmp(nameA, nameB) < 0) {
      result = -1;
    } else if (ft_strcmp(nameA, nameB) > 0) {
      result = 1;
    } else {
      result = 0;
    }
  }
  free(nameA);
  free(nameB);
  return result;
}

void Sort(SymbolNode **head) {
  if (!*head || !(*head)->next) {
    return;
  }

  // Diviser la liste en deux moitiés
  SymbolNode *slow = *head;
  SymbolNode *fast = (*head)->next;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  SymbolNode *mid = slow->next;
  slow->next = NULL;
  mid->prev = NULL;

  // Trier les deux moitiés
  Sort(&(*head));
  Sort(&mid);

  // Fusionner les deux moitiés triées
  SymbolNode *sorted = NULL;
  SymbolNode **tail = &sorted;
  SymbolNode *left = *head;
  SymbolNode *right = mid;
  while (left && right) {
    int cmp = compareNames(left, right);
    if (cmp < 0) {
      *tail = left;
      left = left->next;
    } else if (cmp > 0) {
      *tail = right;
      right = right->next;
    } else {
      *tail = left;
      left = left->next;
      tail = &(*tail)->next;
      *tail = right;
      right = right->next;
    }
    (*tail)->prev = *tail;
    tail = &(*tail)->next;
  }
  *tail = left ? left : right;
  if (*tail) {
    (*tail)->prev = NULL;
  }
  *head = sorted;
}
