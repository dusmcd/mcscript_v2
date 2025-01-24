#include "vm.h"
#include <stdlib.h>
#include <string.h>

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
  vm->limit = MAX;

  return vm; 
}

void free_vm(vm_t* vm)
{
  if (vm->cpu != NULL)
    free(vm->cpu);
  
  if (vm != NULL)
    free(vm);

  vm = NULL;
}

object_t* execute_command(vm_t* vm, command_t* cmd)
{
  instruction_t instr = vm->cpu->instruction_set[cmd->instr_idx];
  operation_t op = instr.operation;
  switch(op)
  {
    case ADD:
      // call add function
      return add(cmd->operands[0], cmd->operands[1]);
      break;
    case SUBTRACT:
      // call subtract function
      return subtract(cmd->operands[0], cmd->operands[1]);
      break;
    case MULTIPLY:
      // call multiply function
      return multiply(cmd->operands[0], cmd->operands[1]);
      break;
    case DIVIDE:
      // call divide function
      return divide(cmd->operands[0], cmd->operands[1]);
      break;
    case ALLOCATE:
      // make space for a command and identify it
      break;
    case ASSIGN:
      // put a value in memory
      break;
    default:
      return NULL;
  }
}

object_t* add(object_t* left, object_t* right)
{
  if (left == NULL || right == NULL)
    return NULL;

  switch(left->type)
  {
    case INTEGER:
      if (right->type == INTEGER)
      {
        int sum = left->data.v_int + right->data.v_int;
        object_t* obj = malloc(sizeof(obj));
        obj->data.v_int = sum;
        obj->type = INTEGER;
        return obj;
      }
      else
        return NULL;
    case STRING:
      if (right->type == STRING)
      {
        char* cat = strcat(left->data.v_string, right->data.v_string);
        int length = strlen(left->data.v_string) + strlen(right->data.v_string);
        char* new_str = malloc(length + 1);
        strcpy(new_str, cat);

        object_t* obj = malloc(sizeof(obj));
        obj->data.v_string = new_str;
        obj->type = STRING;
        return obj;
      }
      return NULL;
    default:
    {
      return NULL;
    }
  }
}

object_t* subtract(object_t* left, object_t* right)
{
  if (left == NULL || right == NULL)
    return NULL;

  switch(left->type)
  {
    case INTEGER:
      if (right->type == INTEGER)
      {
        int diff = left->data.v_int - right->data.v_int;
        object_t* obj = malloc(sizeof(object_t));
        obj->data.v_int = diff;
        obj->type = INTEGER;

        return obj;
      }
      return NULL;
    default:
      return NULL;
  }
}
object_t* multiply(object_t* left, object_t* right)
{
  if (left == NULL || right == NULL)
    return NULL;
  
  switch (left->type)
  {
    case INTEGER:
      if (right->type == INTEGER)
      {
        int product = left->data.v_int * right->data.v_int;
        object_t* obj = malloc(sizeof(object_t));
        obj->data.v_int = product;
        obj->type = INTEGER;
        return obj;
      }
      return NULL;
    default:
      return NULL;
  }
}
object_t* divide(object_t* left, object_t* right)
{
  if (left == NULL || right == NULL)
    return NULL;
  
  switch(left->type)
  {
    case INTEGER:
      if (right->type == INTEGER)
      {
        int quot = left->data.v_int / right->data.v_int;
        object_t* obj = malloc(sizeof(object_t));
        obj->data.v_int = quot;
        obj->type = INTEGER;
        return obj;
      }
      return NULL;
    default:
      return NULL;
  }
}
