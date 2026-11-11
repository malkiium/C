#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "defines.h"

typedef struct {
  int pos_x;
  int pos_y;
  int bonus;
  int nb_case;
  char nom[28];
} Robot;
struct termios ancien;

void activeClavierDirect() {
  tcgetattr(STDIN_FILENO, &ancien);

  struct termios nouveau = ancien;
  nouveau.c_lflag &= ~(ICANON | ECHO);

  tcsetattr(STDIN_FILENO, TCSANOW, &nouveau);
}

void restaureClavier() { tcsetattr(STDIN_FILENO, TCSANOW, &ancien); }

/* implementations */
void clearScreen() { printf("\e[1;1H\e[2J"); }

void afficheCouleur(ColorCode fg, ColorCode bg, char c) {
  printf("\033[%d;%dm%c\033[m", FG_SHIFT + fg, BG_SHIFT + bg, c);
}

void creeNiveau(Niveau *niv, int l, int h) {
  assert((niv != NULL) && "error creeNiveau: void data");
  assert((l > 0 && h > 0) && "error creeNiveau: wrong dimension");

  /* copie les dimensions */
  niv->largeur = l;
  niv->hauteur = h;

  /* allocation memoire */
  niv->carte = malloc(sizeof(niv->carte[0]) * h);
  if (niv->carte == NULL) {
    free(niv->carte);
    ERROR("malloc carte");
  }
  for (int i = 0; i < h; i++) {
    niv->carte[i] = malloc(sizeof(niv->carte[i][0]) * l);
    if (niv->carte[i] == NULL) {
      for (int j = i; j >= 0; j--) {
        free(niv->carte[j]);
      }
      free(niv->carte);
      ERROR("malloc carte[i]");
    }
  }

  /* initialisation carte */
  initNiveau(niv);
}

void detruitNiveau(Niveau *niv) {
  assert((niv != NULL) && "error detruitNiveau: void data");
  assert((niv->largeur > 0 && niv->hauteur > 0) &&
         "error detruitNiveau: wrong dimension");

  /* desallocation */
  for (int i = 0; i < niv->hauteur; i++) {
    free(niv->carte[i]);
  }
  free(niv->carte);

  /* initialisation etat */
  niv->carte = NULL;
  niv->largeur = 0;
  niv->hauteur = 0;
  niv->position = -1;
  niv->nb_coups = 0;
  niv->nb_bonus = 0;
}

void initNiveau(Niveau *niv) {
  /* vide carte */
  for (int i = 0; i < niv->hauteur; i++) {
    for (int j = 0; j < niv->largeur; j++) {
      niv->carte[i][j] = VIDE;
    }
  }

  /* initialisation etat */
  niv->position = 0;
  niv->nb_coups = 0;
  niv->nb_bonus = 0;
}

void afficheNiveau(Niveau *niv) {
  assert((niv != NULL) && "error afficheNiveau: void data");
  /* nettoie le terminal */
  clearScreen();

  /* affiche carte */
  for (int i = 0; i < niv->hauteur; i++) {
    for (int j = 0; j < niv->largeur; j++) {
      if (niv->position == niv->largeur * i + j) {
        printf("@");
      } else {
        switch (niv->carte[i][j]) {
        case MUR:
          printf("#");
          break;
        case FIN:
          printf("F");
          break;
        case BONUS:
          printf("B");
          break;
        case VIDE:
          printf(" ");
          break;
        case DEBUT:
          printf("D");
          break;
        }
      }
    }
    printf("\n");
  }

  /* affiche etat */
  printf("Pos : %d\n", niv->position);
  printf("Bonus : %d\n", niv->nb_bonus);
  printf("Coups : %d\n", niv->nb_coups);
}

void litNiveau(const char filename[], Niveau *niv) {
  int largeur, hauteur;

  assert((niv != NULL) && "error litNiveau: void data");

  /* ouvre le fichier */
  FILE *fil = fopen(filename, "rt");

  /* lit les dimensions */
  assert(fscanf(fil, "%5i%5i", &largeur, &hauteur) == 2);

  /* cree le niveau */
  creeNiveau(niv, largeur, hauteur);

  /* lit le niveau */
  assert((niv->position != -1) && "error litNiveau: no initial position");

  int c;
  for (int i = 0; i < niv->hauteur; i++) {
    for (int j = 0; j < niv->largeur; j++) {
      do {
        c = fgetc(fil);
      } while (c == '\n' || c == '\r');
      switch (c) {
      case 'X':
        niv->carte[i][j] = MUR;
        break;
      case 'd':
        niv->carte[i][j] = DEBUT;
        niv->position = i * niv->largeur + j;
        break;
      case 'f':
        niv->carte[i][j] = FIN;
        break;
      case '$':
        niv->carte[i][j] = BONUS;
        niv->nb_bonus += 1;
        break;
      case ' ':
        niv->carte[i][j] = VIDE;
        break;
      }
    }
  }

  /* ferme le fichier */
  fclose(fil);
}

