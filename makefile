CC = gcc
FLAGS = -Wall -g

all: stringProg
stringProg: main.c Digraph.c graph.h
	$(CC) $(FLAGS) main.c Digraph.c graph.h -o graph
.PHONY: clean all

clean:
	rm -f graph