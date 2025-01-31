# McScript v. 2.0

When I started McScript v. 1.0, I wasn't sure how far I could take it. It turns out,
I was able to build an interpreter that worked for some basic JavaScript-type code.
However, as I started adding more features, I realized the overall fragility of my design.
With that in mind, I decided to start over (this time in C because why not). My first step 
is to build an intermediary execution environment that can take in pre-defined commands 
(or instructions) and execute them (see *vm_t.h* and *vm_t.c*). I'm calling it a virtual machine, but
it's not a virtual machine in the traditional sense. Here is the basic idea:
    **Source Code** => **Tokens** => **VM Commands** => **Virtual Machine** => **Executable Program**

Once I have a functioning "virtual machine", I will need to figure out how to parse the source code and 
turn the given statements into commands that the VM can understand (see the `command_t struct` in *vm.h*).

## Instructions
- So far, the only thing that functions is some basic tests
- Run `make test` from the root project directory
- Run the created `test` executable (will be placed in root project directory)