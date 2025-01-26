all: build_matrix compile run clean

build_matrix:
	python3 create-matrix.py 4 > graph.txt
compile:	
	gcc main.c vertex.h vertex.c -o main.o
run:
	./main.o < graph.txt
clean:
	rm -f main.o graph.txt