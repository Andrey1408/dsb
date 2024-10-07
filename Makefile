
DC_DEBUG_PRINT := 0

all:
	clang -std=c99 -Wall -pedantic -Werror -D DC_DEBUG_PRINT='${DC_DEBUG_PRINT}' *.c -o main.c

run: all
	./main.c

clean:
	rm -f main.c
	rm -f *.log
	rm -rf cmake-build-debug/
