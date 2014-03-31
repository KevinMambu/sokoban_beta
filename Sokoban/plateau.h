#ifndef _PLATEAU_

typedef struct plateau_s
{
    int h;
    int l;
    char ** statique;
    char ** mobile;
} plateau_t;

plateau_t * creer_plateau(int h, int l);
void detruire_plateau(plateau_t * p);
void afficher_plateau(plateau_t * p);
char contenu_case(plateau_t * p, int x, int y);
void modifier_contenu_case(plateau_t * p, int x, int y, char v);
plateau_t * charger_plateau(const char * filename);
int tester_plateau(plateau_t * p);

#endif // _PLATEAU_
