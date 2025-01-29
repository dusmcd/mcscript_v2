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
  ALLOCATE,
  ASSIGN,
  OUTPUT
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
  byte operands[2]; // 0-3 indicating which register to look at for value
} command_t;

typedef struct {// for simplicity's sake, we will only run one program at a time
  reg_t program_counter;
  void** address_space; // can address up to 2^16 memory addresses;
  reg_t stack_ptr; // the index for the current frame
  stack_t* frames; // all the call stack frames in a program
} program_t;

typedef struct {
  cpu_t* cpu;
  program_t* current_program;
  reg_t limit; // equals MAX
} vm_t;

object_t* execute_command(vm_t* vm, command_t* cmd);
vm_t* create_vm();
void free_vm(vm_t* vm);
void load_program(vm_t* vm);
object_t* add(object_t* left, object_t* right);
object_t* subtract(object_t* left, object_t* right);
object_t* multiply(object_t* left, object_t* right);
object_t* divide(object_t* left, object_t* right);
object_t* get_obj_from_memory(vm_t* vm, int reg_idx);
reg_t allocate(vm_t vm);
void assign(object_t* memory_addr, void* val);

#endif