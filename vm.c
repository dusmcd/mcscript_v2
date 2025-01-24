#include "vm.h"
#include <stdlib.h>

vm_t* create_vm()
{
  vm_t* vm = malloc(sizeof(vm_t));
  if (vm == NULL)
    return NULL;
  
  cpu_t* cpu = malloc(sizeof(cpu_t));
  if (cpu == NULL)
    return NULL;
  
  instruction_t instruction_set[6] = {
    {.num_operands = 2, .operation = ADD},
    {.num_operands = 2, .operation = SUBTRACT},
    {.num_operands = 2, .operation = MULTIPLY},
    {.num_operands = 2, .operation = DIVIDE},
    {.num_operands = 2, .operation = ASSIGN},
    {.num_operands = 2, .operation = ALLOCATE},
  };
  for (int i = 0; i < 6; i++)
    cpu->instruction_set[i] = instruction_set[i];

  vm->cpu = cpu;

  return vm; 
}

void free_vm(vm_t* vm)
{
  free(vm->cpu);
  free(vm);

  vm = NULL;
}

void execute_command(vm_t* vm, command_t* cmd)
{
  operation_t op = vm->cpu->instruction_set[cmd->instr_idx].operation;
  switch(op)
  {
    case ADD:
      // call add function
      break;
    case SUBTRACT:
      // call subtract function
      break;
    case MULTIPLY:
      // call multiply function
      break;
    case DIVIDE:
      // call divide function
      break;
    case ALLOCATE:
      // make space for a command and identify it
      break;
    case ASSIGN:
      // put a value in memory
      break;
    default:
      exit(1);
  }
}