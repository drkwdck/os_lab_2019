
CC=gcc
CFLAGS=-I.


all : process_memory parallel_sum zombie

process_memory : process_memory.c 
	$(CC) -o process_memory process_memory.c

parallel_sum : utils.o utils.h parallel_sum.o
	$(CC) -o parallel_sum -pthread utils.o parallel_sum.o

zombie : 
	$(CC) -o zombie zombie.c $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c -std=c99 utils.c $(CFLAGS)


parallel_sum.o : utils.h
	$(CC) -o parallel_sum.o -c -std=c99 parallel_sum.c $(CFLAGS)

clean :
	rm utils.o parallel_sum.o process_memory parallel_sum zombie