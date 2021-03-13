CC=gcc
CFLAGS=

all: client server

client : client.o mult.o
	$(CC) -o client -pthread client.o mult.o $(CFLAGS)

server : server.o mult.c mult.h
	$(CC) -o server -pthread server.o mult.o $(CFLAGS)

client.o : mult.h client.c
	$(CC) -o client.o -c client.c $(CFLAGS)

server.o : mult.h client.c
	$(CC) -o server.o -c server.c $(CFLAGS)
 
mult.o: mult.h
	$(CC) -o mult.o -c mult.c $(CFLAGS)

clean : 
	rm client.o server.o mult.o client server