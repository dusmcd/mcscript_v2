#include "vm.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

vm_t* create_vm() {
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

void free_vm(vm_t* vm) {
  if (vm->cpu != NULL)
    free(vm->cpu);
  
  if (vm != NULL)
    free(vm);

  vm = NULL;
}


object_t* execute_command(vm_t* vm, command_t* cmd) {
  instruction_t instr = vm->cpu->instruction_set[cmd->instr_idx];
  operation_t op = instr.operation;
  switch(op) {
    case ADD: {
      object_t* left = get_obj_from_memory(vm, cmd->operands[0]);
      object_t* right = get_obj_from_memory(vm, cmd->operands[1]);

      return add(left, right);
      break;
    }
    case SUBTRACT: {
      object_t* left = get_obj_from_memory(vm, cmd->operands[0]);
      object_t* right = get_obj_from_memory(vm, cmd->operands[1]);

      return subtract(left, right);
      break;
    }
    case MULTIPLY: {
      object_t* left = get_obj_from_memory(vm, cmd->operands[0]);
      object_t* right = get_obj_from_memory(vm, cmd->operands[1]);
      
      return multiply(left, right);
      break;
    }
    case DIVIDE: {
      object_t* left = get_obj_from_memory(vm, cmd->operands[0]);
      object_t* right = get_obj_from_memory(vm, cmd->operands[1]);
      
      return divide(left, right);
      break;
    }
    case ALLOCATE:
      // make space for a command and identify it
      break;
    case ASSIGN:
      // put a value in memory
      break;
    default:
      return NULL;
  }
  return NULL;
}

object_t* add(object_t* left, object_t* right) {
  if (left == NULL || right == NULL)
    return NULL;

  switch(left->type) {
    case INTEGER:
      if (right->type == INTEGER) {
        int sum = left->data.v_int + right->data.v_int;
        object_t* obj = create_new_int(sum);
        return obj;
      }
      else
        return NULL;
    case STRING:
      if (right->type == STRING) {
        char* cat = strcat(left->data.v_string, right->data.v_string);
        object_t* obj = create_new_string(cat);
        return obj;
      }
      return NULL;
    default: {
      return NULL;
    }
  }
}

object_t* subtract(object_t* left, object_t* right) {
  if (left == NULL || right == NULL)
    return NULL;

  switch(left->type) {
    case INTEGER:
      if (right->type == INTEGER) {
        int diff = left->data.v_int - right->data.v_int;
        object_t* obj = create_new_int(diff);

        return obj;
      }
      return NULL;
    default:
      return NULL;
  }
}
object_t* multiply(object_t* left, object_t* right) {
  if (left == NULL || right == NULL)
    return NULL;
  
  switch (left->type) {
    case INTEGER:
      if (right->type == INTEGER) {
        int product = left->data.v_int * right->data.v_int;
        object_t* obj = create_new_int(product);
        return obj;
      }
      return NULL;
    default:
      return NULL;
  }
}
object_t* divide(object_t* left, object_t* right) {
  if (left == NULL || right == NULL)
    return NULL;
  
  switch(left->type) {
    case INTEGER:
      if (right->type == INTEGER) {
        int quot = left->data.v_int / right->data.v_int;
        object_t* obj = create_new_int(quot);
        return obj;
      }
      return NULL;
    default:
      return NULL;
  }
}

object_t* get_obj_from_memory(vm_t* vm, int reg_idx) {
  cpu_t* cpu = vm->cpu;
  reg_t memory_addr = cpu->registers[reg_idx];

  object_t* obj = vm->current_program->address_space[memory_addr];
  if (obj == NULL)
    return NULL;
  
  return obj;
}