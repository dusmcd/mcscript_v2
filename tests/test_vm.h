#ifndef _TEST_VM_H
#define _TEST_VM_H

#include "../vm.h"
#include "../object.h"
#include <stdbool.h>


typedef struct {
  vm_t* vm;
  command_t* cmd;
  object_t output;
  const char* desc;
  type_t type;
} test_case_exec;



bool test_execute_command(test_case_exec* test_cases, int size);
test_case_exec* generate_exec_cases(vm_t* vm);
void test_vm();


#endif