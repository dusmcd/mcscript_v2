#ifndef MCSCRIPT_V2_LIST_H
#define MCSCRIPT_V2_LIST_H

typedef struct Node node_t;

struct Node {
  char* val;
  node_t* next;
}; 

typedef struct {
  node_t* head;
  node_t* tail;
  int size;
} list_t;

list_t* initialize_list();
void push_back(list_t* list, const char* val);


#endif