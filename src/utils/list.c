#include "list.h"
#include "stdlib.h"
#include "string.h"

list_t* initialize_list() {
  list_t* list = malloc(sizeof(list_t));
  if (list == NULL)
    return NULL;
  
  node_t* root = malloc(sizeof(node_t));
  if (root == NULL)
    return NULL;
  
  root->val = NULL;
  root->next = NULL;
  list->head = root;
  list->tail = root;
  list->size = 1;

  return list;
}

void push_back(list_t* list, const char* val) {
  if (list == NULL || val == NULL)
    return;
  
  char* new_val = malloc(strlen(val) + 1);
  if (new_val == NULL)
    return;

  strcpy(new_val, val);

  node_t* new_node = malloc(sizeof(node_t));
  if (new_node == NULL)
    return;
  
  new_node->val = new_val;
  new_node->next = NULL;

  list->tail->next = new_node;
  list->tail = new_node;
}