void copieNiveau(Niveau *niv1, Niveau *niv2) {
  assert((niv1 != NULL && niv2 != NULL) && "error copieNiveau: void data");

  /* redimensionnement eventuel */
  if (niv2->largeur != niv1->largeur || niv2->hauteur != niv1->hauteur) {
    detruitNiveau(niv2);
    creeNiveau(niv2, niv1->largeur, niv1->hauteur);
  }

  /* copie le niveau */
  for (int i = 0; i < niv1->hauteur; i++) {
    for (int j = 0; j < niv1->largeur; j++) {
      niv2->carte[i][j] = niv1->carte[i][j];
    }
  }

  /* copie l'etat */
  niv2->nb_bonus = niv1->nb_bonus;
  niv2->nb_coups = niv1->nb_coups;
  niv2->position = niv1->position;
}

int compareNiveau(Niveau *niv1, Niveau *niv2) {

  assert((niv1 != NULL && niv2 != NULL) && "error compareNiveau: void data");

  /* compare les dimensions */
  if (niv1->largeur != niv2->largeur) {
    printf("largeur pas identique\n");
    return 0;
  }
  if (niv1->hauteur != niv2->hauteur) {
    printf("hauteur pas identique\n");
    return 0;
  }

  /* compare les cases */
  for (int i = 0; i < niv1->hauteur; i++) {
    for (int j = 0; j < niv1->largeur; j++) {
      if (niv2->carte[i][j] != niv1->carte[i][j]) {
        printf("erreur a : %i %i \n", i, j);
        return 0;
      }
    }
  }

  /* compare l'etat du jeu */
  if (niv1->nb_bonus != niv2->nb_bonus) {
    printf("nb_bonus pas identique\n");
    return 0;
  }
  if (niv1->nb_coups != niv2->nb_coups) {
    printf("nb_coups pas identique\n");
    return 0;
  }
  if (niv1->position != niv2->position) {
    printf("position pas identique\n");
    return 0;
  }

  return 1;
}

int move(Niveau *niv, Direction d) {
  int delta_h = 0, delta_l = 0, pos_h, pos_l, next_l, next_h;
  Case next_c;

  assert((niv != NULL) && "error move: void data");
  assert(((d >= NORD) && (d <= OUEST)) && "error move: wrong direction");
  printf("move: direction = %s\n", dirName[d]);

  /* test si la position courante est hors grille */
  if (niv->position < 0 || niv->position >= (niv->largeur * niv->hauteur)) {
    return -1;
  }

  /* calcule la direction de deplacement */
  if (d == NORD) {
    delta_h = -1;
    delta_l = 0;
  } else if (d == SUD) {
    delta_h = 1;
    delta_l = 0;
  } else if (d == OUEST) {
    delta_h = 0;
    delta_l = -1;
  } else if (d == EST) {
    delta_h = 0;
    delta_l = 1;
  }
  /* position initiale */
  pos_h = niv->position / niv->largeur;
  pos_l = niv->position % niv->largeur;

  /* boucle de deplacement */
  next_h = pos_h + delta_h;
  next_l = pos_l + delta_l;

  if (next_l >= 0 && next_l < niv->largeur) {
    if (next_h >= 0 && next_h < niv->hauteur) {
      next_c = niv->carte[next_h][next_l];
    } else {
      return -1;
    }
  } else {
    return -1;
  }

  if (next_c == MUR) {
    return -1;
  } else if (next_c == FIN) {
    niv->nb_coups += 1;
    niv->position = niv->largeur * next_h + next_l;
    return 0;
  } else if (next_c == VIDE || next_c == DEBUT) {
    niv->position = niv->largeur * next_h + next_l;
    niv->nb_coups += 1;
    return 1;
  } else if (next_c == BONUS) {
    niv->carte[next_h][next_l] = VIDE;
    niv->nb_bonus -= 1;
    niv->position = niv->largeur * next_h + next_l;
    niv->nb_coups += 1;
    return 1;
  }

  return -1;
}

void play(Niveau *niv) {
  int res = 0;

  activeClavierDirect();

  do {
    /* affichage du niveau */
    printf("ATTEIGNEZ LA SORTIE");
    afficheNiveau(niv);

    /* lecture de la commande */
    Direction d;
    char touche;
    printf("Entrez une dirction (zqsd) :");
    touche = getchar();

    /* gestion de la commande */
    switch (touche) {
    case 'z':
      d = NORD;
      break;
    case 's':
      d = SUD;
      break;
    case 'q':
      d = OUEST;
      break;
    case 'd':
      d = EST;
      break;
    }
    res = move(niv, d);
  } while (res);

  afficheNiveau(niv);

  /* affichage final */
  printf("%s\n", ((niv->position != -1) ? "SORTIE ATTEINTE!"
                                        : "PERDU DANS L'ESPACE..."));
  restaureClavier();
}

int main(int argc, char **argv) {
  Niveau niv;

  assert((argc > 1) && "error main: manque le fichier");
  litNiveau(argv[1], &niv);
  afficheNiveau(&niv);

  play(&niv);

  detruitNiveau(&niv);

  return EXIT_SUCCESS;
}
