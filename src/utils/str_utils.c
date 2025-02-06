#include "str_utils.h"
#include "stdlib.h"
#include "string.h"

char* append_str(char* str, char ch, int size) {
  char* temp = realloc(str, size + 1);
  if (temp == NULL) {
    free(str);
    return NULL;
  }

  str = temp;
  str[size - 1] = ch;
  str[size] = '\0';

  return str;
}

list_t* split(const char* str, char ch) {
  int len = strlen(str);
  list_t* substrs = initialize_list();
  char* current = NULL;

  int j = 0;
  for (int i = 0; i < len; i++) {
    if (str[i] == ch) {
      push_back(substrs, current);
      j = 0;
      free(current);
      current = NULL;
      continue;
    }
    current = append_str(current, str[i], j + 1);
    j++;
  }

  if (current != NULL) {
    push_back(substrs, current);
    free(current);
    current = NULL;
  }
  return substrs;
}