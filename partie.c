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
                res -> joueur -> x = j;
                res -> joueur -> y = i;
            }
        }
    }
    return res;
}

int coup_autorise(partie_t * partie, char c)
{
    switch(c) /*on fait une distinction de cas en fonction de la touche en entrée: un switch est préférable*/
	{
		case 'q':
			if((contenu_case(partie -> plateau,(partie -> joueur -> y),(partie -> joueur -> x - 1)) != 'M'))    /*si y a pas de mur à gauche*/
			{
			    if(partie->plateau->mobile[partie -> joueur -> y][partie -> joueur -> x - 1] == 'C')            /*si en plus il y a une caisse*/
                {
                    if(coup_autorise_caisse(partie, partie -> joueur -> y,partie -> joueur -> x - 1, c))        /*et si la caisse a les moyens de bouger à gauche*/
                    {
                        return 2;                                                                               /* en renvoie 2*/
                    }
                }
				return 1;                                                                                       /*sinon en renvoie 1*/
			}                                                                                                   /*a réiterer en fct des directions*/
			break;
		case 'Q':
			if((contenu_case(partie -> plateau,(partie -> joueur -> y),(partie -> joueur -> x - 1)) != 'M'))
			{
			    if(partie->plateau->mobile[partie -> joueur -> y][partie -> joueur -> x - 1] == 'C')
                {
                    if(coup_autorise_caisse(partie, partie -> joueur -> y,partie -> joueur -> x - 1, c))
                    {
                        return 2;
                    }
                }
				return 1;
			}
			break;
		case 'z':
			if((contenu_case(partie -> plateau,(partie -> joueur -> y - 1),(partie -> joueur -> x)) != 'M'))
			{
			    if(partie->plateau->mobile[partie -> joueur -> y - 1][partie -> joueur -> x] == 'C')
                {
                    if(coup_autorise_caisse(partie, partie ->joueur->y - 1, partie->joueur->x, c))
                    {
                        return 2;
                    }
                }
				return 1;
			}
			break;
		case 'Z':
			if((contenu_case(partie -> plateau,(partie -> joueur -> y - 1),(partie -> joueur -> x)) != 'M'))
			{
			    if(partie->plateau->mobile[partie -> joueur -> y - 1][partie -> joueur -> x] == 'C')
                {
                    if(coup_autorise_caisse(partie, partie ->joueur->y - 1, partie->joueur->x, c))
                    {
                        return 2;
                    }
                }
				return 1;
			}
			break;
		case 's':
			if((contenu_case(partie -> plateau,(partie -> joueur -> y + 1),(partie -> joueur -> x)) != 'M'))
			{
			    if(partie->plateau->mobile[partie -> joueur -> y + 1][partie -> joueur -> x] == 'C')
                {
                    if(coup_autorise_caisse(partie, partie ->joueur->y + 1, partie->joueur->x, c))
                    {
                        return 2;
                    }
                }
				return 1;
			}
			break;
		case 'S':
			if((contenu_case(partie -> plateau,(partie -> joueur -> y + 1),(partie -> joueur -> x)) != 'M'))
			{
			    if(partie->plateau->mobile[partie -> joueur -> y + 1][partie -> joueur -> x] == 'C')
                {
                    if(coup_autorise_caisse(partie, partie ->joueur->y + 1, partie->joueur->x, c))
                    {
                        return 2;
                    }
                }
				return 1;
			}
			break;
		case 'd':
			if((contenu_case(partie -> plateau,(partie -> joueur -> y),(partie -> joueur -> x + 1)) != 'M'))
			{
			    if(partie->plateau->mobile[partie -> joueur -> y][partie -> joueur -> x + 1] == 'C')
                {
                    if(coup_autorise_caisse(partie, partie -> joueur -> y,partie -> joueur -> x + 1, c))
                    {
                        return 2;
                    }
                }
				return 1;
			}
			break;
		case 'D':
			if((contenu_case(partie -> plateau,(partie -> joueur -> y),(partie -> joueur -> x + 1)) != 'M'))
			{
			    if(partie->plateau->mobile[partie -> joueur -> y][partie -> joueur -> x + 1] == 'C')
                {
                    if(coup_autorise_caisse(partie, partie -> joueur -> y,partie -> joueur -> x + 1, c))
                    {
                        return 2;
                    }
                }
				return 1;
			}
			break;
	}
	return 0; /*Si la touche entrée n'est pas conforme, ou qu'aucune des conditions precendentes etaient validables, on renvoie 0*/
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
    /*on récupere la touche à l'aide d'un scanf*/
    char key;
	scanf("%c", &key);


    /*ensuite, on fait certaines choses en fct de la touche entree
    La configuration est la suivante:

    Pour chaque touche autorisée:
    -> si le coup est UNIQUEMENT autorise dans cette direction
       -> on deplace le joueur
    -> sinon ,si le coup est autorisé ET qu'il ya une caisse sur le chemin
       -> si la caisse est deplacable
          -> on deplace le joueur et la caisse
    Si situation non conforme on déplace rien*/
	switch(key)
	{
		case 'z':
			if (coup_autorise(partie, key) == 1)
			{
                modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                partie ->joueur -> y -= 1;
                partie ->nb_coups += 1;
			}
			else if (coup_autorise(partie, key) == 2)
			{
			    if(coup_autorise_caisse(partie, partie ->joueur -> y - 1, partie ->joueur -> x, key))
                {
                    jouer_coup_caisse(partie, partie ->joueur -> y - 1, partie ->joueur -> x, key);
                    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                    partie ->joueur -> y -= 1;
                    partie ->nb_coups += 1;
                }
			}
			break;
		case 'Z':
			if (coup_autorise(partie, key) == 1)
			{
                modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                partie ->joueur -> y -= 1;
                partie ->nb_coups += 1;
			}
			else if (coup_autorise(partie, key) == 2)
			{
			    if(coup_autorise_caisse(partie, partie ->joueur -> y - 1, partie ->joueur -> x, key))
                {
                    jouer_coup_caisse(partie, partie ->joueur -> y - 1, partie ->joueur -> x, key);
                    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                    partie ->joueur -> y -= 1;
                    partie ->nb_coups += 1;
                }
			}
			break;
		case 'q':
			if (coup_autorise(partie, key) == 1)
			{
                modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                partie ->joueur -> x -= 1;
                partie ->nb_coups += 1;
			}
			else if (coup_autorise(partie, key) == 2)
			{
			    if(coup_autorise_caisse(partie, partie ->joueur -> y, partie ->joueur -> x - 1, key))
                {
                    jouer_coup_caisse(partie, partie ->joueur -> y, partie ->joueur -> x - 1, key);
                    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                    partie ->joueur -> x -= 1;
                    partie ->nb_coups += 1;
                }
			}
			break;
		case 'Q':
			if (coup_autorise(partie, key) == 1)
			{
			    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                partie ->joueur -> x -= 1;
                partie ->nb_coups += 1;
			}
			else if (coup_autorise(partie, key) == 2)
			{
			    if(coup_autorise_caisse(partie, partie ->joueur -> y, partie ->joueur -> x - 1, key))
                {
                    jouer_coup_caisse(partie, partie ->joueur -> y, partie ->joueur -> x - 1, key);
                    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                    partie ->joueur -> x -= 1;
                    partie ->nb_coups += 1;
                }
			}
			break;
		case 'd':
			if (coup_autorise(partie, key) == 1)
			{
			    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                partie ->joueur -> x += 1;
                partie ->nb_coups += 1;
			}
			else if (coup_autorise(partie, key) == 2)
			{
			    if(coup_autorise_caisse(partie, partie ->joueur -> y, partie ->joueur -> x + 1, key))
                {
                    jouer_coup_caisse(partie, partie ->joueur -> y, partie ->joueur -> x + 1, key);
                    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                    partie ->joueur -> x += 1;
                    partie ->nb_coups += 1;
                }
			}
			break;
		case 'D':
			if (coup_autorise(partie, key) == 1)
			{
			    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                partie ->joueur -> x += 1;
                partie ->nb_coups += 1;
			}
			else if (coup_autorise(partie, key) == 2)
			{
			    if(coup_autorise_caisse(partie, partie ->joueur -> y, partie ->joueur -> x + 1, key))
                {
                    jouer_coup_caisse(partie, partie ->joueur -> y, partie ->joueur -> x + 1, key);
                    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                    partie ->joueur -> x += 1;
                    partie ->nb_coups += 1;
                }
			}
			break;
		case 's':
			if (coup_autorise(partie, key) == 1)
			{
			    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                partie ->joueur -> y += 1;
                partie ->nb_coups += 1;
			}
			else if (coup_autorise(partie, key) == 2)
			{
			    if(coup_autorise_caisse(partie, partie ->joueur -> y + 1, partie ->joueur -> x, key))
                {
                    jouer_coup_caisse(partie, partie ->joueur -> y + 1, partie ->joueur -> x, key);
                    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                    partie ->joueur -> y += 1;
                    partie ->nb_coups += 1;
                }
			}
			break;
		case 'S':
			if (coup_autorise(partie, key) == 1)
			{
			    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                partie ->joueur -> y += 1;
                partie ->nb_coups += 1;
			}
			else if (coup_autorise(partie, key) == 2)
			{
			    if(coup_autorise_caisse(partie, partie ->joueur -> y + 1, partie ->joueur -> x, key))
                {
                    jouer_coup_caisse(partie, partie ->joueur -> y + 1, partie ->joueur -> x, key);
                    modifier_contenu_case(partie ->plateau, partie ->joueur -> y, partie ->joueur -> x, ' ');
                    partie ->joueur -> y += 1;
                    partie ->nb_coups += 1;
                }
			}
			break;
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
    system("clear");
    printf("\n");
    printf("Nom du joueur: %s (%dx%d)\n\n", partie ->joueur->nom, partie ->joueur->x, partie ->joueur->y);
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
    detruire_partie(res);
}


void infos(partie_t * partie)
{
    int i;
    int j;
    printf("Joueur: %s <%dx%d>", partie->joueur->nom, partie->joueur->x, partie->joueur->y);
    printf("\n\n\nPlateau statique\n\n");
    for(i = 0; i < partie ->plateau->h; i += 1)
    {
        for(j = 0; j < partie -> plateau -> l; j +=1)
        {
            printf("%c", partie->plateau->statique[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\nPlateau mobile\n\n");
    for(i = 0; i < partie ->plateau->h; i += 1)
    {
        for(j = 0; j < partie -> plateau -> l; j +=1)
        {
            printf("%c", partie->plateau->mobile[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\nDimensions <%dx%d>\n\n", partie ->plateau->h, partie->plateau->l);
    printf("\n\n\nCoordonées des points d'arrivees\n\n");
    for(i = 0; i < partie->nb_arrivees; i += 1)
    {
        printf("<%dx%d>", partie->liste_arrivees[i][0], partie->liste_arrivees[i][1]);
    }
    printf("\n\n\nValidité du plateau: %d\n\n", tester_plateau(partie->plateau));
}

int coup_autorise_caisse(partie_t * partie, int y_caisse, int x_caisse, char c)
{
    switch (c)
    {
    case 'q':
        if(contenu_case(partie->plateau, y_caisse - 1, x_caisse) != 'M')
        {
            return 1;
        }
        break;
    case 'Q':
        if(contenu_case(partie->plateau, y_caisse - 1, x_caisse) != 'M')
        {
            return 1;
        }
        break;
    case 'z':
        if(contenu_case(partie->plateau, y_caisse, x_caisse - 1) != 'M')
        {
            return 1;
        }
        break;
    case 'Z':
        if(contenu_case(partie->plateau, y_caisse, x_caisse - 1) != 'M')
        {
            return 1;
        }
        break;
    case 's':
        if(contenu_case(partie->plateau, y_caisse + 1, x_caisse) != 'M')
        {
            return 1;
        }
        break;
    case 'S':
        if(contenu_case(partie->plateau, y_caisse + 1, x_caisse) != 'M')
        {
            return 1;
        }
        break;
    case 'd':
        if(contenu_case(partie->plateau, y_caisse, x_caisse + 1) != 'M')
        {
            return 1;
        }
        break;
    case 'D':
        if(contenu_case(partie->plateau, y_caisse, x_caisse + 1) != 'M')
        {
            return 1;
        }
        break;
    }
    return 0;
}

int chercher_arrivees(partie_t * partie, int x, int y)
{
    int k;
    int cpt = 0;

    /*on fouille un à un le tableau, à chaque fois que le couple n'y est pas
      on incremente le compteur (peut etre optimisé)*/
    for(k = 0; k < partie -> nb_arrivees; k += 1)
    {
        if ((partie -> liste_arrivees[k][0] != x) && (partie -> liste_arrivees[k][1] != y))
        {
            cpt += 1;
        }
    }

    /*traduction: si on a rien trouvé de semblable au couple, c'est bon*/
    if(cpt == partie ->nb_arrivees)
    {
        return 0;
    }
    else{return 1;}
}

void jouer_coup_caisse(partie_t * partie, int y_caisse, int x_caisse, char c)
{
    modifier_contenu_case(partie->plateau, y_caisse, x_caisse, ' ');
    switch(c)
    {
    case 'z':
        modifier_contenu_case(partie->plateau, y_caisse - 1, x_caisse, 'C');
        break;
    case 'Z':
        modifier_contenu_case(partie->plateau, y_caisse - 1, x_caisse, 'C');
        break;
    case 'q':
        modifier_contenu_case(partie->plateau, y_caisse , x_caisse - 1, 'C');
        break;
    case 'Q':
        modifier_contenu_case(partie->plateau, y_caisse , x_caisse - 1, 'C');
        break;
    case 'd':
        modifier_contenu_case(partie->plateau, y_caisse , x_caisse + 1, 'C');
        break;
    case 'D':
        modifier_contenu_case(partie->plateau, y_caisse , x_caisse + 1, 'C');
        break;
    case 's':
        modifier_contenu_case(partie->plateau, y_caisse + 1, x_caisse, 'C');
        break;
    case 'S':
        modifier_contenu_case(partie->plateau, y_caisse + 1, x_caisse, 'C');
        break;
    }
}
