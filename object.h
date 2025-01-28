#ifndef _OBJECT_H
#define _OBJECT_H

typedef enum {
  INTEGER,
  STRING, 
} type_t;

typedef union {
  int v_int;
  char* v_string;
} data_t;

typedef struct {
  type_t type;
  data_t data;
} object_t;



#endif