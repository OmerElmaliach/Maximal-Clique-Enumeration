all: build run clean

build:	
	gcc main.c -o main.o
run:
	./main.o
clean:
	rm -f main.o