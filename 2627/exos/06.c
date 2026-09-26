#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define TAILLE 5

bool pilePleine(int *sommet) {
  if (*sommet == TAILLE-1) {
    return true;
  }
  return false;
}

bool pileVide(int *sommet) {
  if (*sommet == 0) {
    return true;
  }
  return false;
}

void initialiser(int P[], int *sommet) {
  for (int i=0; i<TAILLE; i++) {
    P[i] = 0;
  }
  (*sommet) = 0;
}

void empiler(int P[], int x, int *sommet) {
  if (pilePleine(sommet)) {
    printf("Pile deja remplie.");  
  } else {
    P[*sommet] = x; 
    (*sommet)++;
  }
}

void depiler(int P[], int *sommet) {
  if (pileVide(sommet)) {
    printf("la pile est deja vide");
  } else {
    (*sommet)--;
    P[*sommet] = 0;
  }
  printf("\n");
}

void status(int *sommet) {
  if (pileVide(sommet)) {
    printf("la pile est vide");
  } else if (pilePleine(sommet)) {
    printf("la pile est pleine");
  } else {
    printf("%d", *sommet+1);
  }
  printf("\n");
}

void showPile(int P[]) {
  for (int i=0; i<TAILLE; i++) {
    printf("%d ", P[i]);
  }
  printf("\n");
}

int main() {
  int P[TAILLE];
  int sommet;
  initialiser(P, &sommet);
  showPile(P);
  empiler(P, 5, &sommet);
  showPile(P);
  depiler(P, &sommet);
  showPile(P);
  depiler(P, &sommet);
  showPile(P);
  status(&sommet);
  showPile(P);

  return 0;
}
