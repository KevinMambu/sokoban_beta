#ifndef _PLATEAU_
#define _PLATEAU_

typedef struct plateau_s
{
char * * statique;
char * * mobile;
int h;
int l;
}plateau_t;

typedef struct player_s
{
int x;
int y;
}player_t;

typedef struct caisse_s
{
int x;
int y;
}caisse_t;

plateau_t * creer_plateau( int h, int l);
void afficher_plateau(plateau_t * p);
void deplacer_joueur(player_t * j, plateau_t * p);
player_t * creer_joueur(int x, int y, plateau_t * p);
char contenu_case(plateau_t * p, int x, int y);
void modifier_contenu_case(plateau_t * p, int x, int y, char v);
int coup_autorise(plateau_t * p, player_t * j, char c);


#endif
