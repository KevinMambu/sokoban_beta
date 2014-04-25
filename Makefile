CFLAGS= -Wall -ansi -pedantic -O3
CC= gcc
PROG = sokoban_beta

all:partie.o plateau.o main.o
	$(CC) $(CFLAGS) partie.o plateau.o main.o -o $(PROG)

plateau.o:plateau.c
	$(CC) -c $(CFLAGS) plateau.c

partie.o:partie.c
	$(CC) -c $(CFLAGS) partie.c

main.o:main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm *.o 2>/dev/null
