CC = g++

CompileParms = -c -O0 -Wall -std=c++11

OBJS = main.o

Opdr: $(OBJS)
		$(CC) $(OBJS) -o a

main.o: main.cc node.h automaton.h basic.h
		$(CC) $(CompileParms)  main.cc