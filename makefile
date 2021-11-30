CC = g++

CompileParms = -c -O0 -Wall -std=c++11

OBJS = main.o automaton.o node.o basic.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o main

basic.o: basic.cc basic.h
	$(CC) $(CompileParms) basic.cc

node.o: node.cc node.h basic.h
	$(CC) $(CompileParms) node.cc

automaton.o: automaton.cc automaton.h node.h basic.h
	$(CC) $(CompileParms) automaton.cc

main.o: main.cc node.h automaton.h basic.h
	$(CC) $(CompileParms)  main.cc
