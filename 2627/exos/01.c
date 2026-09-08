#include <stdio.h>
#include <stdbool.h>

bool isBissextile(int n) {
    return((n%4 == 0) && (n%100 != 0) || (n%400 == 0));
}

int main() {
    printf("Hello, World!\n");
    printf("taille int = %lu\n", sizeof(int));
    printf("taille long = %lu\n", sizeof(long));
    printf("taille char = %lu\n", sizeof(char));
    printf("taille d'un float = %lu\n", sizeof(float));
    printf("taille d'un double = %lu\n", sizeof(double));

    printf(" \n\n");
    unsigned char cpt=0;
    while ((unsigned char)(cpt+1) > cpt) {
        cpt = cpt+1;
    }
    printf("valeur maximale de unsigned char = %u\n", cpt);
    
    printf(" \n\n");
    int i = 35;
    printf("valeur de i = %d\n", i);
    void * ptr = &i;
    printf("valeur de ptr = %f\n", ptr);
    float a = *(float *)ptr;
    printf("valeur de a = %f\n", a);
    
    printf("\n\n");
    int annee = 1;
    if (isBissextile(annee)) {
        printf("c'est bissextile : %i\n", annee);
    } else {
        printf("ce n'est pas bissextile : %d\n", annee);
    }

    printf("\n\n");
    int anbase;
    printf("année ? : ");
    scanf("%d", &anbase);
    int ancmpt = anbase;
    int ancur = 2026;
    while (ancmpt <= ancur) {
        if (isBissextile(ancmpt)) {
            printf(" - %d", ancmpt);
        }
        ancmpt++;
    }



    printf(" \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}