#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct {
  int *nmbs;
  int taille;
} NMBS;

void initStruct(NMBS *Nmbs,int taille) {
  Nmbs->taille=taille;
  Nmbs->nmbs= malloc(sizeof(int)*Nmbs->taille);
  for (int i=0; i<taille; i++) {
    Nmbs->nmbs[i] = 0;
  }
}

void initFichier(char *name) {
  FILE *fichier = fopen(name, "w");
  fclose(fichier);
}

void generationNombres(NMBS *Nmbs) {
  for (int i=0; i<Nmbs->taille; i++) {
    Nmbs->nmbs[i] = rand()%500+1;
  }
}

void insertionNombresFichier(NMBS *Nmbs, char *name) {
  FILE *fichier = fopen(name, "w");
  for (int i=0; i<Nmbs->taille; i++) {
    fprintf(fichier, "%d ", Nmbs->nmbs[i]);
  }
  fclose(fichier);
} 

int lireTailleFichier(char *name) {
  FILE *fichier = fopen(name, "r");
  int taille=0;
  int c;

  if (fichier) {
    while ((c = fgetc(fichier)) != EOF) {
      if (c== ' ') {
        taille++;
      }
    }
    fclose(fichier);
    return taille;
  }
  return 0;
}

void nmbsReset(NMBS *Nmbs) {
  free(Nmbs->nmbs);
  Nmbs->nmbs=NULL;
  Nmbs->taille=0;
}

void insertFileNmbs(NMBS *Nmbs, char *name) {
  FILE *fichier = fopen(name, "r");

  if (fichier) {
    for (int i=0; i<Nmbs->taille; i++) {
      if (fscanf(fichier, "%d", &Nmbs->nmbs[i]) != 1) {
        break;
      }
    }
    fclose(fichier);
  }
}

int findMax(NMBS *Nmbs) {
  int max=0;
  for (int i=0; i<Nmbs->taille; i++) {
    if (Nmbs->nmbs[i]>max) {
      max=Nmbs->nmbs[i];
    }
  }
  return max;
}

int findMin(NMBS *Nmbs) {
  int min=500;
  for (int i=0; i<Nmbs->taille; i++) {
    if (Nmbs->nmbs[i]<min) {
      min=Nmbs->nmbs[i];
    }
  }
  return min;
}

float findMoy(NMBS *Nmbs) {
  float total=0;
  float moy;

  for (int i=0; i<Nmbs->taille; i++) {
      total+=Nmbs->nmbs[i];
  }
  moy = total/Nmbs->taille;
  return moy;
}

double findEcartType(NMBS *Nmbs) {
    double moy = findMoy(Nmbs);
    double total = 0;

    for (int i = 0; i < Nmbs->taille; i++) {
        double diff = Nmbs->nmbs[i] - moy;
        total += diff * diff;
    }

    return sqrt(total / Nmbs->taille);
}

int main() {
  srand(time(NULL));
  NMBS nmbs;
  char *name = "nombres.txt";
  int taille=rand()%500 +1;
  initStruct(&nmbs, taille);
  initFichier(name);
  generationNombres(&nmbs);
  insertionNombresFichier(&nmbs, name);
  printf("%d\n", nmbs.taille);
  nmbsReset(&nmbs);
  printf("%d\n", nmbs.taille);
  nmbs.taille = lireTailleFichier(name);
  printf("%d\n", nmbs.taille);
  initStruct(&nmbs, nmbs.taille);
  insertFileNmbs(&nmbs, name);
  int max = findMax(&nmbs);
  printf("max : %d\n", max);
  int min =findMin(&nmbs);
  printf("min : %d\n", min);
  float moy = findMoy(&nmbs);
  printf("moy : %f\n", moy);
  double ET = findEcartType(&nmbs);
  printf("Ecart type : %f\n", ET);


  nmbsReset(&nmbs);
  return 0;
}
