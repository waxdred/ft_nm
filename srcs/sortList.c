#include "../includes/nm.h"

int compareNames(SymbolNode *a, SymbolNode *b) {
  int result = ft_strcasecmp(a->name, b->name);
  if (result == 0) {
    if (a->type < b->type) {
      return -1;
    } else if (a->type > b->type) {
      return 1;
    } else {
      return 0;
    }
  }

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
