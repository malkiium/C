#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAILLE 5


void initialiser(int V[]) {
  for (int i=0; i<TAILLE; i++) {
    V[i] = 0;
  }
}

void inserer(int V[], int x, int y) {
  if (x>TAILLE) {
    printf("trop grand., taille entre 1-5");
  } else if (x <= 0) {
    printf("trop petit, taille entre 1-5");
  } else {
    V[x-1] = y;
  }
}

double recuperer(int V[], int x) {
  if (x>TAILLE) {
    printf("trop grand., taille entre 1-5");
  } else if (x <= 0) {
    printf("trop petit, taille entre 1-5");
  } else {
    return V[x-1];
  }
  return NAN;
}

void showVect(int V[]) {
  for (int i=0; i<TAILLE; i++) {
    printf("%d ", V[i]);
  }
  printf("\n");
}

int main() {
  int V[TAILLE];

  initialiser(V);
  inserer(V, 2, 68);
  showVect(V);
  printf("%f\n", recuperer(V, 2));

  return 0;
}
