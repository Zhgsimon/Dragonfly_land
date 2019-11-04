#include "biblio.h"
#include <stdio.h>
#include <stdlib.h>

void lancerToutAllegro(int largeur, int hauteur)
{
    ///initialisation générale
    allegro_init();

    ///pour utiliser le clavier
    install_keyboard();

    ///pour utiliser la souris
    install_mouse();

    ///initialisation du MODE GRAPHIQUE
    //on fixe le mode couleur (8,16,24 ou 32 bits)
    set_color_depth(desktop_color_depth());
    //on essaie d'ouvrir une fenetre de largeur*hauteur pixels
    //si l'ouverture échoue on quitte
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,largeur,hauteur,0,0)!=0)
    {
        allegro_message("probleme mode graphique: %s",allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    ///si on veut afficher le pointeur de souris
    show_mouse(screen);
}


int choixmenu (BITMAP *menu,BITMAP *buffer)
{
    int choix=0;
    if(choix==0)
    {
        blit(menu,buffer,0,0,0,0,SCREEN_W,SCREEN_H); //Affichage du menu principal
        if (mouse_b&1 && (415<=mouse_x)&&(mouse_x<=590) && (260<= mouse_y) && (mouse_y <= 332) ) //Lancer le mode JOUER
            choix = 1;
        if (mouse_b&1 &&(436<= mouse_x) && (mouse_x<=560) && (369<= mouse_y) && (mouse_y<= 430))
            choix=2;
        if (mouse_b&1 && (385<= mouse_x) && (mouse_x<=610) && (480<= mouse_y) && (mouse_y<= 550) )   //QUITTER LE JEU
            choix =3;
    }

    rest(X);
    return choix;
}
int choixniveau (BITMAP *niveau,BITMAP *buffer,int progression)
{
    int lvl=0;
    ///affichage des niveaux disponibles
    blit(niveau,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    if(mouse_b&1 &&(335<=mouse_x)&&(mouse_x<=665)&&(234<=mouse_y)&&(mouse_y<=317))
    {
        lvl=1;
    }
    if(mouse_b&1 &&(325<=mouse_x)&&(mouse_x<=675)&&(372<=mouse_y)&&(mouse_y<=456))
    {
        /*if(progression<2)
            allegro_message("Il faut d'abord battre le niveau 1 !");*/
        // else
        lvl=2;
    }
    if(mouse_b&1 &&(328<=mouse_x)&&(mouse_x<=673)&&(512<=mouse_y)&&(mouse_y<=595))
        lvl=3;
    rest(X);
    return lvl;
}

void initialisation_buffer(BITMAP *buffer,BITMAP *fond,BITMAP *grille,BITMAP *flechebas,BITMAP *flechehaut,BITMAP* flechegauche,BITMAP *flechedroite, BITMAP *lancer, BITMAP *droite, int lvl,BITMAP *grille2,BITMAP *gateau,BITMAP *prison,BITMAP *liberer, BITMAP* grille3, BITMAP* droitemarron, BITMAP* gaucherouge, BITMAP* gauchegris,BITMAP* ennemi)
{
    blit(fond,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    masked_blit(flechebas,buffer,0,0,665,12,SCREEN_W,SCREEN_H);
    masked_blit(flechehaut,buffer,0,0,735,12,SCREEN_W,SCREEN_H);
    masked_blit(flechegauche,buffer,0,0,805,12,SCREEN_W,SCREEN_H);
    masked_blit(flechedroite,buffer,0,0,875,12,SCREEN_W,SCREEN_H);
    masked_blit(droite,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(lancer,buffer,0,0,665,600,SCREEN_W,SCREEN_H);
    if(lvl==1)
    {
        masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        ///On affiche le gateau
        masked_blit(gateau,buffer,0,0,503,431,SCREEN_W,SCREEN_H);
    }
    if(lvl==2)
    {
        masked_blit(grille2,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        ///Liberer caché derriere la prison pour ensuite clear la prison et faire se déplacer les libellules
        ///Libres
        masked_blit(liberer,buffer,0,0,0,430,SCREEN_W,SCREEN_H);
        masked_blit(liberer,buffer,0,0,Y,430,SCREEN_W,SCREEN_H);
        masked_blit(liberer,buffer,0,0,Y+X,430,SCREEN_W,SCREEN_H);
        ///Prisonniers
        masked_blit(prison,buffer,0,0,0,430,SCREEN_W,SCREEN_H);
        masked_blit(prison,buffer,0,0,Y,430,SCREEN_W,SCREEN_H);
        masked_blit(prison,buffer,0,0,Y+X,430,SCREEN_W,SCREEN_H);

    }
    if(lvl==3)
    {
        ///grille de jeu
        masked_blit(grille3,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        ///personnages
        masked_blit(droitemarron,buffer,0,0,3,431,SCREEN_W,SCREEN_H);
        masked_blit(gauchegris,buffer,0,0,503,431,SCREEN_W,SCREEN_H);
        masked_blit(gaucherouge,buffer,0,0,503,3,SCREEN_W,SCREEN_H);
        masked_blit(ennemi,buffer,0,0,203,217,SCREEN_W,SCREEN_H);
    }
}
void sequence_instruction(BITMAP *buffer,BITMAP *flechebas,BITMAP *flechehaut,BITMAP *flechegauche,BITMAP *flechedroite,int *i,int *j,int *i2,int *j2,int *i3,int *j3,int*i4,int *j4, int *tab,int *k,int *k2,int *k3,int *k4,int*tabm, int*tabg, int*tabr, int lvl,int *perso)
{
    int couleur=0;
    int l;
    int m=0;
    int n=0;
    if(lvl==1||lvl==2)
    {
        ///au bout de chaque 4e instruction *i prend la valeur 0
        if(*i==4)
        {
            *i=0;
            *j=*j+1;
        }
        if(mouse_b&1)
        {
            couleur=getpixel(buffer,mouse_x,mouse_y);
        }
        ///Il appuit sur flechebas
        if(couleur==makecol(255,0,0))
        {
            masked_blit(flechebas,buffer,0,0,665+*i*70,210+*j*105,SCREEN_W,SCREEN_H);
            ///on enregistre la couleur
            tab[*k]=couleur;
            printf("%d\n",tab[*k]);
            *k=*k+1;
            *i=*i+1;
        }
        ///il appuit sur flechehaut
        if(couleur==makecol(254,0,0))
        {
            masked_blit(flechehaut,buffer,0,0,665+*i*70,210+*j*105,SCREEN_W,SCREEN_H);
            ///on enregistre la couleur
            tab[*k]=couleur;
            printf("%d\n",tab[*k]);
            *k=*k+1;
            *i=*i+1;
        }
        ///il appuit sur flechegauche
        if(couleur==makecol(253,0,0))
        {
            masked_blit(flechegauche,buffer,0,0,665+*i*70,210+*j*105,SCREEN_W,SCREEN_H);
            ///on enregistre la couleur
            tab[*k]=couleur;
            printf("%d\n",tab[*k]);
            *k=*k+1;
            *i=*i+1;
        }
        ///il appuit sur flechedroite
        if(couleur==makecol(252,0,0))
        {
            masked_blit(flechedroite,buffer,0,0,665+*i*70,210+*j*105,SCREEN_W,SCREEN_H);
            ///on enregistre la couleur
            tab[*k]=couleur;
            printf("%d\n",tab[*k]);
            *k=*k+1;
            *i=*i+1;
        }
    }

    if(lvl==3)
    {
        ///au bout de chaque 4e instruction *i prend la valeur 0
        if(*i==4)
        {
            *i=0;
            *j=*j+1;
        }
        ///au bout de chaque 4e instruction *i2 prend la valeur 0
        if(*i2==4)
        {
            *i2=0;
            *j2=*j2+1;
        }
        ///au bout de chaque 4e instruction *i3 prend la valeur 0
        if(*i3==4)
        {
            *i3=0;
            *j3=*j3+1;
        }
        ///au bout de chaque 4e instruction *i4 prend la valeur 0
        if(*i4==4)
        {
            *i4=0;
            *j4=*j4+1;
        }
        if(mouse_b&1)
        {
            couleur=getpixel(buffer,mouse_x,mouse_y);
            printf("\n%d",couleur);
            if(couleur==makecol(185,122,87)||(couleur==makecol(237,28,36))||couleur==makecol(127,127,127)||couleur==makecol(239,228,176))
            {
                *perso=couleur;
                rectfill(buffer,668,211,942,530,makecol(64,77,254));

                if(couleur==makecol(185,122,87))
                {
                    ///affichage des instructions précédentes
                    for(l=0; l<*k2; l++)
                    {
                        if(tabm[l]==makecol(255,0,0))
                            masked_blit(flechebas,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tabm[l]==makecol(254,0,0))
                            masked_blit(flechehaut,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tabm[l]==makecol(253,0,0))
                            masked_blit(flechegauche,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tabm[l]==makecol(252,0,0))
                            masked_blit(flechedroite,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        m++;
                        if(m==4)
                        {
                            m=0;
                            n++;
                        }
                    }
                    m=0;
                    n=0;
                }
                if(couleur==makecol(237,28,36))
                {
                    ///affichage des instructions précédentes
                    for(l=0; l<*k3; l++)
                    {
                        if(tabr[l]==makecol(255,0,0))
                            masked_blit(flechebas,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tabr[l]==makecol(254,0,0))
                            masked_blit(flechehaut,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tabr[l]==makecol(253,0,0))
                            masked_blit(flechegauche,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tabr[l]==makecol(252,0,0))
                            masked_blit(flechedroite,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        m++;
                        if(m==4)
                        {
                            m=0;
                            n++;
                        }
                    }
                    m=0;
                    n=0;
                }
                if(couleur==makecol(127,127,127))
                {
                    ///affichage des instructions précédentes
                    for(l=0; l<*k4; l++)
                    {
                        if(tabg[l]==makecol(255,0,0))
                            masked_blit(flechebas,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tabg[l]==makecol(254,0,0))
                            masked_blit(flechehaut,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tabg[l]==makecol(253,0,0))
                            masked_blit(flechegauche,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tabg[l]==makecol(252,0,0))
                            masked_blit(flechedroite,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        m++;
                        if(m==4)
                        {
                            m=0;
                            n++;
                        }
                    }
                    m=0;
                    n=0;
                }
                if(couleur==makecol(239,228,176))
                {
                    ///affichage des instructions précédentes
                    for(l=0; l<*k; l++)
                    {
                        if(tab[l]==makecol(255,0,0))
                            masked_blit(flechebas,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tab[l]==makecol(254,0,0))
                            masked_blit(flechehaut,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tab[l]==makecol(253,0,0))
                            masked_blit(flechegauche,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        if(tab[l]==makecol(252,0,0))
                            masked_blit(flechedroite,buffer,0,0,665+m*70,210+n*105,SCREEN_W,SCREEN_H);
                        m++;
                        if(m==4)
                        {
                            m=0;
                            n++;
                        }
                    }
                    m=0;
                    n=0;
                }
            }
        }
        if (*perso==makecol(185,122,87))          ///joueur marron
        {
            ///Il appuit sur flechebas
            if(couleur==makecol(255,0,0)&&(*k2!=12))
            {
                masked_blit(flechebas,buffer,0,0,665+*i2*70,210+*j2*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabm[*k2]=couleur;
                printf("%d\n",tab[*k2]);
                *k2=*k2+1;
                *i2=*i2+1;
            }
            ///il appuit sur flechehaut
            if(couleur==makecol(254,0,0)&&(*k2!=12))
            {
                masked_blit(flechehaut,buffer,0,0,665+*i2*70,210+*j2*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabm[*k2]=couleur;
                printf("%d\n",tab[*k2]);
                *k2=*k2+1;
                *i2=*i2+1;
            }
            ///il appuit sur flechegauche
            if(couleur==makecol(253,0,0)&&(*k2!=12))
            {
                masked_blit(flechegauche,buffer,0,0,665+*i2*70,210+*j2*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabm[*k2]=couleur;
                printf("%d\n",tab[*k2]);
                *k2=*k2+1;
                *i2=*i2+1;
            }
            ///il appuit sur flechedroite
            if(couleur==makecol(252,0,0)&&(*k2!=12))
            {
                masked_blit(flechedroite,buffer,0,0,665+*i2*70,210+*j2*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabm[*k2]=couleur;
                printf("%d\n",tab[*k2]);
                *k2=*k2+1;
                *i2=*i2+1;
            }
        }
        if (*perso==makecol(237,28,36))       ///joueur rouge
        {
            ///Il appuit sur flechebas
            if(couleur==makecol(255,0,0)&&(*k3!=12))
            {
                masked_blit(flechebas,buffer,0,0,665+*i3*70,210+*j3*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabr[*k3]=couleur;
                printf("%d\n",tab[*k3]);
                *k3=*k3+1;
                *i3=*i3+1;
            }
            ///il appuit sur flechehaut
            if(couleur==makecol(254,0,0)&&(*k3!=12))
            {
                masked_blit(flechehaut,buffer,0,0,665+*i3*70,210+*j3*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabr[*k3]=couleur;
                printf("%d\n",tab[*k3]);
                *k3=*k3+1;
                *i3=*i3+1;
            }
            ///il appuit sur flechegauche
            if(couleur==makecol(253,0,0)&&(*k3!=12))
            {
                masked_blit(flechegauche,buffer,0,0,665+*i3*70,210+*j3*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabr[*k3]=couleur;
                printf("%d\n",tab[*k3]);
                *k3=*k3+1;
                *i3=*i3+1;
            }
            ///il appuit sur flechedroite
            if(couleur==makecol(252,0,0)&&(*k3!=12))
            {
                masked_blit(flechedroite,buffer,0,0,665+*i3*70,210+*j3*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabr[*k3]=couleur;
                printf("%d\n",tab[*k3]);
                *k3=*k3+1;
                *i3=*i3+1;
            }
        }
        if (*perso==makecol(127,127,127))          ///joueur gris
        {
            ///Il appuit sur flechebas
            if(couleur==makecol(255,0,0)&&(*k4!=12))
            {
                masked_blit(flechebas,buffer,0,0,665+*i4*70,210+*j4*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabg[*k4]=couleur;
                printf("%d\n",tab[*k4]);
                *k4=*k4+1;
                *i4=*i4+1;
            }
            ///il appuit sur flechehaut
            if(couleur==makecol(254,0,0)&&(*k4!=12))
            {
                masked_blit(flechehaut,buffer,0,0,665+*i4*70,210+*j4*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabg[*k4]=couleur;
                printf("%d\n",tab[*k4]);
                *k4=*k4+1;
                *i4=*i4+1;
            }
            ///il appuit sur flechegauche
            if(couleur==makecol(253,0,0)&&(*k4!=12))
            {
                masked_blit(flechegauche,buffer,0,0,665+*i4*70,210+*j4*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabg[*k4]=couleur;
                printf("%d\n",tab[*k4]);
                *k4=*k4+1;
                *i4=*i4+1;
            }
            ///il appuit sur flechedroite
            if(couleur==makecol(252,0,0)&&(*k4!=12))
            {
                masked_blit(flechedroite,buffer,0,0,665+*i4*70,210+*j4*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tabg[*k4]=couleur;
                printf("%d\n",tab[*k4]);
                *k4=*k4+1;
                *i4=*i4+1;
            }
        }
        if (*perso==makecol(239,228,176))          ///joueur jaune
        {
            ///Il appuit sur flechebas
            if(couleur==makecol(255,0,0)&&(*k!=12))
            {
                masked_blit(flechebas,buffer,0,0,665+*i*70,210+*j*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tab[*k]=couleur;
                printf("%d\n",tab[*k]);
                *k=*k+1;
                *i=*i+1;
            }
            ///il appuit sur flechehaut
            if(couleur==makecol(254,0,0)&&(*k!=12))
            {
                masked_blit(flechehaut,buffer,0,0,665+*i*70,210+*j*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tab[*k]=couleur;
                printf("%d\n",tab[*k]);
                *k=*k+1;
                *i=*i+1;
            }
            ///il appuit sur flechegauche
            if(couleur==makecol(253,0,0)&&(*k!=12))
            {
                masked_blit(flechegauche,buffer,0,0,665+*i*70,210+*j*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tab[*k]=couleur;
                printf("%d\n",tab[*k]);
                *k=*k+1;
                *i=*i+1;
            }
            ///il appuit sur flechedroite
            if(couleur==makecol(252,0,0)&&(*k!=12))
            {
                masked_blit(flechedroite,buffer,0,0,665+*i*70,210+*j*105,SCREEN_W,SCREEN_H);
                ///on enregistre la couleur
                tab[*k]=couleur;
                printf("%d\n",tab[*k]);
                *k=*k+1;
                *i=*i+1;
            }
        }
    }
    couleur=0;
    rest(110);
}


void lancer_instruction(BITMAP *buffer,BITMAP* win,BITMAP* perdu,BITMAP *dragonfly,BITMAP *bas,BITMAP *haut,BITMAP *gauche,BITMAP *droite,int *tab,int *tabm,int *tabr,int *tabg,BITMAP* rejouer,BITMAP *grille,int lvl,BITMAP*prison,BITMAP*liberer,BITMAP *magenta,BITMAP*bas_2,BITMAP *haut_2,BITMAP *gauche_2,BITMAP *droite_2,BITMAP *basmarron,BITMAP *basmarron_2,BITMAP *hautmarron,BITMAP *hautmarron_2,BITMAP *gauchemarron,BITMAP *gauchemarron_2,BITMAP *droitemarron,BITMAP *droitemarron_2,BITMAP *basrouge,BITMAP *basrouge_2,BITMAP *hautrouge,BITMAP *hautrouge_2,BITMAP *gaucherouge,BITMAP *gaucherouge_2,BITMAP *droiterouge,BITMAP *droiterouge_2,BITMAP *basgris,BITMAP *basgris_2,BITMAP *hautgris,BITMAP *hautgris_2,BITMAP *gauchegris,BITMAP *gauchegris_2,BITMAP *droitegris,BITMAP *droitegris_2,BITMAP* ennemiprison)
{
    ///compteur pour parcourir tab
    int i,j;

    ///variables pour le rectfill
    int x1=3;
    int y1=3;
    int x2 = 97;
    int y2 = 104;

    ///du marron
    int w4=3;
    int z4=431;
    int a4=97;
    int b4=532;

    ///du rouge
    int w5=503;
    int z5=3;
    int a5=597;
    int b5=104;

    ///du gris
    int w6=503;
    int z6=431;
    int a6=597;
    int b6=532;

    ///Variables pour le déplacement de la libellule
    ///jaune
    int x3=3;
    int y3=3;
    ///marron
    int x4=3;
    int y4=431;
    ///rouge
    int x5=503;
    int y5=3;
    ///gris
    int x6=503;
    int y6=431;

    int dx=3;
    int dy=3;

    ///peu importe le niveau on lance le deplacement de la libellule jaune
    ///on parcours le tableau d'instructions
    for(i=0; i<N; i++)
    {
        ///bas jaune
        if(tab[i]==makecol(255,0,0))
        {
            ///la libellule est blindée ne sort pas du cadre en bas
            if (y3<428)
            {
                /// ne va pas sur les libellules du niv2
                if(lvl==1||lvl==3||(lvl==2&&!(y3+Y==431 && x3==203)))
                {
                    ///ne va pas sur les cases noires(obstacles)
                    if(getpixel(buffer,(x3+5),(y3+Y))!=makecol(0,0,0))
                    {
                        ///actualisation du déplacement
                        for(j=0; j<36; j++)
                        {
                            ///on efface la posistion précédente
                            rectfill(buffer,x1,y1,x2,y2,makecol(64,77,254));
                            rectfill(buffer,x1,y1+Y,x2,y2+Y,makecol(64,77,254));
                            ///alternance entre les 2 bitmaps
                            if(y3%2==1)
                            {
                                masked_blit(bas,buffer,0,0,x3,y3,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(bas_2,buffer,0,0,x3,y3,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            ///calcul de la nouvelle position de la libellule
                            y3=y3+dy;
                            if((y3-4)%Y==0)
                            {
                                y3=y3-1;
                            }
                            rest(50);
                        }
                        ///calcul de la nouvelle position des cases suivante du bas pour effacer la position prec de la libellule
                        y1=y1+Y;
                        y2=y2+Y;
                    }
                }
            }
        }
        ///haut jaune
        if(tab[i]==makecol(254,0,0))
        {
            if (y3>3)
            {
                if(getpixel(buffer,(x3+5),(y3-Y))!=makecol(0,0,0))
                {
                    for(j=0; j<36; j++)
                    {
                        rectfill(buffer,x1,y1,x2,y2,makecol(64,77,254));
                        rectfill(buffer,x1,y1-Y,x2,y2-Y,makecol(64,77,254));
                        if(y3%2==1)
                        {
                            masked_blit(haut,buffer,0,0,x3,y3,SCREEN_W,SCREEN_H);
                            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                            masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                        }
                        else
                        {
                            masked_blit(haut_2,buffer,0,0,x3,y3,SCREEN_W,SCREEN_H);
                            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                            masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                        }
                        y3=y3-dy;
                        if((y3-2)%Y==0)
                        {
                            y3=y3+1;
                        }
                        rest(50);
                    }
                    y1=y1-Y;
                    y2=y2-Y;
                }
            }
        }
        ///gauche jaune
        if(tab[i]==makecol(253,0,0))
        {
            if (x3 > 3)
            {
                if(getpixel(buffer,(x3-100),(y3+5))!=makecol(0,0,0))
                {
                    for(j=0; j<33; j++)
                    {
                        rectfill(buffer,x1,y1,x2,y2,makecol(64,77,254));
                        rectfill(buffer,x1-X,y1,x2-X,y2,makecol(64,77,254));
                        if(x3%2==1)
                        {
                            masked_blit(gauche,buffer,0,0,x3,y3,SCREEN_W,SCREEN_H);
                            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                            masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                        }
                        else
                        {
                            masked_blit(gauche_2,buffer,0,0,x3,y3,SCREEN_W,SCREEN_H);
                            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                            masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                        }
                        x3=x3-dx;
                        if((x3-4)%100==0)
                        {
                            x3=x3-1;
                        }
                        rest(50);
                    }
                    x1=x1-X;
                    x2=x2-X;
                }
            }
        }
        ///droite jaune
        if(tab[i]==makecol(252,0,0))
        {
            if (x3 < 500)
            {
                if(getpixel(buffer,(x3+100),(y3+5))!=makecol(0,0,0))
                {
                    for(j=0; j<33; j++)
                    {
                        rectfill(buffer,x1,y1,x2,y2,makecol(64,77,254));
                        rectfill(buffer,x1+X,y1,x2+X,y2,makecol(64,77,254));
                        if(x3%2==1)
                        {
                            masked_blit(droite,buffer,0,0,x3,y3,SCREEN_W,SCREEN_H);
                            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                            masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                        }
                        else
                        {
                            masked_blit(droite_2,buffer,0,0,x3,y3,SCREEN_W,SCREEN_H);
                            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                            masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                        }
                        x3=x3+dx;
                        if((x3-2)%100==0)
                        {
                            x3=x3+1;
                        }
                        rest(50);
                    }
                    x1=x1+X;
                    x2=x2+X;
                }
            }
        }
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(125);
    }
    if(lvl==3)
    {
        ///déplacement de la libellule marron
        for(i=0; i<N; i++)
        {
            ///bas marron
            if(tabm[i]==makecol(255,0,0))
            {
                if (y4<428)
                {
                    if(getpixel(buffer,(x4+5),(y4+Y))!=makecol(0,0,0))
                    {
                        for(j=0; j<36; j++)
                        {
                            rectfill(buffer,w4,z4,a4,b4,makecol(64,77,254));
                            rectfill(buffer,w4,z4+Y,a4,b4+Y,makecol(64,77,254));
                            if(y4%2==1)
                            {
                                masked_blit(basmarron,buffer,0,0,x4,y4,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(basmarron_2,buffer,0,0,x4,y4,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            y4=y4+dy;
                            if((y4-4)%Y==0)
                            {
                                y4=y4-1;
                            }
                            rest(50);
                        }
                        z4=z4+Y;
                        b4=b4+Y;
                    }
                }
            }
            ///haut marron
            if(tabm[i]==makecol(254,0,0))
            {
                if (y4>3)
                {
                    if(getpixel(buffer,(x4+5),(y4-Y))!=makecol(0,0,0))
                    {
                        for(j=0; j<36; j++)
                        {
                            rectfill(buffer,w4,z4,a4,b4,makecol(64,77,254));
                            rectfill(buffer,w4,z4-Y,a4,b4-Y,makecol(64,77,254));
                            if(y4%2==1)
                            {
                                masked_blit(hautmarron,buffer,0,0,x4,y4,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(hautmarron_2,buffer,0,0,x4,y4,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            y4=y4-dy;
                            if((y4-2)%Y==0)
                            {
                                y4=y4+1;
                            }
                            rest(50);
                        }
                        z4=z4-Y;
                        b4=b4-Y;
                    }
                }
            }
            ///gauche marron
            if(tabm[i]==makecol(253,0,0))
            {
                if (x4 > 3)
                {
                    if(getpixel(buffer,(x4-100),(y4+5))!=makecol(0,0,0))
                    {
                        for(j=0; j<33; j++)
                        {
                            rectfill(buffer,w4,z4,a4,b4,makecol(64,77,254));
                            rectfill(buffer,w4-X,z4,a4-X,b4,makecol(64,77,254));
                            if(x4%2==1)
                            {
                                masked_blit(gauchemarron,buffer,0,0,x4,y4,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(gauchemarron_2,buffer,0,0,x4,y4,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            x4=x4-dx;
                            if((x4-4)%100==0)
                            {
                                x4=x4-1;
                            }
                            rest(50);
                        }
                        w4=w4-X;
                        a4=a4-X;
                    }
                }
            }
            ///droite marron
            if(tabm[i]==makecol(252,0,0))
            {
                if (x4 < 500)
                {
                    if(getpixel(buffer,(x4+100),(y4+5))!=makecol(0,0,0))
                    {
                        for(j=0; j<33; j++)
                        {
                            rectfill(buffer,w4,z4,a4,b4,makecol(64,77,254));
                            rectfill(buffer,w4+X,z4,a4+X,b4,makecol(64,77,254));
                            if(x4%2==1)
                            {
                                masked_blit(droitemarron,buffer,0,0,x4,y4,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(droitemarron_2,buffer,0,0,x4,y4,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            x4=x4+dx;
                            if((x4-2)%100==0)
                            {
                                x4=x4+1;
                            }
                            rest(50);
                        }
                        w4=w4+X;
                        a4=a4+X;
                    }
                }
            }
            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(125);
        }
        for(i=0; i<N; i++)
        {
            ///bas rouge
            if(tabr[i]==makecol(255,0,0))
            {
                if (y5<428)
                {
                    if(getpixel(buffer,(x5+5),(y5+Y))!=makecol(0,0,0))
                    {
                        for(j=0; j<36; j++)
                        {
                            rectfill(buffer,w5,z5,a5,b5,makecol(64,77,254));
                            rectfill(buffer,w5,z5+Y,a5,b5+Y,makecol(64,77,254));
                            if(y5%2==1)
                            {
                                masked_blit(basrouge,buffer,0,0,x5,y5,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(basrouge_2,buffer,0,0,x5,y5,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            y5=y5+dy;
                            if((y5-4)%Y==0)
                            {
                                y5=y5-1;
                            }
                            rest(50);
                        }
                        z5=z5+Y;
                        b5=b5+Y;
                    }
                }
            }
            ///haut rouge
            if(tabr[i]==makecol(254,0,0))
            {
                if (y5>3)
                {
                    if(getpixel(buffer,(x5+5),(y5-Y))!=makecol(0,0,0))
                    {
                        for(j=0; j<36; j++)
                        {
                            rectfill(buffer,w5,z5,a5,b5,makecol(64,77,254));
                            rectfill(buffer,w5,z5-Y,a5,b5-Y,makecol(64,77,254));
                            if(y5%2==1)
                            {
                                masked_blit(hautrouge,buffer,0,0,x5,y5,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(hautrouge_2,buffer,0,0,x5,y5,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            y5=y5-dy;
                            if((y5-2)%Y==0)
                            {
                                y5=y5+1;
                            }
                            rest(50);
                        }
                        z5=z5-Y;
                        b5=b5-Y;
                    }
                }
            }
            ///gauche rouge
            if(tabr[i]==makecol(253,0,0))
            {
                if (x5 > 3)
                {
                    if(getpixel(buffer,(x5-100),(y5+5))!=makecol(0,0,0))
                    {
                        for(j=0; j<33; j++)
                        {
                            rectfill(buffer,w5,z5,a5,b5,makecol(64,77,254));
                            rectfill(buffer,w5-X,z5,a5-X,b5,makecol(64,77,254));
                            if(x5%2==1)
                            {
                                masked_blit(gaucherouge,buffer,0,0,x5,y5,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(gaucherouge_2,buffer,0,0,x5,y5,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            x5=x5-dx;
                            if((x5-4)%100==0)
                            {
                                x5=x5-2;
                            }
                            rest(50);
                        }
                        printf("\n%d",x5);
                        w5=w5-X;
                        a5=a5-X;
                    }
                }
            }
            ///droite rouge
            if(tabr[i]==makecol(252,0,0))
            {
                if (x5 < 500)
                {
                    if(getpixel(buffer,(x5+100),(y5+5))!=makecol(0,0,0))
                    {
                        for(j=0; j<33; j++)
                        {
                            rectfill(buffer,w5,z5,a5,b5,makecol(64,77,254));
                            rectfill(buffer,w5+X,z5,a5+X,b5,makecol(64,77,254));
                            if(x4%2==1)
                            {
                                masked_blit(droiterouge,buffer,0,0,x5,y5,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(droiterouge_2,buffer,0,0,x5,y5,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            x5=x5+dx;
                            if((x5-2)%100==0)
                            {
                                x5=x5+1;
                            }
                            rest(50);
                        }
                        w5=w5+X;
                        a5=a5+X;
                    }
                }
            }
            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(125);
        }
        for(i=0; i<N; i++)
        {
            ///bas gris
            if(tabg[i]==makecol(255,0,0))
            {
                if (y6<428)
                {
                    if(getpixel(buffer,(x6+5),(y6+Y))!=makecol(0,0,0))
                    {
                        for(j=0; j<36; j++)
                        {
                            rectfill(buffer,w6,z6,a6,b6,makecol(64,77,254));
                            rectfill(buffer,w6,z6+Y,a6,b6+Y,makecol(64,77,254));
                            if(y6%2==1)
                            {
                                masked_blit(basgris,buffer,0,0,x6,y6,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(basgris_2,buffer,0,0,x6,y6,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            y6=y6+dy;
                            if((y6-4)%Y==0)
                            {
                                y6=y6-1;
                            }
                            rest(50);
                        }
                        z6=z6+Y;
                        b6=b6+Y;
                    }
                }
            }
            ///haut gris
            if(tabg[i]==makecol(254,0,0))
            {
                if (y6>3)
                {
                    if(getpixel(buffer,(x6+5),(y6-Y))!=makecol(0,0,0))
                    {
                        for(j=0; j<36; j++)
                        {
                            rectfill(buffer,w6,z6,a6,b6,makecol(64,77,254));
                            rectfill(buffer,w6,z6-Y,a6,b6-Y,makecol(64,77,254));
                            if(y6%2==1)
                            {
                                masked_blit(hautgris,buffer,0,0,x6,y6,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(hautgris_2,buffer,0,0,x6,y6,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            y6=y6-dy;
                            if((y6-2)%Y==0)
                            {
                                y6=y6+1;
                            }
                            rest(50);
                        }
                        z6=z6-Y;
                        b6=b6-Y;
                    }
                }
            }
            ///gauche gris
            if(tabg[i]==makecol(253,0,0))
            {

                if (x6 > 3)
                {
                    if(getpixel(buffer,(x6-100),(y6+5))!=makecol(0,0,0))
                    {
                        for(j=0; j<33; j++)
                        {
                            rectfill(buffer,w6,z6,a6,b6,makecol(64,77,254));
                            rectfill(buffer,w6-X,z6,a6-X,b6,makecol(64,77,254));
                            if(x6%2==1)
                            {
                                masked_blit(gauchegris,buffer,0,0,x6,y6,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(gauchegris_2,buffer,0,0,x6,y6,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            x6=x6-dx;
                            if((x6-4)%100==0)
                            {
                                x6=x6-1;
                            }
                            rest(50);
                        }
                        w6=w6-X;
                        a6=a6-X;
                    }
                }
            }
            ///droite gris
            if(tabg[i]==makecol(252,0,0))
            {
                if (x6 < 500)
                {
                    if(getpixel(buffer,(x6+100),(y6+5))!=makecol(0,0,0))
                    {
                        for(j=0; j<33; j++)
                        {
                            rectfill(buffer,w6,z6,a6,b6,makecol(64,77,254));
                            rectfill(buffer,w6+X,z6,a6+X,b6,makecol(64,77,254));
                            if(x6%2==1)
                            {
                                masked_blit(droitegris,buffer,0,0,x6,y6,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            else
                            {
                                masked_blit(droitegris_2,buffer,0,0,x6,y6,SCREEN_W,SCREEN_H);
                                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                                masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                            }
                            x6=x6+dx;
                            if((x6-2)%100==0)
                            {
                                x6=x6+1;
                            }
                            rest(50);
                        }
                        w6=w6+X;
                        a6=a6+X;
                    }
                }
            }
            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            masked_blit(grille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(125);
        }
    }
    resultat(dragonfly,win,perdu,rejouer,x3,y3,x4,y4,x5,y5,x6,y6,lvl,prison,liberer,buffer,magenta,ennemiprison);
}
void resultat(BITMAP* dragonfly, BITMAP* win, BITMAP* perdu,BITMAP* rejouer,int x3, int y3,int x4, int y4,int x5, int y5,int x6, int y6,int lvl,BITMAP*prison,BITMAP*liberer,BITMAP *buffer,BITMAP *magenta,BITMAP* ennemiprison)
{
    int bleu_fond;
    bleu_fond=makecol(64,77,254);
    if(lvl==1)
    {
        if ((x3==503)&&(y3==431))
        {
            ///carré rouge devient vert
            rectfill(buffer,503,431,597,532,makecol(0,200,0));
            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            printf("win");
            while(!mouse_b&1)
            {
                // printf("win");
                masked_blit(dragonfly,magenta,0,0,X,300,SCREEN_W,SCREEN_H);
                masked_blit(win,magenta,0,0,X,X,SCREEN_W,SCREEN_H);
                masked_blit(magenta,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            rectfill(magenta,0,0,1000,800,makecol(255,0,255));
        }
        else
        {
            while(!mouse_b&1)
            {
                // printf("perdu");
                masked_blit(dragonfly,magenta,0,0,X,300,SCREEN_W,SCREEN_H);
                masked_blit(perdu,magenta,0,0,X,X,SCREEN_W,SCREEN_H);
                masked_blit(magenta,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            rectfill(magenta,0,0,1000,800,makecol(255,0,255));
        }
    }
    if(lvl==2)
    {
        if ((x3>=400)&&(x3<=410)&&(y3>=429)&&(y3<=435))
        {
            ///carré rouge devient vert
            rectfill(buffer,400,431,498,532,makecol(0,200,0));
            rectfill(buffer,3,431,97,532,bleu_fond);
            rectfill(buffer,103,431,197,532,bleu_fond);
            rectfill(buffer,203,431,297,532,bleu_fond);

            masked_blit(liberer,buffer,0,0,0,430,SCREEN_W,SCREEN_H);
            masked_blit(liberer,buffer,0,0,Y,430,SCREEN_W,SCREEN_H);
            masked_blit(liberer,buffer,0,0,Y+X,430,SCREEN_W,SCREEN_H);

            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            while(!mouse_b&1)
            {
                ///Deplacement libellule libérée

                ///resultat
                masked_blit(dragonfly,magenta,0,0,X,300,SCREEN_W,SCREEN_H);
                masked_blit(win,magenta,0,0,X,X,SCREEN_W,SCREEN_H);
                masked_blit(magenta,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            rectfill(magenta,0,0,1000,800,makecol(255,0,255));
        }
    }
    if(lvl==3)
    {

        if ((x3>=103)&&(x3<=113)&&(y3>=217)&&(y3<=227))//&&(x4>=203)&&(x4<=213)&&(y4>=110)&&(y4<=120)&&(x5>=403)&&(x5<=413)&&(y5>=217)&&(y5<=227)&&(x6>=303)&&(x6<=313)&&(y6>=324)&&(y6<=334))
        {
            ///carré devient vert
            rectfill(buffer,103,217,197,318,makecol(0,200,0));
            rectfill(buffer,203,110,297,211,makecol(0,200,0));
            rectfill(buffer,403,217,497,318,makecol(0,200,0));
            rectfill(buffer,303,324,397,425,makecol(0,200,0));
            blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            while(!mouse_b&1)
            {
                ///resultat
                masked_blit(ennemiprison,magenta,0,0,203,217,SCREEN_W,SCREEN_H);
                masked_blit(dragonfly,magenta,0,0,X,300,SCREEN_W,SCREEN_H);
                masked_blit(win,magenta,0,0,X,X,SCREEN_W,SCREEN_H);
                masked_blit(magenta,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            rectfill(magenta,0,0,1000,800,makecol(255,0,255));
        }
    }
    else
    {
        while(!mouse_b&1)
        {
            // printf("perdu");
            masked_blit(dragonfly,magenta,0,0,X,300,SCREEN_W,SCREEN_H);
            masked_blit(perdu,magenta,0,0,X,X,SCREEN_W,SCREEN_H);
            masked_blit(magenta,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
        rectfill(magenta,0,0,1000,800,makecol(255,0,255));
    }
    rest(X);
}


void tutoriel(BITMAP *magenta,BITMAP *dragonfly, BITMAP *info1, BITMAP *info2, BITMAP *infoniv2, BITMAP* infoniv3, int lvl)
{
    masked_blit(dragonfly,magenta,0,0,315,400,SCREEN_W,SCREEN_H);
    int tutoriel_compteur=0;
    if (lvl==1)
    {
        while(tutoriel_compteur!=2)
        {
            if(tutoriel_compteur==0)
            {
                masked_blit(info1,magenta,0,0,400,200,SCREEN_W,SCREEN_H);
            }
            if(tutoriel_compteur==1)
            {
                masked_blit(info2,magenta,0,0,400,200,SCREEN_W,SCREEN_H);
            }
            if(mouse_b&1)
            {
                tutoriel_compteur++;
            }

            masked_blit(magenta,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(80);
        }
    }
    if (lvl == 2)
    {
        while(tutoriel_compteur!=1)
        {
            if(tutoriel_compteur==0)
            {
                masked_blit(infoniv2,magenta,0,0,400,200,SCREEN_W,SCREEN_H);

            }
            if(mouse_b&1)
            {
                tutoriel_compteur++;
            }
            masked_blit(magenta,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(80);
        }
    }
    if (lvl == 3)
    {
        while(tutoriel_compteur!=1)
        {
            if(tutoriel_compteur==0)
            {
                masked_blit(infoniv3,magenta,0,0,400,200,SCREEN_W,SCREEN_H);

            }
            if(mouse_b&1)
            {
                tutoriel_compteur++;
            }
            masked_blit(magenta,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(80);
        }
    }
    rectfill(magenta,0,0,1000,800,makecol(255,0,255));
}

void replay_oui_non(BITMAP *dragonfly,BITMAP *rejouer,int *lvl,int *init,int *exec,int *k,int *k2,int *k3,int *k4,int *i, int *j,int *i2,int *j2,int *i3,int *j3,int*i4,int *j4,int *tab,int *tabm, int *tabr,int *tabg)
{
    printf("rejouer");
    while(!mouse_b&1 || !((175<=mouse_x)&&(mouse_x<=230) && (203<= mouse_y) && (mouse_y <= 226)))
    {
        masked_blit(dragonfly,screen,0,0,X,300,SCREEN_W,SCREEN_H);
        masked_blit(rejouer,screen,0,0,X,X,SCREEN_W,SCREEN_H);
        rest(90);
        ///REJOUER OUI
        printf("Click rejouer");
        initialisation_partie(exec,init,i,j,i2,j2,i3,j3,i4,j4,k,k2,k3,k4,lvl,tab,tabm,tabr,tabg);
        if (mouse_b&1 && (315<=mouse_x)&&(mouse_x<=379) && (203<= mouse_y) && (mouse_y <= 226))
            ///REJOUER NON
        {
            allegro_message("A bientot");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
}
void initialisation_partie(int *exec,int *init, int *i,int *j,int *i2,int *j2,int *i3,int *j3,int*i4,int *j4,int *k,int *k2,int *k3,int *k4,int *lvl, int *tab,int *tabm, int *tabr,int *tabg)
{
    int l;
    ///a initialiser à chaque début de niveau + chaque fois que l'on veuilles repartir à zéros instructions
    for(l=0; l<N; l++)
    {
        tab[l]=0;
        tabm[l]=0;
        tabg[l]=0;
        tabr[l]=0;
    }
    *k=0;
    *k2=0;
    *k3=0;
    *k4=0;
    *lvl=0;
    *init=0;
    *exec=0;
    *i=0;
    *j=0;
    *i2=0;
    *j2=0;
    *i3=0;
    *j3=0;
    *i4=0;
    *j4=0;
}
