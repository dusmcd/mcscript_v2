#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_vm.h"

bool test_execute_command(test_case_exec* test_cases, int size) {
  for (int i = 0; i < size; i++) {
    test_case_exec t_case = test_cases[i];
    printf("%s\n", t_case.desc);
    printf("Expected output: ");
    object_t* left = t_case.cmd.operands[0];
    object_t* right = t_case.cmd.operands[1];
    object_t* actual = execute_command(t_case.vm, &t_case.cmd);

    switch(left->type)
    {
      case INTEGER:
        printf("%i, ", t_case.output.data.v_int);
        printf("Actual output: %i\n", actual->data.v_int);
        if (t_case.output.data.v_int != actual->data.v_int)
          return false;
        break;
      case STRING:
        printf("%s, ", t_case.output.data.v_string);
        printf("Actual output: %s\n", actual->data.v_string);
        if (strcmp(t_case.output.data.v_string, actual->data.v_string) != 0)
          return false;
        break;
      default:
        return false;
    }
  }

  return true;
}
void test_vm() {
  vm_t* vm = create_vm();
  test_case_exec* test_cases = generate_exec_cases(vm);

  printf("Testing vm_t functionality...\n");
  int total = 1;
  int passed = 0;

  if (test_execute_command(test_cases, 3)) {
    passed++;
    printf("'execute_command' test passed\n");
  }
  else 
    printf("'execute_command' test failed\n");
  
  printf("\n %i of %i test passed\n", passed, total);

  free_vm(vm);
  free(test_cases);
  test_cases = NULL;
}

test_case_exec* generate_exec_cases(vm_t* vm) {
  test_case_exec* test_cases = malloc(sizeof(test_case_exec) * 3);



  return test_cases;
}

