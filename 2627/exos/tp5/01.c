#include <stdlib.h>
#include <stdio.h>

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

FILE *initFichier() {
  FILE *fichier = fopen("nombre.txt", "w");
  return fichier;
}

void generationNombres(NMBS *Nmbs) {
  for (int i=0; i<Nmbs->taille; i++) {
    Nmbs->nmbs[i] = rand();
  }
}

void insertionNombresFichier(NMBS *Nmbs, FILE *fichier) {
  for (int i=0; i<Nmbs->taille; i++) {
    fprintf(fichier, "%d ", Nmbs->nmbs[i]);
  }
  fclose(fichier);
} 

int main() {
  NMBS nmbs;
  int taille=10;
  initStruct(&nmbs, taille);
  FILE *file = initFichier();
  generationNombres(&nmbs);
  insertionNombresFichier(&nmbs, file);

  free(nmbs.nmbs);
  return 0;
}
