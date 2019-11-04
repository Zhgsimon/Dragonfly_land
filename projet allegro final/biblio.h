#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#define N 12
#define X 100
#define Y 107

void lancerToutAllegro(int largeur, int hauteur);
void initialisation_buffer(BITMAP *buffer,BITMAP *fond,BITMAP *grille,BITMAP *flechebas,BITMAP *flechehaut,BITMAP* flechegauche,BITMAP *flechedroite, BITMAP *lancer, BITMAP *droite, int lvl,BITMAP *grille2,BITMAP *gateau,BITMAP *prison,BITMAP *liberer, BITMAP* grille3, BITMAP* droitemarron, BITMAP* gaucherouge, BITMAP* gauchegris,BITMAP* ennemi);
void sequence_instruction(BITMAP *buffer,BITMAP *flechebas,BITMAP *flechehaut,BITMAP *flechegauche,BITMAP *flechedroite,int *i,int *j,int *i2,int *j2,int *i3,int *j3,int*i4,int *j4, int *tab,int *k,int *k2,int *k3,int *k4,int*tabm, int*tabg, int*tabr, int lvl,int *perso);
int choixmenu (BITMAP *menu,BITMAP *buffer);
int choixniveau (BITMAP *niveau,BITMAP *buffer,int progression);
void lancer_instruction(BITMAP *buffer,BITMAP* win,BITMAP* perdu,BITMAP *dragonfly,BITMAP *bas,BITMAP *haut,BITMAP *gauche,BITMAP *droite,int *tab,int *tabm,int *tabr,int *tabg,BITMAP* rejouer,BITMAP *grille,int lvl,BITMAP*prison,BITMAP*liberer,BITMAP *magenta,BITMAP*bas_2,BITMAP *haut_2,BITMAP *gauche_2,BITMAP *droite_2,BITMAP *basmarron,BITMAP *basmarron_2,BITMAP *hautmarron,BITMAP *hautmarron_2,BITMAP *gauchemarron,BITMAP *gauchemarron_2,BITMAP *droitemarron,BITMAP *droitemarron_2,BITMAP *basrouge,BITMAP *basrouge_2,BITMAP *hautrouge,BITMAP *hautrouge_2,BITMAP *gaucherouge,BITMAP *gaucherouge_2,BITMAP *droiterouge,BITMAP *droiterouge_2,BITMAP *basgris,BITMAP *basgris_2,BITMAP *hautgris,BITMAP *hautgris_2,BITMAP *gauchegris,BITMAP *gauchegris_2,BITMAP *droitegris,BITMAP *droitegris_2,BITMAP* ennemiprison);
void resultat(BITMAP* dragonfly, BITMAP* win, BITMAP* perdu,BITMAP* rejouer,int x3, int y3,int x4, int y4,int x5, int y5,int x6, int y6,int lvl,BITMAP*prison,BITMAP*liberer,BITMAP *buffer,BITMAP *magenta,BITMAP* ennemiprison);
void tutoriel(BITMAP *magenta,BITMAP *dragonfly,BITMAP *info1,BITMAP *info2,BITMAP *infoniv2,BITMAP* infoniv3, int lvl);
void replay_oui_non(BITMAP *dragonfly,BITMAP *rejouer,int *lvl,int *init,int *exec,int *k,int *k2,int *k3,int *k4,int *i, int *j,int *i2,int *j2,int *i3,int *j3,int*i4,int *j4,int *tab,int *tabm, int *tabr,int *tabg);
void initialisation_partie(int *exec,int *init, int *i,int *j,int *i2,int *j2,int *i3,int *j3,int*i4,int *j4,int *k,int *k2,int *k3,int *k4,int *lvl, int *tab,int *tabm, int *tabr,int *tabg);

#endif // BIBLIO_H_INCLUDED
