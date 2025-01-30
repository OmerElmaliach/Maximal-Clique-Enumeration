files = main.c vertex.h vertex.c
all: build_matrix compile run clean

build_matrix:
	@python3 create-matrix.py 20 > graph.txt
compile:	
	@gcc $(files) -o maxclique.o
run:
	@./maxclique.o < graph.txt
clean:
	@rm -f maxclique.o graph.txt