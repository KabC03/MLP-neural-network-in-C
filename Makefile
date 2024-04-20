all: main run
main: main
	clang main.c Matrix.c -o main
run: 
	clear
	./main
