#ifndef _VM_H
#define _VM_H

#include <stdint.h>

typedef uint16_t reg_t; // 16 bit machine
typedef unsigned char byte;

typedef enum
{
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  ALLOCATE,
  ASSIGN
} operation_t;

typedef struct
{
  operation_t operation;
  int num_operands;
} instruction_t;

typedef struct
{
  instruction_t instruction_set[6];
  reg_t rega;
  reg_t regb;
  reg_t regc;
  reg_t regd;
} cpu_t;

typedef struct
{
  reg_t capacity;
  reg_t count;
  void** data;
  reg_t base_pointer; // this will serve as an unchanging reference that can be offset to retrieve data
} stack_t;

typedef struct
{
  byte instr_idx;
  void** operands;
} command_t;

typedef struct // for simplicity's sake, we will only run one program at a time
{
  reg_t program_counter;
  command_t* address_space[0xffff]; // can address up to 2^16 memory addresses; will hold commands for program to execute
  reg_t stack_ptr; // the index for the current frame
  stack_t* frames; // all the call stack frames in a program
} program_t;

typedef struct
{
  cpu_t* cpu;
  program_t* current_program;
} vm_t;

void execute_command(vm_t* vm, command_t* cmd);
vm_t* create_vm();
void load_program(vm_t* vm);
reg_t add(reg_t left, reg_t right);
reg_t subtract(reg_t left, reg_t right);
reg_t multiply(reg_t left, reg_t right);
reg_t divide(reg_t left, reg_t right);
reg_t allocate();
void assign(reg_t memory_addr, void* val);

#endif