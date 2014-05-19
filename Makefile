FLAGS = -Wall -Wextra -Werror -pedantic -ansi -I./include

ALL_C_FILES = $(wildcard ./src/*.c)

default:
	@echo "\nCreating shared library.."
	mkdir -p shared
	gcc -fPIC -c $(ALL_C_FILES) $(FLAGS)
	gcc -shared -o ./shared/libds.so *.o
	rm *.o
	@echo "DONE"
.PHONY: default

tests: slist hash bst bheap vector clean
.PHONY: tests

slist:
	@mkdir -p bin
	@gcc ./src/slist.c ./tests/test_slist.c -o ./bin/test_slist $(FLAGS) -g
	@./bin/test_slist
.PHONY: slist

hash:
	@mkdir -p bin
	@gcc ./src/hash.c ./tests/test_hash.c -o ./bin/test_hash $(FLAGS) -g
	@./bin/test_hash
.PHONY: hash

bst:
	@mkdir -p bin
	@gcc ./src/bst.c ./tests/test_bst.c -o ./bin/test_bst $(FLAGS) -g
	@./bin/test_bst
.PHONY: bst

bheap:
	@mkdir -p bin
	@gcc ./src/bheap.c ./src/vector.c ./tests/test_bheap.c -o ./bin/test_bheap $(FLAGS) -g
	@./bin/test_bheap
.PHONY: bheap 

vector:
	@mkdir -p bin
	@gcc ./src/vector.c ./tests/test_vector.c -o ./bin/test_vector $(FLAGS) -g
	@./bin/test_vector
.PHONY: vector

clean:
	@echo "\nCleaning up.."
	@rm -rf ./bin
	@rm -rf ./shared
	@echo "DONE"
.PHONY: clean
