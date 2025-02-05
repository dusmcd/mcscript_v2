flags = -Wall -g
target = ./bin/main
test_path = ./tests
src_path = ./src
test_target = ./bin/test

vm.o: $(src_path)/vm.c $(src_path)/vm.h
	gcc $< $(flags) -c

object.o: $(src_path)/object.c $(src_path)/object.h
	gcc $< $(flags) -c

test_vm.o: $(test_path)/test_vm.c $(test_path)/test_vm.h
	gcc $< $(flags) -c

test.o: $(test_path)/test.c
	gcc $< $(flags) -c


main.o: $(src_path)/main.c
	gcc $< $(flags) -c

main: vm.o object.o main.o
	gcc $^ -o $(target)

test: test.o test_vm.o vm.o object.o
	gcc $^ -o $(test_target)

clean:
	rm *.o $(target) $(test_target)