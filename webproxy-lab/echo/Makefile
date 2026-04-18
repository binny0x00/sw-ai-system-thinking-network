CC = gcc
CFLAGS = -g -Wall

all: echoserver echoclient

csapp.o: ../csapp.c ../csapp.h
	$(CC) $(CFLAGS) -c ../csapp.c -o csapp.o

echoserver.o: echoserver.c ../csapp.h
	$(CC) $(CFLAGS) -c echoserver.c

echoclient.o: echoclient.c ../csapp.h
	$(CC) $(CFLAGS) -c echoclient.c

echoserver: echoserver.o csapp.o
	$(CC) $(CFLAGS) echoserver.o csapp.o -o echoserver

echoclient: echoclient.o csapp.o
	$(CC) $(CFLAGS) echoclient.o csapp.o -o echoclient

clean:
	rm -f *~ *.o echoserver echoclient core
