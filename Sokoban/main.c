#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "partie.h"

int main()
{
    const char * fichier = "Sokoban Plateaux/test2.map";
    partie_t * res = creer_partie(fichier, "Bob");
    infos(res);
    return EXIT_SUCCESS;
}
