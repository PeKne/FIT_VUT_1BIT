# Soubor: Makefile
# Predmet: Cviceni IZP 
# Datum: Listopad 2016

CC=gcc
FLAGS=-std=c99 -pedantic -Wall -Wextra -g

all: main.o struct.o array.o
	$(CC) $(FLAGS) main.o struct.o array.o -o main

main.o: main.c
	$(CC) $(FLAGS) -c main.c

struct.o: struct.c struct.h
	$(CC) $(FLAGS) -c struct.c

array.o: array.c array.h
	$(CC) $(FLAGS) -c array.c


clean:
	rm array.o test.o struct.o main
