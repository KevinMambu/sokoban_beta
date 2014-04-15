#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "partie.h"

int main()
{
    int debug = 0;
    const char * fichier = "Sokoban Plateaux/test2.map";
    if(!debug)
    {
        nouvelle_partie(fichier, "Bob");
    }
    else
    {
        partie_t * res = creer_partie(fichier, "Bob");
        infos(res);
    }
    return EXIT_SUCCESS;
}
