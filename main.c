#include <stdio.h>
#include "vm.h"

int main()
{
  vm_t* vm = create_vm();
  printf("Vitrual Machine created...\n");
  return 0;
}