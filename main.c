#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plateau.h"
#include "editeur.h"

int main()
{
	int win = 0;
	int i = 0;
	plateau_t * test = creer_plateau(6,6);
	player_t * J1 = creer_joueur(3,4,test);
	mur(test,1,1);
	mur(test,4,4);
	muraille_x(test,1,0,(test -> h - 1));
	muraille_x(test,0,(test -> l - 1),(test -> h - 1));
	muraille_y(test,0,1,(test -> l-1));
	muraille_y(test,(test -> h - 1),0,(test -> l - 1));
	while (!win)
	{
	system("clear");
	printf("\nNombre de coups: %d\n", i);
	printf("%dx%d\n", J1 -> x, J1 -> y);
	afficher_plateau(test);
	deplacer_joueur(J1, test);
	i += 1;
	}
	return EXIT_SUCCESS;
}
