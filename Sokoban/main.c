#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "partie.h"

int main()
{
    const char * fichier = "Sokoban Plateaux/test1.map";
    partie_t * res = creer_partie(fichier, "Bob");
    while(1)
    {
        afficher_partie(res);
        jouer_coup(res);
    }
    return EXIT_SUCCESS;
}
