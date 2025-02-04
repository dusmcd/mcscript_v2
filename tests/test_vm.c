#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_vm.h"

bool test_execute_command(test_case_exec* test_cases, int size) {
  for (int i = 0; i < size; i++) {
    test_case_exec t_case = test_cases[i];
    printf("%s\n", t_case.desc);
    printf("Expected output: ");
    object_t* actual = execute_command(t_case.vm, t_case.cmd);

    switch(t_case.type)
    {
      case INTEGER:
        printf("%i, ", t_case.output.data.v_int);
        printf("Actual output: %i\n", actual->data.v_int);
        if (t_case.output.data.v_int != actual->data.v_int)
          return false;
        break;
      case STRING:
        printf("\"%s\", ", t_case.output.data.v_string);
        printf("Actual output: \"%s\"\n", actual->data.v_string);
        if (strcmp(t_case.output.data.v_string, actual->data.v_string) != 0)
          return false;
        break;
      default:
        return false;
    }
    printf("\n");
  }

  return true;
}
void test_vm() {
  vm_t* vm = create_vm();
  test_case_exec* test_cases = generate_exec_cases(vm);

  printf("Testing vm_t functionality...\n\n");
  int total = 1;
  int passed = 0;

  if (test_execute_command(test_cases, 3)) {
    passed++;
    printf("'execute_command' test passed\n");
  }
  else 
    printf("'execute_command' test failed\n");
  
  printf("\n%i of %i test passed\n", passed, total);

  free_program(vm->current_program);
  free_vm(vm);
  free(test_cases);
  test_cases = NULL;
}

test_case_exec* generate_exec_cases(vm_t* vm) {
  test_case_exec* test_cases = malloc(sizeof(test_case_exec) * 3);

  object_t* obj1 = create_new_int(2);
  object_t* obj2 = create_new_int(3);
  object_t* obj3 = create_new_string("Hello");
  object_t* obj4 = create_new_string(", World");
  object_t* obj5 = create_new_int(100);
  object_t* obj6 = create_new_int(30);

  program_t* program = create_program(vm);
  write_obj_memory(program, obj1, 0);
  write_obj_memory(program, obj2, 0);
  write_obj_memory(program, obj3, 0);
  write_obj_memory(program, obj4, 0);
  write_obj_memory(program, obj5, 0);
  write_obj_memory(program, obj6, 0);

  reg_t addresses1[2] = {obj1->address, obj2->address};
  command_t* cmd1 = create_command(ADD, addresses1, 2);

  reg_t addresses2[2] = {obj3->address, obj4->address};
  command_t* cmd2 = create_command(ADD, addresses2, 2);

  reg_t addresses3[2] = {obj5->address, obj6->address};
  command_t* cmd3 = create_command(SUBTRACT, addresses3, 2);

  write_cmd_memory(program, cmd1);
  write_cmd_memory(program, cmd2);
  write_cmd_memory(program, cmd3);

  load_program(vm, program);

  test_cases[0] = (test_case_exec){.cmd = cmd1, .desc = "Testing add operation", .output = {.data.v_int = 5, .type = INTEGER}, .vm = vm, .type = INTEGER};
  test_cases[1] = (test_case_exec){.cmd = cmd2, .desc = "Testing string concat", .output = {.data.v_string = "Hello, World", .type = STRING}, .vm = vm, .type = STRING};
  test_cases[2] = (test_case_exec){.cmd = cmd3, .desc = "Testing subtract operation", .output = {.data.v_int = 70, .type = INTEGER}, .vm = vm, .type = INTEGER};
  return test_cases;
}

