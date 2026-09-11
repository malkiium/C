#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isBissextile(int n) {
    return(((n%4 == 0) && (n%100 != 0)) || (n%400 == 0));
}

int jourSemaine(int d, int m, int y) {
    return (d += (m < 3) ? y-- : y - 2,
            (23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7);
}

void PrtJS() { 
    int d, m, y;

    printf("Jour : ");
    scanf("%d", &d);

    printf("Mois : ");
    scanf("%d", &m);

    printf("Annee : ");
    scanf("%d", &y);

    int wd = jourSemaine(d, m, y);

    switch (wd) {
        case 0:
            printf("Dimanche\n");
            break;
        case 1:
            printf("Lundi\n");
            break;
        case 2:
            printf("Mardi\n");
            break;
        case 3:
            printf("Mercredi\n");
            break;
        case 4:
            printf("Jeudi\n");
            break;
        case 5:
            printf("Vendredi\n");
            break;
        case 6:
            printf("Samedi\n");
            break;
    }
}

void PlGrCoDi() {
    int a,b;
    printf(" a? : ");
    scanf("%d", &a);
    printf(" b? : ");
    scanf("%d", &b);
    int limite=((a<b)?a:b);
    int pgcd=1;
    for(int i=2; i<limite; i++) {
        if(a%i == 0 && b%i ==0) {
            pgcd=i;
            printf("%d\n", pgcd);
        }
    }
    if (pgcd==1) {
        printf("%d\n", pgcd);
    }
}

int main() {
    PrtJS();
    printf("\n\n");
    PlGrCoDi();
}