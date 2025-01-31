# McScript v. 2.0

- When I started McScript v. 1.0, I wasn't sure how far I could take it
- It turns out, I was able to build an interpreter that worked for some basic JavaScript-type code
- However, as I started adding more features, I realized the overall fragility of my design
- With that in mind, I decided to start over (this time in C because why not)
- My first step is to build a (sort of) virtual machine (see vm_t.h and vm_t.c) that can execute some simple commands
- Once I have a functioning virtual machine, I will need to figure out how to parse source code and turn them into commands
  that the VM can understand (see the command_t struct in vm.h)

## Instructions
- So far, the only that functions is some basic tests
- Run `make test` from the root project directory
- Run the created `test` executable (will be placed in root project directory)