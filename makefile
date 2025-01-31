flags = -Wall -g
target = main
test_path = ./tests
test_target = test

vm.o: vm.c vm.h
	gcc $< $(flags) -c

object.o: object.c object.h
	gcc $< $(flags) -c

test_vm.o: $(test_path)/test_vm.c $(test_path)/test_vm.h
	gcc $< $(flags) -c

test.o: $(test_path)/test.c
	gcc $< $(flags) -c


main.o: main.c
	gcc $< $(flags) -c

main: vm.o object.o main.o
	gcc $^ -o $(target)

test: test.o test_vm.o vm.o object.o
	gcc $^ -o $(test_target)

clean:
	rm *.o $(target) $(test_target)