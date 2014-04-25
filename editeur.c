#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "editeur.h"

void mur(plateau_t * p, int x, int y)
{
	p -> statique[x][y] = 'M';
}

void arrivee(plateau_t * p, int x, int y)
{
	p -> statique[x][y] = 'A';
}

void muraille_x(plateau_t * p, int x, int y, int longueur)
{
	int i;
	for(i = x; i < (x + longueur); i += 1)
	{
		mur(p,i,y);
	}
}


void muraille_y(plateau_t * p, int x, int y, int longueur)
{
	int i;
	for(i = y; i < (y + longueur); i += 1)
	{
		mur(p,x,i);
	}
}
