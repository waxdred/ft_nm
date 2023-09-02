#include "../include.h"

SymbolNode *reverse_list(SymbolNode *head) {
  SymbolNode *prev = NULL;
  SymbolNode *current = head;
  SymbolNode *next = NULL;

  while (current) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  return prev;
}
