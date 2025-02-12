#include "test_utils.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../src/utils/str_utils.h"

void print_list(list_t* list) {
  printf("[");
  node_t* current = list->head->next;
  for (int i = 0; i < list->size; i++) {
    printf("%s", current->val);
    if (i != list->size - 1)
      printf(", ");
    
    current = current->next;
  }

  printf("]");

}

void test_utils() {
  int total = 1;
  int passed = 0;

  case_split_t* split_cases = generate_cases_split();
  printf("\nTesting utility functions...\n");

  if (test_split(split_cases, 5)) {
    printf("'test_util' test passed\n");
    passed++;
  }
  else
    printf("'test_util' test failed\n");
  
  free(split_cases);
  
  printf("%i of %i tests passed\n", passed, total);
}

case_split_t* generate_cases_split() {
  list_t* list1 = initialize_list();
  push_back(list1, "The");
  push_back(list1, "quick");
  push_back(list1, "brown");
  push_back(list1, "fox.");

  list_t* list2 = initialize_list();
  push_back(list2, "a");
  push_back(list2, "+");
  push_back(list2, "b");
  push_back(list2, "+");
  push_back(list2, "c");

  list_t* list3 = initialize_list();
  push_back(list3, "var");
  push_back(list3, "num");
  push_back(list3, "=");
  push_back(list3, "5");

  list_t* list4 = initialize_list();
  push_back(list4, "here");
  push_back(list4, "we");
  push_back(list4, "go");

  list_t* list5 = initialize_list();
  push_back(list5, "something");
  push_back(list5, "in");
  push_back(list5, "the");
  push_back(list5, "way");

  case_split_t* test_cases = malloc(sizeof(case_split_t) * 5);
  if (test_cases == NULL)
    return NULL;


  test_cases[0] = (case_split_t){.ch = ' ', .desc = "Testing splitting on whitespace", .output = list1, .input = "The quick brown fox."};
  test_cases[1] = (case_split_t){.ch = ' ', .desc = "Testing splitting on whitespace", .output = list2, .input = "a + b + c"};
  test_cases[2] = (case_split_t){.ch = ' ', .desc = "Testing splitting on whitespace", .output = list3, .input = "var num = 5"};
  test_cases[3] = (case_split_t){.ch = ' ', .desc = "Testing whitespace at beginning", .output = list4, .input = " here we go"};
  test_cases[4] = (case_split_t){.ch = ' ', .desc = "Testing multiple whitespaces", .output = list5, .input = "something     in the  way    "};

  return test_cases;
}

bool test_split(case_split_t* test_cases, int size) {
  for (int i = 0; i < size; i++) {
    case_split_t t_case = test_cases[i];
    list_t* actual = split(t_case.input, t_case.ch);
    printf("\t%s\n", t_case.desc);
    printf("\tExpected output: ");
    print_list(t_case.output);
    printf(", Actual output: ");
    print_list(actual);
    printf("\n\n");
    node_t* a_current = actual->head->next;
    node_t* e_current = t_case.output->head->next;
    for (int j = 0; j < t_case.output->size; j++) {
      const char* actual_val = a_current->val;
      const char* expected_val = e_current->val;
      if (strcmp(actual_val, expected_val) != 0)
        return false;
      
      a_current = a_current->next;
      e_current = e_current->next;
    }
  }
  return true;
}
