#include <stdio.h>
#include <stdlib.h>
#include <math.h>





void afficherTableau(int T[], int n) {
  for (int i=0; i<n; i++) {
    printf("%d\n", T[i]);
  }
}

void initTableau(int T[], int n) {
  for (int i=0; i<n; i++) {
    T[i] = 0;
  }
}

void remplirTableau(int T[], int n) {
    for (int i = 0; i < n; i++) {
        T[i] = rand() % 101;
    }
}

int getMaxTableau(int T[], int n) {
  int max=0;
  for (int i=0; i<n; i++) {
    if (T[i] > max) {
      max = T[i];
    }
  } 
  return max;
}

double calculeMoyenne(int T[], int n) {
  int sum=0;
  for (int i=0; i<n; i++) {
    sum += T[i];
  }
  return (double) sum/n;
}

double calculeEcartType(int T[], int n) {
    double moyenne = calculeMoyenne(T, n);
    double somme = 0;

    for (int i = 0; i < n; i++) {
        somme += (T[i] - moyenne) * (T[i] - moyenne);
    }

    return sqrt(somme / n);
}

void calculerHistogramme(int T[], int n, int H[], int m) {
    initTableau(H, m);

    int max = getMaxTableau(T, n);
    double largeur = (double)(max + 1) / m;

    for (int i = 0; i < n; i++) {
        int classe = T[i] / largeur;

        if (classe >= m) {
            classe = m - 1;
        }

        H[classe]++;
    }
}

void afficheHistogramme(int H[], int m) {
    for (int i = 0; i < m; i++) {

        if (H[i] == 0)
            continue;

        printf("%d ", i);

        for (int j = 0; j < H[i]; j++) {
            printf("*");
        }

        printf("\n");
    }
}

typedef double Matrice[3][3];

void afficheMatrice(Matrice M) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.2f ", M[i][j]);
        }
        printf("\n");
    }
}

void initMatrice(Matrice M) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M[i][j] = 0;
        }
    }
}

void identite(Matrice M) {
    initMatrice(M);

    for (int i = 0; i < 3; i++) {
        M[i][i] = 1;
    }
}

void randomMatrice(Matrice M) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

void ajouteMatrice(Matrice M1, Matrice M2, Matrice M3) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M3[i][j] = M1[i][j] + M2[i][j];
        }
    }
}

void soustraitMatrice(Matrice M1, Matrice M2, Matrice M3) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M3[i][j] = M1[i][j] - M2[i][j];
        }
    }
}

void multiplieMatrice(Matrice M1, Matrice M2, Matrice M3) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M3[i][j] = 0;

            for (int k = 0; k < 3; k++) {
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
}

double determinant(Matrice M) {
    return M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
         - M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])
         + M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
}

void inverseMatrice(Matrice M) {
    double det = determinant(M);

    if (det == 0) {
        printf("Matrice non inversible\n");
        return;
    }

    Matrice inverse;

    inverse[0][0] =  (M[1][1]*M[2][2] - M[1][2]*M[2][1]) / det;
    inverse[0][1] = -(M[0][1]*M[2][2] - M[0][2]*M[2][1]) / det;
    inverse[0][2] =  (M[0][1]*M[1][2] - M[0][2]*M[1][1]) / det;

    inverse[1][0] = -(M[1][0]*M[2][2] - M[1][2]*M[2][0]) / det;
    inverse[1][1] =  (M[0][0]*M[2][2] - M[0][2]*M[2][0]) / det;
    inverse[1][2] = -(M[0][0]*M[1][2] - M[0][2]*M[1][0]) / det;

    inverse[2][0] =  (M[1][0]*M[2][1] - M[1][1]*M[2][0]) / det;
    inverse[2][1] = -(M[0][0]*M[2][1] - M[0][1]*M[2][0]) / det;
    inverse[2][2] =  (M[0][0]*M[1][1] - M[0][1]*M[1][0]) / det;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            M[i][j] = inverse[i][j];
        }
    }
}

int main(void) {
  int T[100];
  int n;
  printf("Taille n : ");
  scanf("%d", &n);
  
  afficherTableau(T, n);
  initTableau(T, n);
  printf("set to 0\n");
  afficherTableau(T, n);
  printf("randomized\n");
  remplirTableau(T, n);
  afficherTableau(T, n);
  printf("get max \n");
  printf("%d \n", getMaxTableau(T, n));
  printf("moyenne \n");
  printf("%f\n", calculeMoyenne(T, n));
  printf("ecart type \n");
  printf("%f \n", calculeEcartType(T, n));
  int H[101];
  int m=101;
  initTableau(H, m);
  calculerHistogramme(T, n, H, m);
  afficheHistogramme(H, m);
  printf("\n=== MATRICES ===\n");
  Matrice M1;
  Matrice M2;
  Matrice M3;
  printf("\nMatrice nulle :\n");
  initMatrice(M1);
  afficheMatrice(M1);
  printf("\nIdentite :\n");
  identite(M1);
  afficheMatrice(M1);
  printf("\nM1 random :\n");
  randomMatrice(M1);
  afficheMatrice(M1);
  printf("\nM2 random :\n");
  randomMatrice(M2);
  afficheMatrice(M2);
  printf("\nM1 + M2 :\n");
  ajouteMatrice(M1, M2, M3);
  afficheMatrice(M3);
  printf("\nM1 - M2 :\n");
  soustraitMatrice(M1, M2, M3);
  afficheMatrice(M3);
  printf("\nM1 * M2 :\n");
  multiplieMatrice(M1, M2, M3);
  afficheMatrice(M3);
  printf("\nDeterminant M1 :\n");
  printf("%f\n", determinant(M1));
  printf("\n=== INVERSE M1 ===\n");
  inverseMatrice(M1);
  afficheMatrice(M1);


  return 0;
}

