#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "defines.h"


/* implementations */
void clearScreen ()
{
  printf("\e[1;1H\e[2J");
}

 
void afficheCouleur (ColorCode fg, ColorCode bg, char c)
{
  printf("\033[%d;%dm%c\033[m", FG_SHIFT + fg, BG_SHIFT + bg, c);
}


void creeNiveau (Niveau * niv, int l, int h)
{
  assert((niv != NULL) && "error creeNiveau: void data");
  assert((l > 0 && h > 0) && "error creeNiveau: wrong dimension");

  /* copie les dimensions */

  /* allocation memoire */

  /* initialisation carte */
  initNiveau (niv);
}


void detruitNiveau (Niveau * niv)
{
  assert((niv != NULL) && "error detruitNiveau: void data");
  assert((niv->largeur > 0 && niv->hauteur > 0) && "error detruitNiveau: wrong dimension");

  /* desallocation */

  /* initialisation etat */
}


void initNiveau (Niveau * niv)
{
  /* vide carte */

  /* initialisation etat */
}


void afficheNiveau (Niveau * niv)
{
  assert((niv != NULL) && "error afficheNiveau: void data");

  /* nettoie le terminal */
  clearScreen();

  /* affiche carte */

  /* affiche etat */
}


void litNiveau (const char filename[], Niveau * niv)
{
  int largeur, hauteur;

  assert((niv != NULL) && "error litNiveau: void data");

  /* ouvre le fichier */

  /* lit les dimensions */

  /* cree le niveau */
  creeNiveau(niv, largeur, hauteur);

  /* lit le niveau */

  assert((niv->position != -1) && "error litNiveau: no initial position");

  /* ferme le fichier */
}


void copieNiveau (Niveau * niv1, Niveau * niv2)
{
  assert((niv1 != NULL && niv2 != NULL) && "error copieNiveau: void data");

  /* redimensionnement eventuel */

  /* copie le niveau */

  /* copie l'etat */
}


int  compareNiveau (Niveau * niv1, Niveau * niv2)
{
  int i, j;

  assert((niv1 != NULL && niv2 != NULL) && "error compareNiveau: void data");

  /* compare les dimensions */

  /* compare les cases */

  /* compare l'etat du jeu */

  return 1;
}


int move (Niveau * niv, Direction d)
{
  int delta_h, delta_l, pos_h , pos_l, next_l, next_h;
  Case next_c;

  assert((niv != NULL) && "error move: void data");
  assert(((d >= NORD) && (d <= OUEST)) && "error move: wrong direction");
  printf("move: direction = %s\n", dirName[d]);

  /* test si la position courante est hors grille */

  /* calcule la direction de deplacement */

  /* position initiale */

  /* boucle de deplacement */

  return 0;
}


void play (Niveau * niv)
{
  int res = 0;

  do
  {
    /* affichage du niveau */
    printf("ATTEIGNEZ LA SORTIE");
    afficheNiveau(niv);

    /* lecture de la commande */

    /* gestion de la commande */

  } while (res);

  /* affichage final */
  printf("%s\n", ((niv->position != -1)? "SORTIE ATTEINTE!": "PERDU DANS L'ESPACE..."));
  afficheNiveau(niv);
}


int main (int argc, char ** argv)
{
  Niveau niv;

  assert((argc > 1) && "error main: manque le fichier");
  litNiveau(argv[1], &niv);
  /* afficheNiveau(&niv); */

  play(&niv);

  detruitNiveau(&niv);

  return EXIT_SUCCESS;
}
