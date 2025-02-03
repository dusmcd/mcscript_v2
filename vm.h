#ifndef _VM_H
#define _VM_H
#define MAX 0xffff

#include "object.h"
#include "stack.h"
#include "types.h"

typedef enum {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  NEW,
  OUTPUT,
  ASSIGN
} operation_t;

typedef struct {
  operation_t operation;
  int num_operands;
} instruction_t;

typedef struct {
  instruction_t instruction_set[6];
  reg_t registers[4]; // each reg will point to an address, which is an index to address_space
} cpu_t;


typedef struct {
  byte instr_idx;
  reg_t operands[2]; // address of object in address_space
  data_t val;
  type_t type;
} command_t;

typedef struct {// for simplicity's sake, we will only run one program at a time
  reg_t program_counter;
  void** address_space; // can address up to 2^16 memory addresses;
  reg_t stack_ptr; // the index for the current frame
  stack_t* frames; // all the call stack frames in a program
  reg_t cmd_start;
  reg_t cmd_end;
  reg_t obj_start;
  reg_t obj_end;
  reg_t current_addr_cmd;
  reg_t current_addr_obj;
} program_t;

typedef struct {
  cpu_t* cpu;
  program_t* current_program;
  reg_t limit; // equals MAX
} vm_t;

object_t* execute_command(vm_t* vm, command_t* cmd);
vm_t* create_vm();
command_t* create_command(operation_t op, reg_t* addresses, int num_ops);
program_t* create_program(vm_t* vm);
void free_vm(vm_t* vm);
void free_program(program_t* program);
void write_obj_memory(program_t* program, object_t* obj);
void write_cmd_memory(program_t* program, command_t* cmd);
void load_program(vm_t* vm, program_t* program);
object_t* add(object_t* left, object_t* right);
object_t* subtract(object_t* left, object_t* right);
object_t* multiply(object_t* left, object_t* right);
object_t* divide(object_t* left, object_t* right);
object_t* get_obj_from_memory(void** address_space, reg_t memory_addr);
object_t* create_new_object(data_t val, type_t type, program_t* program, reg_t address);

#endif