#include <stdlib.h>
#include <stdio.h>
#include "plateau.h"

plateau_t * creer_plateau(int h, int l)
{
    int i;
    int j;
    plateau_t * res = (plateau_t *)malloc(sizeof(plateau_t));

    res -> statique = (char * *)malloc(sizeof(char *)*l);
    for(i = 0; i < l; i += 1)
    {
        res -> statique[i] = (char *)malloc(sizeof(char)*h);
    }
    for(i = 0; i < l; i += 1)
    {
        for(j = 0; j < h; j += 1)
        {
            res -> statique[i][j] = '.';
        }
    }


    res -> mobile = (char * *)malloc(sizeof(char *)*l);
    for(i = 0; i < l; i += 1)
    {
        res -> mobile[i] = (char *)malloc(sizeof(char)*h);
    }
    for(i = 0; i < l; i += 1)
    {
        for(j = 0; j < h; j += 1)
        {
            res -> mobile[i][j] = ' ';
        }
    }

    res -> h = h;
    res -> l = l;
    return res;
}

void detruire_plateau(plateau_t * p)
{
    int i;
    for(i = 0; i < p -> l; i += 1)
    {
        free(p -> statique[i]);
    }
    for(i = 0; i < p -> l; i += 1)
    {
        free(p -> mobile[i]);
    }
    free(p -> statique);
    free(p -> mobile);
    free(p);
}

void afficher_plateau(plateau_t * p)
{
    int i;
    int j;
    for(i = 0; i < p -> h; i += 1)
    {
        for(j = 0; j < p -> l; j += 1)
        {
            if((p -> mobile[i][j] == 'C')||(p -> mobile[i][j] == 'P'))
            {
                printf("%c  ", p -> mobile[i][j]);
            }
            else
            {
                printf("%c  ", p -> statique[i][j]);
            }
        }
        printf("\n\n");
    }
}

char contenu_case(plateau_t * p, int x, int y)
{
    return p -> statique[x][y];
}

void modifier_contenu_case(plateau_t * p, int x, int y, char v)
{
    p -> mobile[x][y] = v;
}

int tester_plateau(plateau_t * p)
{
   int nb_caisses = 0;
   int nb_arrivees = 0;
   int nb_joueurs = 0;
   int i;
   int j;
   for(i = 0; i < p -> h; i += 1)
   {
       for(j = 0; j < p -> l; j += 1)
       {
           switch(p -> statique[i][j])
           {
                case 'A':
                    nb_arrivees += 1;
                    break;
           }
            switch(p -> mobile[i][j])
            {
               case 'P':
                    nb_joueurs += 1;
                    break;
                case 'C':
                    nb_caisses += 1;
                    break;
            }
   }
   if((nb_joueurs != 1) || (nb_arrivees != nb_caisses))
    {
        return 0;
    }
    else{return 1;}
    }
}

plateau_t * charger_plateau(const char * filename)
{
    int i;
    int j;
    int l_file;
    int h_file;
    plateau_t * res;
    FILE * fichier = fopen(filename, "r");
    fscanf(fichier, "%d %d", &h_file, &l_file);
    res = creer_plateau(h_file, l_file);
    fseek(fichier,2,SEEK_CUR);

    for(i = 0; i < res -> h; i += 1)
    {
        for(j = 0; j < res -> l; j += 1)
        {
            res->mobile[i][j]= ' ';
        }
    }


    for(i = 0; i < res -> h; i += 1)
    {
        for(j = 0; j < res -> l; j += 1)
        {
            res -> statique[i][j] = fgetc(fichier);

        }
        fseek(fichier,2,SEEK_CUR);
    }

    for(i = 0; i < res -> h; i += 1)
    {
        for(j = 0; j < res -> l; j += 1)
        {
            if((res -> statique[i][j] == 'P')||res ->statique[i][j]== 'C')
            {
                res -> mobile[i][j] = res -> statique[i][j];
                res -> statique[i][j] = '.';
            }

        }
    }

    if(tester_plateau(res))
    {
        res = NULL;
    }
    fclose(fichier);
    return res;
}
