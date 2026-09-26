#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_RAND 101

typedef struct {
  int *tab;
  int taille;
} Tableau;

typedef struct {
    int *P;
    int sommet;
    int taille;
} Pile;

Tableau tailleTableau(){
  Tableau t;
  printf("choisir la taille du tableau : ");
  scanf("%d", &t.taille);
  t.tab = malloc(sizeof(*t.tab) * t.taille);
  
  return t;
}

void initia(Tableau t) {
  for (int i=0; i<t.taille; i++) {
    t.tab[i] = rand() % MAX_RAND;
  }
}

void afficherTableau(Tableau t) {
  for (int i=0; i<t.taille; i++) {
    printf("%d ", t.tab[i]);
  }
}

bool pilePleine(Pile pile) {
    return pile.sommet == pile.taille;
}

bool pileVide(Pile pile) {
    return pile.sommet == 0;
}

void initialiser(Pile *pile, Tableau *t) {
  pile->taille = t->taille;
  pile->P = malloc(sizeof(*pile->P) * pile->taille);
  for (int i = 0; i < pile->taille; i++) {
    pile->P[i] = 0;
  }
  pile->sommet = 0;
}

void empiler(Pile *pile, int x) {
    if (pilePleine(*pile)) {
        printf("Pile deja remplie.");
    } else {
        pile->P[pile->sommet]= x;
        pile->sommet++;
    }
}

int depiler(Pile *pile) {
    if (pileVide(*pile)) {
        printf("la pile est deja vide");
        return 0;
    } else {
        pile->sommet--;
        int x = pile->P[pile->sommet];
        pile->P[pile->sommet] = 0;
        return x;
    }
}

void status(Pile pile) {
  if (pileVide(pile)) {
    printf("la pile est vide");
  } else if (pilePleine(pile)) {
    printf("la pile est pleine");
  } else {
    printf("%d", pile.sommet+1);
  }
  printf("\n");
}

void showPile(Pile pile) {
    for (int i = 0; i < pile.taille; i++) {
        printf("%d ", pile.P[i]);
    }
    printf("\n");
}

void renverser(Tableau *t, Pile *pile) {
    for (int i = 0; i < t->taille; i++) {
        empiler(pile, t->tab[i]);
    }
    for (int i = 0; i < t->taille; i++) {
        t->tab[i] = depiler(pile);
    }
}

int main() {
    Tableau t = tailleTableau();
    initia(t);
    afficherTableau(t);
    printf("\n");
    Pile pile;
    printf("\n\n");
    initialiser(&pile, &t);
    renverser(&t, &pile);
    afficherTableau(t);
    printf("\n");
    free(pile.P);
    free(t.tab);
    return 0;
}
