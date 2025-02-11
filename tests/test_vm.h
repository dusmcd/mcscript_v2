#ifndef MCSCRIPT_V2_TESTS_TEST_VM_H
#define MCSCRIPT_V2_TESTS_TEST_VM_H

#include "../src/vm.h"
#include "../src/object.h"
#include <stdbool.h>


typedef struct {
  vm_t* vm;
  command_t* cmd;
  object_t* output;
  const char* desc;
  type_t type;
} test_case_exec;



bool test_arithmetic(test_case_exec* test_cases, int size);
test_case_exec* generate_arith_cases(vm_t* vm);
void test_vm();


#endif