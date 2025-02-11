#ifndef MCSCRIPT_V2_TESTS_TEST_UTILS_H
#define MCSCRIPT_V2_TESTS_TEST_UTILS_H

#include "../src/utils/list.h"
#include "stdbool.h"

typedef struct {
  const char* input;
  char ch;
  list_t* output;
  const char* desc;
} case_split_t;

void test_utils();
case_split_t* generate_cases_split();
bool test_split(case_split_t* test_cases, int size);


#endif