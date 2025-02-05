#include "object.h"
#include <stdlib.h>
#include <string.h>

object_t* create_new_int(int val) {
  object_t* obj = malloc(sizeof(object_t));
  if (obj == NULL)
    return NULL;
  
  obj->data.v_int = val;
  obj->type = INTEGER;

  return obj;
}
object_t* create_new_string(const char* str) {
  object_t* obj = malloc(sizeof(object_t));
  if (obj == NULL)
    return NULL;
  
  char* new_str = malloc(strlen(str));
  if (new_str == NULL) {
    free(obj);
    obj = NULL;
    return NULL;
  }

  strcpy(new_str, str);

  obj->data.v_string = new_str;
  obj->type = STRING;

  return obj;
}
