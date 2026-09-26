#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void afficherASCII() {
  for (int i=32; i<=126; i++) {
    printf("%c ", i);
  }
}

void toUpper(char *str) {
  while (*str != '\0') {
    if (*str >= 'a' && *str <= 'z') {
      *str = *str - ('a' - 'A');
    }
    str++;
  }
}

int count(char *str) {
  int count = 0;
  bool prevSeparateur = true;

  while (*str != '\0') {
    if (*str == ' ' || *str == '\t' || *str == ',' || *str == '.' || 
      *str == ':' || *str == ';' || *str == '?' || *str == '!') {
      prevSeparateur = true;
    } else if (prevSeparateur) {
      count++;
      prevSeparateur = false;
    }
    str++;
  }
  return count;
}

int strLen(char *str) {
  int taille=0;
  while (*str != '\0') {
    taille++;
    str++;
  }
  return taille;
}

char *strDup(char *str) {
  int taille = strLen(str);
  char *copie = malloc(sizeof(*copie)*(taille+1));

  if (copie == NULL) {
    return NULL;
  }
  for (int i=0; i<=taille; i++) {
    copie[i] = str[i];
  }
  return copie;
}

char *strCat(char *str, char *ostr) {
  int taille1 = strLen(str);
  int taille2 = strLen(ostr);
  char *tmp = realloc(str, sizeof(*str)*(taille1+taille2+1));

  if (tmp == NULL) {
    return NULL;
  }

  str = tmp;

  for (int j=0; j<=taille2; j++) {
    str[taille1+j]= ostr[j];
  }
  return str;
}

char *revert(char *str) {
  if (str == NULL) {
    return NULL;
  }
 
  int taille = strLen(str);
  char *tmp = realloc(str, sizeof(*str) * ((taille * 2) + 1));

  if (tmp == NULL) {
    return NULL;
  }

  str = tmp;

  for (int j = taille - 1; j >= 0; j--) {
    str[(2 * taille - 1) - j] = str[j];
  }
  for (int j = 0; j < taille; j++) {
    str[j] = str[taille + j];
  }

  str[taille] = '\0';

  return str;
}

int main() {
  printf("=== afficherASCII ===\n");
  afficherASCII();
  printf("\n\n");

  printf("=== toUpper ===\n");
  char upper[] = "Bonjour le Monde! abc XYZ 123";
  printf("Avant : %s\n", upper);
  toUpper(upper);
  printf("Apres : %s\n\n", upper);

  printf("=== count ===\n");
  char phrase[] = "Bonjour, ceci est une phrase. Avec plusieurs mots!";
  printf("Chaine : %s\n", phrase);
  printf("Nombre de mots : %d\n\n", count(phrase));

  printf("=== strLen ===\n");
  char longueur[] = "Hello World";
  printf("Chaine : %s\n", longueur);
  printf("Longueur : %d\n\n", strLen(longueur));

  printf("=== strDup ===\n");
  char original[] = "Nebula";
  char *copie = strDup(original);

  if (copie != NULL) {
    printf("Original : %s\n", original);
    printf("Copie : %s\n\n", copie);
    free(copie);
  } else {
    printf("Erreur allocation strDup\n\n");
  }

  printf("=== strCat ===\n");
  char *concat = strDup("Hello ");

  if (concat != NULL) {
    concat = strCat(concat, "World!");

    if (concat != NULL) {
      printf("Resultat : %s\n\n", concat);
      free(concat);
    } else {
      printf("Erreur realloc strCat\n\n");
    }
  }

  printf("=== revert ===\n");
  char *inverse = strDup("abcdef");

  if (inverse != NULL) {
    printf("Avant : %s\n", inverse);
    inverse = revert(inverse);

    if (inverse != NULL) {
      printf("Apres : %s\n", inverse);
      free(inverse);
    } else {
      printf("Erreur realloc revert\n");
    }
  }

  return 0;
}
