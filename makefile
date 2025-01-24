flags = -Wall
target = main

vm.o: vm.c vm.h
	gcc $< $(flags) -c

main.o: main.c
	gcc $< $(flags) -c

main: vm.o main.o
	gcc $^ -o $(target)

clean:
	rm *.o main