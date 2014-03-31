#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

int main()
{
    const char * fichier = "Sokoban Plateaux/test1.map";
    plateau_t * test = charger_plateau(fichier);
    afficher_plateau(test);
    return EXIT_SUCCESS;
}
