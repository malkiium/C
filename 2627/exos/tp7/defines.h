#ifndef __DEFINES_H__
#define __DEFINES_H__


/* "constantes" */
#define TAILLE_MAX 20


/* type de donnees */
typedef enum {NORD = 0, EST, SUD, OUEST} Direction;
typedef enum {MUR = 0, DEBUT, FIN, BONUS, VIDE} Case;
typedef struct
{
  int hauteur;
  int largeur;
  Case ** carte;

  int position;
  int nb_coups;
  int nb_bonus;
} Niveau;


/* astuce pour afficher un enum en char* */
#define STRINGIFY(x) [x] = #x
const char * dirName[] = { STRINGIFY(NORD), STRINGIFY(EST), STRINGIFY(SUD), STRINGIFY(OUEST)};


/* utilisation de la couleur */
#define FG_SHIFT 30
#define BG_SHIFT 40
typedef enum {BLACK = 0, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE} ColorCode;


/* messages */
#define ERROR(msg) {printf("error in function %s, file %s, line %d: %s\n", __func__, __FILE__, __LINE__, (msg)); exit(1);}
#define ENTER() printf("entering function %s\n", __func__);
#define LEAVE() printf("leaving function %s\n", __func__);


/* prototypes */
void clearScreen ();
void afficheCouleur (ColorCode, ColorCode, char);

void creeNiveau (Niveau *, int, int);
void detruitNiveau (Niveau *);
void initNiveau (Niveau *);
void afficheNiveau (Niveau *);
void litNiveau (const char [], Niveau *);
void copieNiveau (Niveau *, Niveau *);
int  compareNiveau (Niveau *, Niveau *);

int  move (Niveau *, Direction);
void play (Niveau *);


#endif
