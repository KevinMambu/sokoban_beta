CFLAGS=-g -Wall -ansi -pedantic -O3

all:plateau.o main.o editeur.o
	gcc $(CFLAGS) plateau.o main.o editeur.o

plateau.o:plateau.c
	gcc -c $(CFLAGS) plateau.c

main.o:main.c
	gcc -c $(CFLAGS) main.c

editeur.o:editeur.c
	gcc -c $(CFLAGS) editeur.c

clean:
	rm *.o 2>/dev/null
