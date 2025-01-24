#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

int main()
{
  vm_t* vm = create_vm();
  printf("Vitrual Machine created...\n");
  object_t* left = malloc(sizeof(object_t));
  object_t* right = malloc(sizeof(object_t));

  left->data.v_int = 2;
  left->type = INTEGER;

  right->data.v_int = 3;
  left->type = INTEGER;

  command_t* cmd = malloc(sizeof(command_t));
  cmd->instr_idx = 0;
  object_t** operands = malloc(sizeof(object_t*));

  operands[0] = left;
  operands[1] = right;

  cmd->operands = operands;

  object_t* sum = execute_command(vm, cmd);

  printf("The resulting sum of %i + %i = %i\n", left->data.v_int, right->data.v_int, sum->data.v_int);
  free_vm(vm);
  free(cmd);
  cmd = NULL;
  return 0;
}