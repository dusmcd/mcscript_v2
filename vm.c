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
    {.num_operands = 2, .operation = NEW},
    {.num_operands = 1, .operation = ASSIGN}
  };
  for (int i = 0; i < 6; i++)
    cpu->instruction_set[i] = instruction_set[i];

  vm->cpu = cpu;
  vm->limit = MAX - 1;

  return vm; 
}

void free_vm(vm_t* vm) {
  if (vm->cpu != NULL)
    free(vm->cpu);
  
  if (vm != NULL)
    free(vm);

  vm = NULL;
}

void free_program(program_t* program) {
  if (program->address_space != NULL) {
    for (reg_t i = 0; i <= program->current_addr_obj; i++) {
      if (program->address_space[i] == 0)
        continue;
      free(program->address_space[i]);
    }
    free(program->address_space);
    program->address_space = NULL;
  }
  free(program);
  program = NULL;
}


object_t* execute_command(vm_t* vm, command_t* cmd) {
  instruction_t instr = vm->cpu->instruction_set[cmd->instr_idx];
  operation_t op = instr.operation;
  void** address_space = vm->current_program->address_space;
  switch(op) {
    case ADD: {
      object_t* left = get_obj_from_memory(address_space, cmd->operands[0]);
      object_t* right = get_obj_from_memory(address_space, cmd->operands[1]);

      return add(left, right);
      break;
    }
    case SUBTRACT: {
      object_t* left = get_obj_from_memory(address_space, cmd->operands[0]);
      object_t* right = get_obj_from_memory(address_space, cmd->operands[1]);

      return subtract(left, right);
      break;
    }
    case MULTIPLY: {
      object_t* left = get_obj_from_memory(address_space, cmd->operands[0]);
      object_t* right = get_obj_from_memory(address_space, cmd->operands[1]);
      
      return multiply(left, right);
      break;
    }
    case DIVIDE: {
      object_t* left = get_obj_from_memory(address_space, cmd->operands[0]);
      object_t* right = get_obj_from_memory(address_space, cmd->operands[1]);
      
      return divide(left, right);
      break;
    }
    case NEW: {
      return create_new_object(cmd->val, cmd->type, vm->current_program, 0);
    }
    case ASSIGN: {
      // first operand is address of object being assigned to
      return create_new_object(cmd->val, cmd->type, vm->current_program, cmd->operands[0]);
    }
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

object_t* get_obj_from_memory(void** address_space, reg_t memory_addr) {
  if (address_space == NULL)
    return NULL;
  
  if (memory_addr > MAX)
    return NULL;
  
  object_t* obj = (object_t*)address_space[memory_addr];

  return obj;
}

int get_instr_idx(operation_t op) {
  switch(op) {
    case ADD:
      return 0;
    case SUBTRACT:
      return 1;
    case MULTIPLY:
      return 2;
    case DIVIDE:
      return 3;
    default:
      return -1;
  }
  return -1;
}

command_t* create_command(operation_t op, reg_t* addresses, int num_ops) {
  command_t* cmd = malloc(sizeof(command_t));
  if (cmd == NULL)
    return NULL;
  
  cmd->instr_idx = get_instr_idx(op);
  for (int i = 0; i < num_ops; i++) {
    cmd->operands[i] = addresses[i];
  }

  return cmd;
}

program_t* create_program(vm_t* vm) {
  program_t* program = malloc(sizeof(program_t));
  if (program == NULL)
    return NULL;
  
  void** memory = malloc(sizeof(void*) * MAX);
  if (memory == NULL) {
    return NULL;
  }

  program->address_space = memory;
  program->cmd_start = 0x0;
  program->cmd_end = 0x8000 - 1;
  program->obj_start = 0x8000;
  program->obj_end = vm->limit;

  program->current_addr_cmd = program->cmd_start;
  program->current_addr_obj = program->obj_start;
  
  return program;
}


void write_obj_memory(program_t* program, object_t* obj) {
  if (program == NULL || obj == NULL)
    return;
  
  reg_t next_address = program->current_addr_obj;
  if (next_address >= program->obj_end)
    exit(1);

  obj->address = next_address;
  program->address_space[next_address] = obj;

  program->current_addr_obj++;
}

void write_cmd_memory(program_t* program, command_t* cmd) {
  if (program == NULL || cmd == NULL)
    return;
  
  reg_t next_address = program->current_addr_cmd;
  if (next_address >= program->cmd_end)
    exit(1);

  program->address_space[next_address] = cmd;

  program->current_addr_cmd++;
}

void load_program(vm_t* vm, program_t* program) {
  vm->current_program = program;
}

object_t* create_new_object(data_t val, type_t type, program_t* program, reg_t address) {
  if (program == NULL)
    return NULL;
  
  switch(type) {
    case INTEGER: {
      object_t* obj = create_new_int(val.v_int);
      if (address == 0)
        write_obj_memory(program, obj);
      else
        program->address_space[address] = obj;
      return obj;
    }
    case STRING: {
      object_t* obj = create_new_string(val.v_string);
      if (address == 0)
        write_obj_memory(program, obj);
      else
        program->address_space[address] = obj;
      return obj;
    }
    case NONE: {
      // meaning we are simply creating an object in memory without data (e.g., var num;)
      object_t* obj = malloc(sizeof(object_t));
      if (obj == NULL) {
        return NULL;
      }
      obj->type = NONE;
      write_obj_memory(program, obj);
      return obj;
    }
    default: {
      return NULL;
    }
  }

  return NULL;
}