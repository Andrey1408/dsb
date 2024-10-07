all:
	clang-3.5 -std=c99 -Wall -pedantic -Werror  *.c -o main.c

run: all
	./main.c

clean:
	rm -f main.c
	rm -f *.log
	rm -rf cmake-build-debug/