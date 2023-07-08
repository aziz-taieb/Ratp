CC=gcc -Wall
CFLAGS=-I.

all: main

main: main.o projet.o
	$(CC) main.o projet.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

projet.o: projet.c projet.h
	$(CC) $(CFLAGS) -c projet.c
