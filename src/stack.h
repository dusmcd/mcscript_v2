#ifndef _STACK_H
#define _STACK_H

#include "types.h"

typedef struct {
  reg_t capacity;
  reg_t count;
  void** data;
  reg_t base_pointer; // this will serve as an unchanging reference that can be offset to retrieve data
} stack_t;


#endif