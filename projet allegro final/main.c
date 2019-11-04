#include "biblio.h"


int main()
{
    ///déclaration des variables
    ///Tous les différents fonds utilisés
    BITMAP *fond;
    BITMAP *grille;
    BITMAP *buffer;
    BITMAP *help;
    BITMAP *menu;
    BITMAP *gateau;
    BITMAP *info1;
    BITMAP *info2;
    BITMAP *win;
    BITMAP *perdu;
    BITMAP *niveau;
    BITMAP *magenta;
    BITMAP* rejouer;
    BITMAP *grille2;
    BITMAP* niv2info;
    BITMAP* grille3;
    BITMAP* infoniv3;

    ///icones de jeu
    BITMAP *flechebas;
    BITMAP *flechehaut;
    BITMAP *flechegauche;
    BITMAP *flechedroite;
    BITMAP *lancer;

    ///personnage
    BITMAP *dragonfly;
    BITMAP* prison;
    BITMAP* liberer;
    BITMAP* ennemi;
    BITMAP* ennemiprison;

    ///PERSO 1
    BITMAP *bas;
    BITMAP *haut;
    BITMAP *gauche;
    BITMAP *droite;
    BITMAP *bas_2;
    BITMAP *haut_2;
    BITMAP *gauche_2;
    BITMAP *droite_2;
    ///PERSO 2
    BITMAP *basmarron;
    BITMAP *basmarron_2;
    BITMAP *hautmarron;
    BITMAP *hautmarron_2;
    BITMAP *gauchemarron;
    BITMAP *gauchemarron_2;
    BITMAP *droitemarron;
    BITMAP *droitemarron_2;
    /// PERSO 3
    BITMAP *basrouge;
    BITMAP *basrouge_2;
    BITMAP* hautrouge;
    BITMAP *hautrouge_2;
    BITMAP *gaucherouge;
    BITMAP *gaucherouge_2;
    BITMAP *droiterouge;
    BITMAP *droiterouge_2;
    /// PERSO 4
    BITMAP *basgris;
    BITMAP *basgris_2;
    BITMAP* hautgris;
    BITMAP *hautgris_2;
    BITMAP *gauchegris;
    BITMAP *gauchegris_2;
    BITMAP *droitegris;
    BITMAP *droitegris_2;


    ///exec sert à lancer le sous programme lancer_instruction à 0 permet
    ///d'ajouter des instructions quand il passe à 1 il lance la chaine d'instruction
    int exec=0;

    ///init sert à afficher une seule fois uniquement sur le buffer les icones il passe alors à 1,
    ///car il est inutile de les réafficher. Si besoin est on aura qu'à passer init à 0 pour réafficher les icones (par ex: pour un éventuel réinitiliser niveau ?)
    int init=0;

    ///compteurs permettant de décaler en colonne l'affichage des icones de jeu flechebas, flechehaut, flechegauche, flechedroite
    ///dans le sous-programme sequence_instruction
    int i=0;
    int j=0;
    int i2=0;
    int j2=0;
    int i3=0;
    int j3=0;
    int i4=0;
    int j4=0;

    ///variable pour jouer à un niveau débloqué
    int progression=1;

    int tuto=0;
    int tuto2=0;
    int tuto3=0;
    int k;
    int k2;
    int k3;
    int k4;

    int perso;
    ///on initialise choix à 0 pour qu'il vérifie le test case 0:
    ///dans le switch ligne 85(suceptible de changer)
    int choix = 0;
    int lvl=0;
    ///on déclare un tableau statique qui va stocker un nombre prédéfini d'instructions
    ///(ici on a choisi de stocker les couleurs de chaque flèche) ex: flechebas est composé de r:255 ,v:0 ,b:0;
    int tab[N];
    int tabm[N];
    int tabg[N];
    int tabr[N];

    ///initialisation des données pour commencer un niveau
    initialisation_partie(&exec,&init,&i,&j,&i2,&j2,&i3,&j3,&i4,&j4,&k,&k2,&k3,&k4,&lvl,tab,tabm,tabr,tabg);

    ///on initialise allegro
    lancerToutAllegro(1000,800);

    ///on charge toutes les images que l'on utilise on pourrait faire un sous-prog plus tard pour qu'il y ait moins de lignes dans le main

    buffer=create_bitmap(1000,800);
    clear_bitmap(buffer);
    fond=load_bitmap("fond.bmp",NULL);
    grille=load_bitmap("Grille.bmp",NULL);
    flechebas=load_bitmap("flechebas.bmp",NULL);
    flechehaut=load_bitmap("flechehaut.bmp",NULL);
    flechegauche=load_bitmap("flechegauche.bmp",NULL);
    flechedroite=load_bitmap("flechedroite.bmp",NULL);
    dragonfly=load_bitmap("dragonfly.bmp",NULL);
    lancer=load_bitmap("jouer.bmp",NULL);
    help=load_bitmap("aides.bmp",NULL);
    menu=load_bitmap("menu.bmp",NULL);
    gateau = load_bitmap("gateau.bmp",NULL);
    win = load_bitmap("win.bmp",NULL);
    perdu = load_bitmap("perdu.bmp",NULL);
    info1 = load_bitmap("info.bmp",NULL);
    info2 = load_bitmap("info2.bmp",NULL);
    niveau=load_bitmap("niveau.bmp",NULL);
    magenta=load_bitmap("Magenta.bmp",NULL);
    rejouer = load_bitmap("rejouer.bmp",NULL);
    prison = load_bitmap("prison.bmp",NULL);
    liberer = load_bitmap("liberee.bmp",NULL);
    grille2 = load_bitmap("niveau2.bmp",NULL);
    niv2info = load_bitmap("niv2tuto.bmp",NULL);
    grille3 = load_bitmap("Grilleniv3.bmp",NULL);
    infoniv3 = load_bitmap("niv3tuto.bmp",NULL);


    ///PERSO PRINCIPAL
    bas=load_bitmap("bas.bmp",NULL);
    haut=load_bitmap("haut.bmp",NULL);
    gauche=load_bitmap("gauche.bmp",NULL);
    droite=load_bitmap("droite.bmp",NULL);
    bas_2=load_bitmap("bas_2.bmp",NULL);
    haut_2=load_bitmap("haut_2.bmp",NULL);
    gauche_2=load_bitmap("gauche_2.bmp",NULL);
    droite_2=load_bitmap("droite_2.bmp",NULL);

    ///BAS PERSO SECONDAIRE
    basgris= load_bitmap("bas_gris_1.bmp",NULL);
    basmarron = load_bitmap("bas_marron_1.bmp",NULL);
    basrouge = load_bitmap("bas_rouge_1.bmp",NULL);
    basgris_2= load_bitmap("bas_gris_2.bmp",NULL);
    basmarron_2=load_bitmap("bas_marron_2.bmp",NULL);
    basrouge_2=load_bitmap("bas_rouge_2.bmp",NULL);

    ///HAUT PERSO SECONDAIRE
    hautgris= load_bitmap("haut_gris_1.bmp",NULL);
    hautmarron = load_bitmap("haut_marron_1.bmp",NULL);
    hautrouge = load_bitmap("haut_rouge_1.bmp",NULL);
    hautgris_2= load_bitmap("haut_gris_2.bmp",NULL);
    hautmarron_2=load_bitmap("haut_marron_2.bmp",NULL);
    hautrouge_2=load_bitmap("haut_rouge_2.bmp",NULL);

    ///GAUCHE PERSO SECONDAIRE

    gauchegris= load_bitmap("gauche_gris_1.bmp",NULL);
    gauchemarron = load_bitmap("gauche_marron_1.bmp",NULL);
    gaucherouge = load_bitmap("gauche_rouge_1.bmp",NULL);
    gauchegris_2= load_bitmap("gauche_gris_2.bmp",NULL);
    gauchemarron_2=load_bitmap("gauche_marron_2.bmp",NULL);
    gaucherouge_2=load_bitmap("gauche_rouge_2.bmp",NULL);
    ///DROITE PERSO SECONDAIRE

    droitegris= load_bitmap("droite_gris_1.bmp",NULL);
    droitemarron = load_bitmap("droite_marron_1.bmp",NULL);
    droiterouge = load_bitmap("droite_rouge_1.bmp",NULL);
    droitegris_2= load_bitmap("droite_gris_2.bmp",NULL);
    droitemarron_2=load_bitmap("droite_marron_2.bmp",NULL);
    droiterouge_2=load_bitmap("droite_rouge_2.bmp",NULL);

    ennemi = load_bitmap("ennemi.bmp",NULL);
    ennemiprison = load_bitmap("ennemi.bmp",NULL);

    ///on test l'allocation du buffer
    if(buffer==NULL)
    {
        ///alors l'allocation a échoué
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    ///on test le chargement des images
    if(fond==NULL||grille==NULL||flechebas==NULL||flechehaut==NULL||flechegauche==NULL||flechedroite==NULL||dragonfly==NULL||lancer==NULL||help==NULL||menu==NULL||bas==NULL||haut==NULL||gauche==NULL||droite==NULL||gateau==NULL||win==NULL||perdu==NULL||info1==NULL||info2==NULL||niveau==NULL)
    {
        ///alors l'allocation a échoué
        allegro_message("Erreur image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    ///Boucle de jeu evenementielle
    while(!key[KEY_ESC])
    {
        // textprintf_ex(screen,font,60,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        ///C'est la variable choix qui décide de quels actions on va effectuer exemple: si choix==1 on est dans la partie jouer
        switch(choix)
        {
        case 0:
            ///appel de la fonction choixmenu qui va afficher le menu si le choix est toujour égal à 0 et qui va continuer à s'afficher
            ///sauf si les condtions(par un test de coordonées de la souris avec click gauche) pour appuyer sur Jouer,l'aide et le quitter
            ///sont remplis ils retournent alors respectivement 1,2 ou 3
            choix=choixmenu(menu,buffer);
            break;

        ///Lancer le mode jouer
        case 1:
            ///on récupère quel niveau il veut jouer
            switch (lvl)
            {
            case 0:
                lvl=choixniveau(niveau,buffer,progression);
                break;
            case 1:
                if(init==0)
                {
                    ///init passe à 1 initialisation_buffer ne se fait qu'une fois car il ne faut pas réafficher le fond
                    ///ex: si on affiche le fond et que notre personnage bouge et qu'ensuite on réaffiche le fond on voit pas la différence
                    init=1;
                    initialisation_buffer(buffer,fond,grille,flechebas,flechehaut,flechegauche,flechedroite,lancer,droite,lvl,grille2,gateau,prison,liberer,grille3,droitemarron,gaucherouge,gauchegris,ennemi);
                }
                ///si c'est le niveau 1 on affiche les bulles du tutoriel
                ///a ajouter
                ///on doit afficher le perso cartoon avec les messages bulles, + on doit faire ex: click gauche pour passer à la bulle suivante
                ///on peut faire un sous prog

                ///on bloque toute action pour s'assurer que l'utilisateur regarde bien toutes les bulles d'aides
                ///faire un sous prog
                if(tuto==0)
                {
                    tuto=1;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                    tutoriel(magenta,dragonfly,info1,info2,niv2info,infoniv3,lvl);
                }
                ///de base exec est égal à 0 pour définir comme un état on l'on peut ajouter des instructions
                ///Si exec=0 et soit k!=12(le nombre d'instruction ajouté) alors on peux toujours rajouter une instruction
                if(exec==0&&k!=12)
                {
                    sequence_instruction(buffer,flechebas,flechehaut,flechegauche,flechedroite,&i,&j,&i2,&j2,&i3,&j3,&i4,&j4,tab,&k,&k2,&k3,&k4,tabm,tabg,tabr,lvl,&perso);
                }

                ///Si on appuit sur lancer alors on n'est plus capable d'ajouter de nouvelles instructions
                if(mouse_x>665&&mouse_x<945&&mouse_y>600&&mouse_y<700&&mouse_b&1)
                {
                    exec=1;
                    lancer_instruction(buffer,win,perdu,dragonfly,bas,haut,gauche,droite,tab,tabm,tabr,tabg,rejouer,grille,lvl,prison,liberer,magenta,bas_2,haut_2,gauche_2,droite_2,basmarron,basmarron_2,hautmarron,hautmarron_2,gauchemarron,gauchemarron_2,droitemarron,droitemarron_2,basrouge,basrouge_2,hautrouge,hautrouge_2,gaucherouge,gaucherouge_2,droiterouge,droiterouge_2,basgris,basgris_2,hautgris,hautgris_2,gauchegris,gauchegris_2,droitegris,droitegris_2,ennemiprison);
                }
                ///Proposition rejouer
                if(exec==1)
                {
                    rest(20);
                    replay_oui_non(dragonfly,rejouer,&lvl,&init,&exec,&k,&k2,&k3,&k4,&i,&j,&i2,&j2,&i3,&j3,&i4,&j4,tab,tabm,tabg,tabr);
                }
                break;
            case 2:
                if(init==0)
                {
                    ///init passe à 1 initialisation_buffer ne se fait qu'une fois car il ne faut pas réafficher le fond
                    ///ex: si on affiche le fond et que notre personnage bouge et qu'ensuite on réaffiche le fond on voit pas la différence
                    init=1;
                    initialisation_buffer(buffer,fond,grille,flechebas,flechehaut,flechegauche,flechedroite,lancer,droite,lvl,grille2,gateau,prison,liberer,grille3,droitemarron,gaucherouge,gauchegris,ennemi);
                }
                if(tuto2==0)
                {
                    tuto2=1;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                    tutoriel(magenta,dragonfly,info1,info2,niv2info,infoniv3,lvl);
                }
                ///de base exec est égal à 0 pour définir comme un état on l'on peut ajouter des instructions
                ///Si exec=0 et soit k!=12(le nombre d'instruction ajouté) alors on peux toujours rajouter une instruction
                if(exec==0&&k!=12)
                {
                    sequence_instruction(buffer,flechebas,flechehaut,flechegauche,flechedroite,&i,&j,&i2,&j2,&i3,&j3,&i4,&j4,tab,&k,&k2,&k3,&k4,tabm,tabg,tabr,lvl,&perso);
                }

                ///Si on appuit sur lancer alors on n'est plus capable d'ajouter de nouvelles instructions
                if(mouse_x>665&&mouse_x<945&&mouse_y>600&&mouse_y<700&&mouse_b&1)
                {
                    exec=1;
                    lancer_instruction(buffer,win,perdu,dragonfly,bas,haut,gauche,droite,tab,tabm,tabr,tabg,rejouer,grille,lvl,prison,liberer,magenta,bas_2,haut_2,gauche_2,droite_2,basmarron,basmarron_2,hautmarron,hautmarron_2,gauchemarron,gauchemarron_2,droitemarron,droitemarron_2,basrouge,basrouge_2,hautrouge,hautrouge_2,gaucherouge,gaucherouge_2,droiterouge,droiterouge_2,basgris,basgris_2,hautgris,hautgris_2,gauchegris,gauchegris_2,droitegris,droitegris_2,ennemiprison);
                }
                ///Proposition rejouer
                if(exec==1)
                {
                    rest(20);
                    replay_oui_non(dragonfly,rejouer,&lvl,&init,&exec,&k,&k2,&k3,&k4,&i,&j,&i2,&j2,&i3,&j3,&i4,&j4,tab,tabm,tabg,tabr);
                }


                /*
                allegro_message("Niveau non disponible");
                lvl=0;*/
                break;
            case 3:
                /*allegro_message("Niveau non disponible");
                lvl=0;*/
                if(init==0)
                {
                    ///init passe à 1 initialisation_buffer ne se fait qu'une fois car il ne faut pas réafficher le fond
                    ///ex: si on affiche le fond et que notre personnage bouge et qu'ensuite on réaffiche le fond on voit pas la différence
                    init=1;
                    initialisation_buffer(buffer,fond,grille,flechebas,flechehaut,flechegauche,flechedroite,lancer,droite,lvl,grille2,gateau,prison,liberer,grille3,droitemarron,gaucherouge,gauchegris,ennemi);
                }
                if(tuto3==0)
                {
                    tuto3=1;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                    tutoriel(magenta,dragonfly,info1,info2,niv2info,infoniv3,lvl);
                }
                ///de base exec est égal à 0 pour définir comme un état on l'on peut ajouter des instructions
                ///Si exec=0 et soit k!=12(le nombre d'instruction ajouté) alors on peux toujours rajouter une instruction

                if(exec==0&&k!=12&&k2!=12&&k3!=12&&k4!=12)
                {
                    sequence_instruction(buffer,flechebas,flechehaut,flechegauche,flechedroite,&i,&j,&i2,&j2,&i3,&j3,&i4,&j4,tab,&k,&k2,&k3,&k4,tabm,tabg,tabr,lvl,&perso);
                }

                ///Si on appuit sur lancer alors on n'est plus capable d'ajouter de nouvelles instructions
                if(mouse_x>665&&mouse_x<945&&mouse_y>600&&mouse_y<700&&mouse_b&1)
                {
                    exec=1;
                    lancer_instruction(buffer,win,perdu,dragonfly,bas,haut,gauche,droite,tab,tabm,tabr,tabg,rejouer,grille,lvl,prison,liberer,magenta,bas_2,haut_2,gauche_2,droite_2,basmarron,basmarron_2,hautmarron,hautmarron_2,gauchemarron,gauchemarron_2,droitemarron,droitemarron_2,basrouge,basrouge_2,hautrouge,hautrouge_2,gaucherouge,gaucherouge_2,droiterouge,droiterouge_2,basgris,basgris_2,hautgris,hautgris_2,gauchegris,gauchegris_2,droitegris,droitegris_2,ennemiprison);
                }
                ///Proposition rejouer
                if(exec==1)
                {
                    rest(20);
                    replay_oui_non(dragonfly,rejouer,&lvl,&init,&exec,&k,&k2,&k3,&k4,&i,&j,&i2,&j2,&i3,&j3,&i4,&j4,tab,tabm,tabg,tabr);
                }
                break;
            }
            break;
        ///Ecran d'aide
        case 2:
            ///affichage de l'aide
            blit(help,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            ///Si l'utilisateur décide de retourner au menu en appuyant sur enter il peut de nouveau modifer quel choix il va sélectionner.
            ///Comme s'il venait de lancer l'appli c a d choix reste à 0 tant que l'utilisateur n'a pas appuyer sur aide, jouer, quitter
            if (key[KEY_ENTER])
            {
                choix=choixmenu(menu,buffer);
            }
            break;

        ///quitter le jeu
        case 3:
            allegro_message("A BIENTOT !");
            allegro_exit();
            exit(EXIT_FAILURE);
            break;
        }
        ///on affiche le buffer après avoir effectuer toutes les différentes actions effectuées dessus (dans les sous prog)
        ///que ce soit pour afficher l'aide
        ///le jeu
        ///la modification de la position de la libellule
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    return 0;
}
END_OF_MAIN();
