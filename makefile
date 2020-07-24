all: compile run

compile: pagerank.c 
	gcc pagerank.c -lm
run: a.out
	./a.out <input.txt
