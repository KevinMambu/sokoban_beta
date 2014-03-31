#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plateau.h"



plateau_t * creer_plateau( int h, int l)
{
	int i;
	int j;
	plateau_t * res = (plateau_t *)malloc(sizeof(plateau_t));

	res -> statique = (char * *)malloc(sizeof(char *)*h);
	res -> mobile = (char * *)malloc(sizeof(char *)*h);
	for(i = 0; i < h; i += 1)
	{
	 	res -> statique[i] = (char *)malloc(sizeof(char)*l);
		res -> mobile[i] = (char *)malloc(sizeof(char)*l);
	}

	for(i = 0; i < h; i += 1)
	{
		for(j = 0; j < l; j += 1)
		{
			res -> statique[i][j] = '.';
			printf("%c", res -> statique[i][j]);
		}
		printf("\n");
	} 

	printf("\n\n");


	for(i = 0; i < h; i += 1)
	{
		for(j = 0; j < l; j += 1)
		{
			res -> mobile[i][j] = ' ';
			printf("%c", res -> mobile[i][j]);
		}
		printf("\n");
	} 
	
	res -> h = h;
	res -> l = l;

	return res;
}


void afficher_plateau(plateau_t * p)
{
	int i;
	int j;
	for ( i = 0 ; i < p -> h ; i += 1 ) 
	{
		for ( j = 0 ; j < p -> l ; j += 1 )
		{
			if((p -> mobile[i][j] == 'P')||(p -> mobile[i][j] == 'C'))
			{
			printf("%c  ", p -> mobile[i][j]);
			}
			else
			{
			printf("%c  ", p -> statique[i][j]);
			}
		}
		printf("\n");
	}
}

char contenu_case(plateau_t * p, int x, int y)
{
	return p -> statique[y][x];
}

void modifier_contenu_case(plateau_t * p, int x, int y, char v)
{
	p -> mobile[x][y] = v;
}

int coup_autorise(plateau_t * p, player_t * j, char c)
{
	switch(c)
	{
		case 'q':
			if(contenu_case(p,(j -> x - 1),(j -> y)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'Q':
			if(contenu_case(p,(j -> x - 1),(j -> y)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'z':
			if(contenu_case(p,(j -> x),(j -> y - 1)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'Z':
			if(contenu_case(p,(j -> x),(j -> y - 1)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 's':
			if(contenu_case(p,(j -> x),(j -> y + 1)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'S':
			if(contenu_case(p,(j -> x),(j -> y + 1)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'd':
			if(contenu_case(p,(j -> x + 1),(j -> y)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'D':
			if(contenu_case(p,(j -> x + 1),(j -> y)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
	}
}

void deplacer_joueur(player_t * j, plateau_t * p)
{
	char key;
	modifier_contenu_case(p, j -> y, j -> x, ' ');
	key = getchar();
	getchar();
	switch(key)
	{
		case 'q':
			if (coup_autorise(p,j,key) == 1)
			{
			j -> x -= 1;
			}
			break;
		case 'Q':
			if (coup_autorise(p,j,key) == 1)
			{
			j -> x -= 1;
			}
			break;
		case 'z':
			if (coup_autorise(p,j,key) == 1)
			{
			j -> y -= 1;
			}
			break;
		case 'Z':
			if (coup_autorise(p,j,key) == 1)
			{
			j -> y -= 1;
			}
			break;
		case 's':
			if (coup_autorise(p,j,key) == 1)
			{
			j -> y += 1;
			}
			break;
		case 'S':
			if (coup_autorise(p,j,key) == 1)
			{
			j -> y += 1;
			}
			break;
		case 'd':
			if (coup_autorise(p,j,key) == 1)
			{
			j -> x += 1;
			}
			break;
		case 'D':
			if (coup_autorise(p,j,key) == 1)
			{
			j -> x += 1;
			}
			break;
		default:
			printf("\nNo Habla Espanol\n");
	}
	modifier_contenu_case(p, j -> y, j -> x, 'P');
}

player_t * creer_joueur(int x, int y, plateau_t * p)
{
	player_t * res = (player_t *)malloc(sizeof(player_t));
	res -> x = x;
	res -> y = y;
	modifier_contenu_case(p, res -> x, res -> y, 'P');
	return res;
}
