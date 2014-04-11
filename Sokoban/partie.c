#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plateau.h"
#include "partie.h"

partie_t * creer_partie(const char * nom_fichier, const char * nom_joueur)
{
    int i;
    int j;
    int k;
    partie_t * res = (partie_t *)malloc(sizeof(partie_t));


    res -> plateau = charger_plateau(nom_fichier);


    res -> score = 0;


    res -> nb_arrivees = 0;


    res -> nb_coups = 0;

    for(i = 0; i < res -> plateau -> h; i += 1)
    {
        for(j = 0; j < res -> plateau -> l; j += 1)
        {
            if(res -> plateau -> statique[i][j] == 'A')
            {
                res -> nb_arrivees += 1;
            }
        }
    }

    res -> liste_arrivees = (int * *)malloc(sizeof(int *)*(res -> nb_arrivees));
    for(i = 0; i < res -> nb_arrivees; i += 1)
    {
        res -> liste_arrivees[i] = (int *)malloc(sizeof(int)*2);
    }

    for(k = 0; k < res -> nb_arrivees; k += 1)
    {
        for(i = 0; i < res -> plateau -> h; i += 1)
        {
            for(j = 0; j < res -> plateau -> l; j += 1)
            {
                if(res -> plateau -> statique[i][j] == 'A')
                {
                    res -> liste_arrivees[k][0] = i;
                    res -> liste_arrivees[k][1] = j;
                }
            }
        }
    }


    res -> joueur = (player_t *)malloc(sizeof(player_t));
    res -> joueur -> nom = (char *)malloc(sizeof(char)*(strlen(nom_joueur) + 1));
    res -> joueur -> nom = strcpy(res -> joueur -> nom, nom_joueur);
    for(i = 0; i < res -> plateau -> h; i += 1)
    {
        for(j = 0; j < res -> plateau -> l; j += 1)
        {
            if(res -> plateau -> mobile[i][j] == 'P')
            {
                res -> joueur -> x = i;
                res -> joueur -> y = j;
            }
        }
    }
    return res;
}

int coup_autorise(partie_t * partie, char c)
{
    switch(c)
	{
		case 'q':
			if(contenu_case(partie -> plateau,(partie -> joueur -> x - 1),(partie -> joueur -> y)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'Q':
			if(contenu_case(partie -> plateau,(partie -> joueur -> x - 1),(partie -> joueur -> y)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'z':
			if(contenu_case(partie -> plateau,(partie -> joueur -> x),(partie -> joueur -> y - 1)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'Z':
			if(contenu_case(partie -> plateau,(partie -> joueur -> x),(partie -> joueur -> y - 1)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 's':
			if(contenu_case(partie -> plateau,(partie -> joueur -> x),(partie -> joueur -> y + 1)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'S':
			if(contenu_case(partie -> plateau,(partie -> joueur -> x),(partie -> joueur -> y + 1)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'd':
			if(contenu_case(partie -> plateau,(partie -> joueur -> x + 1),(partie -> joueur -> y)) != 'M')
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case 'D':
			if(contenu_case(partie -> plateau,(partie -> joueur -> x + 1),(partie -> joueur -> y)) != 'M')
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

void detruire_partie(partie_t * partie)
{
    int i;
    detruire_plateau(partie ->plateau);
    free(partie -> joueur -> nom);
    free(partie -> joueur);
    for(i = 0; i < partie ->nb_arrivees; i += 1)
    {
        free(partie -> liste_arrivees[i]);
    }
    free(partie -> liste_arrivees);
    free(partie);
}

void jouer_coup(partie_t * partie)
{
    char key;
	modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
	key = getchar();
	getchar();
	switch(key)
	{
		case 'q':
			if (coup_autorise(partie, key) == 1)
			{
			partie ->joueur -> x -= 1;
			partie ->nb_coups += 1;
			}
			break;
		case 'Q':
			if (coup_autorise(partie, key) == 1)
			{
			partie ->joueur -> x -= 1;
			partie ->nb_coups += 1;
			}
			break;
		case 'z':
			if (coup_autorise(partie, key) == 1)
			{
			partie ->joueur -> y -= 1;
			partie ->nb_coups += 1;
			}
			break;
		case 'Z':
			if (coup_autorise(partie, key) == 1)
			{
			partie ->joueur -> y -= 1;
			partie ->nb_coups += 1;
			}
			break;
		case 's':
			if (coup_autorise(partie, key) == 1)
			{
			partie ->joueur -> y += 1;
			partie ->nb_coups += 1;
			}
			break;
		case 'S':
			if (coup_autorise(partie, key) == 1)
			{
			partie ->joueur -> y += 1;
			partie ->nb_coups += 1;
			}
			break;
		case 'd':
			if (coup_autorise(partie, key) == 1)
			{
			partie ->joueur -> x += 1;
			partie ->nb_coups += 1;
			}
			break;
		case 'D':
			if (coup_autorise(partie, key) == 1)
			{
			partie ->joueur -> x += 1;
			partie ->nb_coups += 1;
			}
			break;
		default:
			printf("\nLa touche n'a pas été reconnue\n");
	}
	modifier_contenu_case(partie -> plateau, partie ->joueur -> y, partie ->joueur -> x, 'P');
}

int partie_terminee(partie_t * partie)
{
    int i;
    int j;
    int k;
    int cmpt = 0;
    for(k = 0; k < partie -> nb_arrivees; k += 1)
    {
        for(i = 0; i < partie -> plateau -> h; i += 1)
        {
            for(j = 0; j < partie -> plateau -> l; j += 1)
            {
                if(partie -> plateau -> mobile[partie -> liste_arrivees[k][0]][partie -> liste_arrivees[k][1]] == 'C')
                {
                    cmpt += 1;
                }
            }
        }
    }
    if(cmpt == partie -> nb_arrivees)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void afficher_partie(partie_t * partie)
{
    system("cls");
    printf("\n");
    printf("Nom du joueur: %s\n\n", partie ->joueur->nom);
    afficher_plateau(partie ->plateau);
    printf("Nombre de coups: %d", partie->nb_coups);
    printf("\n");

}

void nouvelle_partie(const char * nom_fichier, const char * nom_joueur)
{
    partie_t * res = creer_partie(nom_fichier, nom_joueur);
    while(!partie_terminee(res))
    {
        afficher_partie(res);
        jouer_coup(res);
    }
    printf("\n\n\n");
    printf("Bravo! En %d coups!", res ->nb_coups);
}
