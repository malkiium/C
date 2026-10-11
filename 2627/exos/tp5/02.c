#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char prenom[51];
  char nom[51];
  char grade[51];
} personne_t;

typedef struct {
  char nom[51];
  int annee;
} naissance_t;

typedef struct {
  char prenom[51];
  char nom[51];
  char grade[51];
  int annee;
} total_t;

int comp(naissance_t *naissance, char *nomGrader) {
  FILE *fichier = fopen("naissance.bin", "rb");

  if (fichier == NULL) {
    return -1;
  }

  while (fread(naissance, sizeof(naissance_t), 1, fichier) == 1) {
    if (strcmp(naissance->nom, nomGrader) == 0) {
      int annee = naissance->annee;
      fclose(fichier);
      return annee;
    }
  }
  fclose(fichier);
  return 0;
}

int chercherGrade(personne_t *p, char *grade) {
  FILE *fichier = fopen("personel.txt", "r");
  naissance_t naissance;

  if (fichier == NULL) {
    return -1;
  }

  while (fscanf(fichier, "%50s %50s %50s", p->prenom, p->nom, p->grade) == 3) {
    if (strcmp(p->grade, grade) == 0) {
      if (comp(&naissance, p->nom) >= 0) {
        fclose(fichier);
        return naissance.annee;
      }
    }
  }
  fclose(fichier);
  return 0;
}

void combineIntoBin(char *fileName, personne_t *p) {
  FILE *fichierNouveau = fopen(fileName, "ab");
  FILE *fichier = fopen("personel.txt", "r");
  naissance_t naissance;
  total_t total;

  if (fichierNouveau == NULL) {
    return;
  }
  if (fichier == NULL) {
    return;
  }

  while (fscanf(fichier, "%50s %50s %50s", p->prenom, p->nom, p->grade) == 3) {
    if (comp(&naissance, p->nom) > 0) {
      strcpy(total.prenom, p->prenom);
      strcpy(total.nom, p->nom);
      strcpy(total.grade, p->grade);
      total.annee = naissance.annee;
      fwrite(&total, sizeof(total_t), 1, fichierNouveau);
    }
  }
  fclose(fichierNouveau);
  fclose(fichier);
}

void afficherBin(char *fileName) {
  FILE *fichier = fopen(fileName, "rb");
  total_t total;

  if (fichier == NULL) {
    return;
  }

  while (fread(&total, sizeof(total_t), 1, fichier) == 1) {
    printf("%s %s %s %d\n", total.prenom, total.nom, total.grade, total.annee);
  }

  fclose(fichier);
}

int main() {
  personne_t personne;
  char *grade = "capitaine";
  int annee = chercherGrade(&personne, grade);
  printf("\n\n");
  printf("l'annee de naissance du %s ", grade);
  printf("est de : %d\n", annee);
  char *fileName = "total.bin";
  FILE *fichier = fopen(fileName, "wb");
  fclose(fichier);
  printf("\n\n");
  combineIntoBin(fileName, &personne);
  afficherBin(fileName);

  return 0;
}
