flags = -Wall -g
target = ./bin/main
test_path = ./tests
src_path = ./src
test_target = ./bin/test

vm.o: $(src_path)/vm.c $(src_path)/vm.h
	gcc $< $(flags) -c

object.o: $(src_path)/object.c $(src_path)/object.h
	gcc $< $(flags) -c

list.o: $(src_path)/utils/list.c $(src_path)/utils/list.h
	gcc $< $(flags) -c

str_utils.o: $(src_path)/utils/str_utils.c $(src_path)/utils/str_utils.h
	gcc $< $(flags) -c

parser.o: $(src_path)/parser.c $(src_path)/parser.h
	gcc $< $(flags) -c

test_vm.o: $(test_path)/test_vm.c $(test_path)/test_vm.h
	gcc $< $(flags) -c

test_utils.o: $(test_path)/test_utils.c $(test_path)/test_utils.h
	gcc $< $(flags) -c

test.o: $(test_path)/test.c
	gcc $< $(flags) -c


main.o: $(src_path)/main.c
	gcc $< $(flags) -c

main: vm.o object.o list.o parser.o str_utils.o main.o
	gcc $^ -o $(target)

test: test.o test_vm.o vm.o object.o list.o str_utils.o test_utils.o
	gcc $^ -o $(test_target)

clean:
	rm *.o $(target) $(test_target)